# This shell script emits a C file. -*- C -*-
#   Copyright 2004, 2006, 2007, 2008 Free Software Foundation, Inc.
#
# This file is part of the GNU Binutils.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
# MA 02110-1301, USA.

fragment <<EOF

#include "ldctor.h"
#include "elf/mips.h"
#include "elfxx-mips.h"

#define is_mips_elf(bfd)				\
  (bfd_get_flavour (bfd) == bfd_target_elf_flavour	\
   && elf_tdata (bfd) != NULL				\
   && elf_object_id (bfd) == MIPS_ELF_DATA)

/* Fake input file for stubs.  */
static lang_input_statement_type *stub_file;
static bfd *stub_bfd;

static bfd_boolean insn32;

struct hook_stub_info
{
  lang_statement_list_type add;
  asection *input_section;
};

/* Traverse the linker tree to find the spot where the stub goes.  */

static bfd_boolean
hook_in_stub (struct hook_stub_info *info, lang_statement_union_type **lp)
{
  lang_statement_union_type *l;
  bfd_boolean ret;

  for (; (l = *lp) != NULL; lp = &l->header.next)
    {
      switch (l->header.type)
	{
	case lang_constructors_statement_enum:
	  ret = hook_in_stub (info, &constructor_list.head);
	  if (ret)
	    return ret;
	  break;

	case lang_output_section_statement_enum:
	  ret = hook_in_stub (info,
			      &l->output_section_statement.children.head);
	  if (ret)
	    return ret;
	  break;

	case lang_wild_statement_enum:
	  ret = hook_in_stub (info, &l->wild_statement.children.head);
	  if (ret)
	    return ret;
	  break;

	case lang_group_statement_enum:
	  ret = hook_in_stub (info, &l->group_statement.children.head);
	  if (ret)
	    return ret;
	  break;

	case lang_input_section_enum:
	  if (info->input_section == NULL
	      || l->input_section.section == info->input_section)
	    {
	      /* We've found our section.  Insert the stub immediately
		 before its associated input section.  */
	      *lp = info->add.head;
	      *(info->add.tail) = l;
	      return TRUE;
	    }
	  break;

	case lang_data_statement_enum:
	case lang_reloc_statement_enum:
	case lang_object_symbols_statement_enum:
	case lang_output_statement_enum:
	case lang_target_statement_enum:
	case lang_input_statement_enum:
	case lang_assignment_statement_enum:
	case lang_padding_statement_enum:
	case lang_address_statement_enum:
	case lang_fill_statement_enum:
	  break;

	default:
	  FAIL ();
	  break;
	}
    }
  return FALSE;
}

/* Create a new stub section called STUB_SEC_NAME and arrange for it to
   be linked in OUTPUT_SECTION.  The section should go at the beginning of
   OUTPUT_SECTION if INPUT_SECTION is null, otherwise it must go immediately
   before INPUT_SECTION.  */

static asection *
mips_add_stub_section (const char *stub_sec_name, asection *input_section,
		       asection *output_section)
{
  asection *stub_sec;
  flagword flags;
  const char *secname;
  lang_output_section_statement_type *os;
  struct hook_stub_info info;

  /* PR 12845: If the input section has been garbage collected it will
     not have its output section set to *ABS*.  */
  if (bfd_is_abs_section (output_section))
    return NULL;

  /* Create the stub file, if we haven't already.  */
  if (stub_file == NULL)
    {
      stub_file = lang_add_input_file ("linker stubs",
				       lang_input_file_is_fake_enum,
				       NULL);
      stub_bfd = bfd_create ("linker stubs", link_info.output_bfd);
      if (stub_bfd == NULL
	  || !bfd_set_arch_mach (stub_bfd,
				 bfd_get_arch (link_info.output_bfd),
				 bfd_get_mach (link_info.output_bfd)))
	{
	  einfo ("%F%P: can not create BFD %E\n");
	  return NULL;
	}
      stub_bfd->flags |= BFD_LINKER_CREATED;
      stub_file->the_bfd = stub_bfd;
      ldlang_add_file (stub_file);
    }

  /* Create the section.  */
  stub_sec = bfd_make_section_anyway (stub_bfd, stub_sec_name);
  if (stub_sec == NULL)
    goto err_ret;

  /* Set the flags.  */
  flags = (SEC_ALLOC | SEC_LOAD | SEC_READONLY | SEC_CODE
	   | SEC_HAS_CONTENTS | SEC_IN_MEMORY | SEC_KEEP);
  if (!bfd_set_section_flags (stub_bfd, stub_sec, flags))
    goto err_ret;

  /* Create an output section statement.  */
  secname = bfd_get_section_name (output_section->owner, output_section);
  os = lang_output_section_find (secname);

  /* Initialize a statement list that contains only the new statement.  */
  lang_list_init (&info.add);
  lang_add_section (&info.add, stub_sec, NULL, os);
  if (info.add.head == NULL)
    goto err_ret;

  /* Insert the new statement in the appropriate place.  */
  info.input_section = input_section;
  if (hook_in_stub (&info, &os->children.head))
    return stub_sec;

 err_ret:
  einfo ("%X%P: can not make stub section: %E\n");
  return NULL;
}

/* This is called before the input files are opened.  */

static void
mips_create_output_section_statements (void)
{
  struct elf_link_hash_table *htab;

  htab = elf_hash_table (&link_info);
  if (is_elf_hash_table (htab) && is_mips_elf (link_info.output_bfd))
    _bfd_mips_elf_insn32 (&link_info, insn32);

  if (is_mips_elf (link_info.output_bfd))
    _bfd_mips_elf_init_stubs (&link_info, mips_add_stub_section);
}

/* This is called after we have merged the private data of the input bfds.  */

static void
mips_before_allocation (void)
{
  flagword flags;

  flags = elf_elfheader (link_info.output_bfd)->e_flags;
  if (!link_info.shared
      && !link_info.nocopyreloc
      && (flags & (EF_MIPS_PIC | EF_MIPS_CPIC)) == EF_MIPS_CPIC)
    _bfd_mips_elf_use_plts_and_copy_relocs (&link_info);

  gld${EMULATION_NAME}_before_allocation ();
}

/* Avoid processing the fake stub_file in vercheck, stat_needed and
   check_needed routines.  */

static void (*real_func) (lang_input_statement_type *);

static void mips_for_each_input_file_wrapper (lang_input_statement_type *l)
{
  if (l != stub_file)
    (*real_func) (l);
}

static void
mips_lang_for_each_input_file (void (*func) (lang_input_statement_type *))
{
  real_func = func;
  lang_for_each_input_file (&mips_for_each_input_file_wrapper);
}

#define lang_for_each_input_file mips_lang_for_each_input_file

EOF

# Define some shell vars to insert bits of code into the standard elf
# parse_args and list_options functions.
#
PARSE_AND_LIST_PROLOGUE='
#define OPTION_INSN32			301
#define OPTION_NO_INSN32		(OPTION_INSN32 + 1)
'

PARSE_AND_LIST_LONGOPTS='
  { "insn32", no_argument, NULL, OPTION_INSN32 },
  { "no-insn32", no_argument, NULL, OPTION_NO_INSN32 },
'

PARSE_AND_LIST_OPTIONS='
  fprintf (file, _("\
  --insn32                    Only generate 32-bit microMIPS instructions\n"
		   ));
  fprintf (file, _("\
  --no-insn32                 Generate all microMIPS instructions\n"
		   ));
'

PARSE_AND_LIST_ARGS_CASES='
    case OPTION_INSN32:
      insn32 = TRUE;
      break;

    case OPTION_NO_INSN32:
      insn32 = FALSE;
      break;
'

LDEMUL_BEFORE_ALLOCATION=mips_before_allocation
LDEMUL_CREATE_OUTPUT_SECTION_STATEMENTS=mips_create_output_section_statements
