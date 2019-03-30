/* mips-opc.c -- MIPS opcode list.
   Copyright 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
   2003, 2004, 2005, 2006, 2007, 2008, 2009, 2012
   Free Software Foundation, Inc.
   Contributed by Ralph Campbell and OSF
   Commented and modified by Ian Lance Taylor, Cygnus Support
   Extended for MIPS32 support by Anders Norlander, and by SiByte, Inc.
   MIPS-3D, MDMX, and MIPS32 Release 2 support added by Broadcom
   Corporation (SiByte).

   This file is part of the GNU opcodes library.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this file; see the file COPYING.  If not, write to the
   Free Software Foundation, 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include <stdio.h>
#include "opcode/mips.h"
#include "mips-formats.h"

/* The 4-bit XYZW mask used in some VU0 instructions.  */
const struct mips_operand mips_vu0_channel_mask = { OP_VU0_SUFFIX, 4, 21 };

static unsigned char reg_0_map[] = { 0 };

/* Return the mips_operand structure for the operand at the beginning of P.  */

const struct mips_operand *
decode_mips_operand (const char *p)
{
  switch (p[0])
    {
    case '+':
      switch (p[1])
	{
	case '1': HINT (5, 6);
	case '2': HINT (10, 6);
	case '3': HINT (15, 6);
	case '4': HINT (20, 6);
	case '5': REG (5, 6, VF);
	case '6': REG (5, 11, VF);
	case '7': REG (5, 16, VF);
	case '8': REG (5, 6, VI);
	case '9': REG (5, 11, VI);
	case '0': REG (5, 16, VI);

	case 'A': BIT (5, 6, 0);		/* (0 .. 31) */
	case 'B': MSB (5, 11, 1, TRUE, 32);	/* (1 .. 32), 32-bit op */
	case 'C': MSB (5, 11, 1, FALSE, 32);	/* (1 .. 32), 32-bit op */
	case 'E': BIT (5, 6, 32);		/* (32 .. 63) */
	case 'F': MSB (5, 11, 33, TRUE, 64);	/* (33 .. 64), 64-bit op */
	case 'G': MSB (5, 11, 33, FALSE, 64);	/* (33 .. 64), 64-bit op */
	case 'H': MSB (5, 11, 1, FALSE, 64);	/* (1 .. 32), 64-bit op */
	case 'J': HINT (10, 11);
	case 'K': SPECIAL (4, 21, VU0_MATCH_SUFFIX);
	case 'L': SPECIAL (2, 21, VU0_SUFFIX);
	case 'M': SPECIAL (2, 23, VU0_SUFFIX);
	case 'N': SPECIAL (2, 0, VU0_MATCH_SUFFIX);
	case 'P': BIT (5, 6, 32);		/* (32 .. 63) */
	case 'Q': SINT (10, 6);
	case 'S': MSB (5, 11, 0, FALSE, 63);	/* (0 .. 31), 64-bit op */
	case 'X': BIT (5, 16, 32);		/* (32 .. 63) */
	case 'Z': REG (5, 0, FP);

	case 'a': SINT (8, 6);
	case 'b': SINT (8, 3);
	case 'c': INT_ADJ (9, 6, 255, 4, FALSE); /* (-256 .. 255) << 4 */
	case 'd': BIT (0, 31, 0); /* get 0 */
	case 'f': INT_ADJ (15, 6, 32767, 3, TRUE);
	case 'g': SINT (5, 6);
	case 'i': JALX (26, 0, 2);
	case 'j': SINT (9, 7);
	case 'm': REG (0, 0, R5900_ACC);
	case 'p': BIT (5, 6, 0);		/* (0 .. 31), 32-bit op */
	case 'q': REG (0, 0, R5900_Q);
	case 'r': REG (0, 0, R5900_R);
	case 's': MSB (5, 11, 0, FALSE, 31);	/* (0 .. 31) */
	case 't': REG (5, 16, COPRO);
	case 'x': BIT (5, 16, 0);		/* (0 .. 31) */
	case 'y': REG (0, 0, R5900_I);
	case 'z': REG (5, 0, GP);
	}
      break;

    case '<': BIT (5, 6, 0);			/* (0 .. 31) */
    case '>': BIT (5, 6, 32);			/* (32 .. 63) */
    case '%': UINT (3, 21);
    case ':': SINT (7, 19);
    case '\'': HINT (6, 16);
    case '@': SINT (10, 16);
    case '!': UINT (1, 5);
    case '$': UINT (1, 4);
    case '*': REG (2, 18, ACC);
    case '&': REG (2, 13, ACC);
    case '~': SINT (12, 0);
    case '\\': BIT (3, 12, 0);			/* (0 .. 7) */

    case '0': SINT (6, 20);
    case '1': HINT (5, 6);
    case '2': HINT (2, 11);
    case '3': HINT (3, 21);
    case '4': HINT (4, 21);
    case '5': HINT (8, 16);
    case '6': HINT (5, 21);
    case '7': REG (2, 11, ACC);
    case '8': HINT (6, 11);
    case '9': REG (2, 21, ACC);

    case 'B': HINT (20, 6);
    case 'C': HINT (25, 0);
    case 'D': REG (5, 6, FP);
    case 'E': REG (5, 16, COPRO);
    case 'G': REG (5, 11, COPRO);
    case 'H': UINT (3, 0);
    case 'J': HINT (19, 6);
    case 'K': REG (5, 11, HW);
    case 'M': REG (3, 8, CCC);
    case 'N': REG (3, 18, CCC);
    case 'O': UINT (3, 21);
    case 'P': SPECIAL (5, 1, PERF_REG);
    case 'Q': SPECIAL (10, 16, MDMX_IMM_REG);
    case 'R': REG (5, 21, FP);
    case 'S': REG (5, 11, FP);
    case 'T': REG (5, 16, FP);
    case 'U': SPECIAL (10, 11, CLO_CLZ_DEST);
    case 'V': OPTIONAL_REG (5, 11, FP);
    case 'W': OPTIONAL_REG (5, 16, FP);
    case 'X': REG (5, 6, VEC);
    case 'Y': REG (5, 11, VEC);
    case 'Z': REG (5, 16, VEC);

    case 'a': JUMP (26, 0, 2);
    case 'b': REG (5, 21, GP);
    case 'c': HINT (10, 16);
    case 'd': REG (5, 11, GP);
    case 'e': UINT (3, 22)
    case 'g': REG (5, 11, COPRO);
    case 'h': HINT (5, 11);
    case 'i': HINT (16, 0);
    case 'j': SINT (16, 0);
    case 'k': HINT (5, 16);
    case 'o': SINT (16, 0);
    case 'p': BRANCH (16, 0, 2);
    case 'q': HINT (10, 6);
    case 'r': OPTIONAL_REG (5, 21, GP);
    case 's': REG (5, 21, GP);
    case 't': REG (5, 16, GP);
    case 'u': HINT (16, 0);
    case 'v': OPTIONAL_REG (5, 21, GP);
    case 'w': OPTIONAL_REG (5, 16, GP);
    case 'x': REG (0, 0, GP);
    case 'z': MAPPED_REG (0, 0, GP, reg_0_map);
    }
  return 0;
}

/* Short hand so the lines aren't too long.  */

#define LDD     INSN_LOAD_MEMORY_DELAY
#define LCD	INSN_LOAD_COPROC_DELAY
#define UBD     INSN_UNCOND_BRANCH_DELAY
#define CBD	INSN_COND_BRANCH_DELAY
#define COD     INSN_COPROC_MOVE_DELAY
#define CLD	INSN_COPROC_MEMORY_DELAY
#define CBL	INSN_COND_BRANCH_LIKELY
#define NODS	INSN_NO_DELAY_SLOT
#define TRAP	INSN_NO_DELAY_SLOT
#define SM	INSN_STORE_MEMORY

#define WR_1	INSN_WRITE_1
#define WR_2	INSN_WRITE_2
#define RD_1	INSN_READ_1
#define RD_2	INSN_READ_2
#define RD_3	INSN_READ_3
#define RD_4	INSN_READ_4
#define MOD_1	(WR_1|RD_1)
#define MOD_2	(WR_2|RD_2)

#define WR_31   INSN_WRITE_GPR_31
#define WR_CC	INSN_WRITE_COND_CODE
#define RD_CC	INSN_READ_COND_CODE
#define RD_C0   INSN_COP
#define RD_C1	INSN_COP
#define RD_C2   INSN_COP
#define RD_C3   INSN_COP
#define WR_C0   INSN_COP
#define WR_C1	INSN_COP
#define WR_C2   INSN_COP
#define WR_C3   INSN_COP
#define UDI	INSN_UDI
#define CP	INSN_COP

#define WR_HI	INSN_WRITE_HI
#define RD_HI	INSN_READ_HI
#define MOD_HI  WR_HI|RD_HI

#define WR_LO	INSN_WRITE_LO
#define RD_LO	INSN_READ_LO
#define MOD_LO  WR_LO|RD_LO

#define WR_HILO WR_HI|WR_LO
#define RD_HILO RD_HI|RD_LO
#define MOD_HILO WR_HILO|RD_HILO

#define IS_M    INSN_MULT

#define WR_MACC INSN2_WRITE_MDMX_ACC
#define RD_MACC INSN2_READ_MDMX_ACC

#define I1	INSN_ISA1
#define I2	INSN_ISA2
#define I3	INSN_ISA3
#define I4	INSN_ISA4
#define I5	INSN_ISA5
#define I32	INSN_ISA32
#define I64     INSN_ISA64
#define I33	INSN_ISA32R2
#define I65	INSN_ISA64R2
#define I3_32   INSN_ISA3_32
#define I3_33   INSN_ISA3_32R2
#define I4_32   INSN_ISA4_32
#define I4_33   INSN_ISA4_32R2
#define I5_33   INSN_ISA5_32R2

/* MIPS64 MIPS-3D ASE support.  */
#define M3D     ASE_MIPS3D

/* MIPS32 SmartMIPS ASE support.  */
#define SMT	ASE_SMARTMIPS

/* MIPS64 MDMX ASE support.  */
#define MX      ASE_MDMX

#define IL2E    (INSN_LOONGSON_2E)
#define IL2F    (INSN_LOONGSON_2F)
#define IL3A    (INSN_LOONGSON_3A)

#define P3	INSN_4650
#define L1	INSN_4010
#define V1	(INSN_4100 | INSN_4111 | INSN_4120)
#define T3      INSN_3900
/* Emotion Engine MIPS r5900. */
#define EE      INSN_5900
#define M1	INSN_10000
#define SB1     INSN_SB1
#define N411	INSN_4111
#define N412	INSN_4120
#define N5	(INSN_5400 | INSN_5500)
#define N54	INSN_5400
#define N55	INSN_5500
#define IOCT	(INSN_OCTEON | INSN_OCTEONP | INSN_OCTEON2)
#define IOCTP	(INSN_OCTEONP | INSN_OCTEON2)
#define IOCT2	INSN_OCTEON2
#define XLR     INSN_XLR
#define IVIRT	ASE_VIRT
#define IVIRT64	ASE_VIRT64

/* Loongson AMO support.  */
#define LAMO	ASE_LOONGSON_AMO

/* Loongson CSR support.  */
#define LCSR	ASE_LOONGSON_CSR

/* Loongson EXT3 support.  */
#define LEXT3	ASE_LOONGSON_EXT3

#define G1      (T3             \
                 |EE            \
                 )

#define G2      (T3             \
                 )

#define G3      (I4             \
                 |EE            \
                 )

/* 64 bit CPU with 32 bit FPU (single float). */
#define SF	EE

/* Support for 128 bit MMI instructions. */
#define MMI	EE

/* 64 bit CPU with only 32 bit multiplication/division support. */
#define M32	EE

/* Support for VU0 Coprocessor instructions */
#define VU0	EE
#define VU0CH	INSN2_VU0_CHANNEL_SUFFIX

/* MIPS DSP ASE support.
   NOTE:
   1. MIPS DSP ASE includes 4 accumulators ($ac0 - $ac3).  $ac0 is the pair
   of original HI and LO.  $ac1, $ac2 and $ac3 are new registers, and have
   the same structure as $ac0 (HI + LO).  For DSP instructions that write or
   read accumulators (that may be $ac0), we add WR_a (WR_HILO) or RD_a
   (RD_HILO) attributes, such that HILO dependencies are maintained
   conservatively.

   2. For some mul. instructions that use integer registers as destinations
   but destroy HI+LO as side-effect, we add WR_HILO to their attributes.

   3. MIPS DSP ASE includes a new DSP control register, which has 6 fields
   (ccond, outflag, EFI, c, scount, pos).  Many DSP instructions read or write
   certain fields of the DSP control register.  For simplicity, we decide not
   to track dependencies of these fields.
   However, "bposge32" is a branch instruction that depends on the "pos"
   field.  In order to make sure that GAS does not reorder DSP instructions
   that writes the "pos" field and "bposge32", we add DSP_VOLA
   (INSN_NO_DELAY_SLOT) attribute to those instructions that write the "pos"
   field.  */

#define WR_a	WR_HILO	/* Write dsp accumulators (reuse WR_HILO)  */
#define RD_a	RD_HILO	/* Read dsp accumulators (reuse RD_HILO)  */
#define MOD_a	WR_a|RD_a
#define DSP_VOLA INSN_NO_DELAY_SLOT
#define D32	ASE_DSP
#define D33	ASE_DSPR2
#define D64	ASE_DSP64

/* MIPS MT ASE support.  */
#define MT32	ASE_MT

/* MIPS MCU (MicroController) ASE support.  */
#define MC	ASE_MCU

/* MIPS Enhanced VA Scheme.  */
#define EVA	ASE_EVA

/* TLB invalidate instruction support.  */
#define TLBINV	ASE_EVA

/* The order of overloaded instructions matters.  Label arguments and
   register arguments look the same. Instructions that can have either
   for arguments must apear in the correct order in this table for the
   assembler to pick the right one. In other words, entries with
   immediate operands must apear after the same instruction with
   registers.

   Because of the lookup algorithm used, entries with the same opcode
   name must be contiguous.
 
   Many instructions are short hand for other instructions (i.e., The
   jal <register> instruction is short for jalr <register>).  */

const struct mips_opcode mips_builtin_opcodes[] =
{
/* These instructions appear first so that the disassembler will find
   them first.  The assemblers uses a hash table based on the
   instruction name anyhow.  */
/* name,		args,		match,	    mask,	pinfo,          	pinfo2,		membership,	ase,	exclusions */
{"pref",		"k,o(b)",	0xcc000000, 0xfc000000, RD_3,           	0,		I4_32|G3,	0,	0 },
{"pref",		"k,A(b)",	0,    (int) M_PREF_AB,	INSN_MACRO,		0,		I4_32|G3,	0,	0 },
{"prefx",		"h,t(b)",	0x4c00000f, 0xfc0007ff, RD_2|RD_3|FP_S,		0,		I4_33,		0,	0 },
{"nop",			"",		0x00000000, 0xffffffff, 0,              	INSN2_ALIAS,	I1,		0,	0 }, /* sll */
{"ssnop",		"",		0x00000040, 0xffffffff, 0,              	INSN2_ALIAS,	I1,		0,	0 }, /* sll */
{"ehb",			"",		0x000000c0, 0xffffffff, 0,              	INSN2_ALIAS,	I1,		0,	0 }, /* sll */
{"li",			"t,j",		0x24000000, 0xffe00000, WR_1,			INSN2_ALIAS,	I1,		0,	0 }, /* addiu */
{"li",			"t,i",		0x34000000, 0xffe00000, WR_1,			INSN2_ALIAS,	I1,		0,	0 }, /* ori */
{"li",			"t,I",		0,    (int) M_LI,	INSN_MACRO,		0,		I1,		0,	0 },
{"move",		"d,s",		0,    (int) M_MOVE,	INSN_MACRO,		0,		I1,		0,	0 },
{"move",		"d,s",		0x0000002d, 0xfc1f07ff, WR_1|RD_2,		INSN2_ALIAS,	I3,		0,	0 },/* daddu */
{"move",		"d,s",		0x00000021, 0xfc1f07ff, WR_1|RD_2,		INSN2_ALIAS,	I1,		0,	0 },/* addu */
{"move",		"d,s",		0x00000025, 0xfc1f07ff,	WR_1|RD_2,		INSN2_ALIAS,	I1,		0,	0 },/* or */
{"b",			"p",		0x10000000, 0xffff0000,	UBD,			INSN2_ALIAS,	I1,		0,	0 },/* beq 0,0 */
{"b",			"p",		0x04010000, 0xffff0000,	UBD,			INSN2_ALIAS,	I1,		0,	0 },/* bgez 0 */
{"bal",			"p",		0x04110000, 0xffff0000,	WR_31|UBD,		INSN2_ALIAS,	I1,		0,	0 },/* bgezal 0*/

/* Loongson specific instructions.  Loongson 3A redefines the Coprocessor 2
   instructions.  Put them here so that disassembler will find them first.
   The assemblers uses a hash table based on the instruction name anyhow.  */
{"campi",		"d,s",		0x70000075, 0xfc1f07ff,	WR_1|RD_2,		0,		IL3A,		0,	0 },
{"campv",		"d,s",		0x70000035, 0xfc1f07ff,	WR_1|RD_2,		0,		IL3A,		0,	0 },
{"camwi",		"d,s,t",	0x700000b5, 0xfc0007ff,	RD_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"ramri",		"d,s",		0x700000f5, 0xfc1f07ff,	WR_1|RD_2,		0,		IL3A,		0,	0 },
{"gsle",		"s,t",		0x70000026, 0xfc00ffff,	RD_1|RD_2,		0,		IL3A,		0,	0 },
{"gsgt",		"s,t",		0x70000027, 0xfc00ffff,	RD_1|RD_2,		0,		IL3A,		0,	0 },
{"gslble",		"t,b,d",	0xc8000010, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"gslbgt",		"t,b,d",	0xc8000011, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"gslhle",		"t,b,d",	0xc8000012, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"gslhgt",		"t,b,d",	0xc8000013, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"gslwle",		"t,b,d",	0xc8000014, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"gslwgt",		"t,b,d",	0xc8000015, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"gsldle",		"t,b,d",	0xc8000016, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"gsldgt",		"t,b,d",	0xc8000017, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"gssble",		"t,b,d",	0xe8000010, 0xfc0007ff,	RD_1|RD_2|RD_3|SM,	0,		IL3A,		0,	0 },
{"gssbgt",		"t,b,d",	0xe8000011, 0xfc0007ff,	RD_1|RD_2|RD_3|SM,	0,		IL3A,		0,	0 },
{"gsshle",		"t,b,d",	0xe8000012, 0xfc0007ff,	RD_1|RD_2|RD_3|SM,	0,		IL3A,		0,	0 },
{"gsshgt",		"t,b,d",	0xe8000013, 0xfc0007ff,	RD_1|RD_2|RD_3|SM,	0,		IL3A,		0,	0 },
{"gsswle",		"t,b,d",	0xe8000014, 0xfc0007ff,	RD_1|RD_2|RD_3|SM,	0,		IL3A,		0,	0 },
{"gsswgt",		"t,b,d",	0xe8000015, 0xfc0007ff,	RD_1|RD_2|RD_3|SM,	0,		IL3A,		0,	0 },
{"gssdle",		"t,b,d",	0xe8000016, 0xfc0007ff,	RD_1|RD_2|RD_3|SM,	0,		IL3A,		0,	0 },
{"gssdgt",		"t,b,d",	0xe8000017, 0xfc0007ff,	RD_1|RD_2|RD_3|SM,	0,		IL3A,		0,	0 },
{"gslwlec1",		"T,b,d",	0xc800001c, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"gslwgtc1",		"T,b,d",	0xc800001d, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"gsldlec1",		"T,b,d",	0xc800001e, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"gsldgtc1",		"T,b,d",	0xc800001f, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"gsswlec1",		"T,b,d",	0xe800001c, 0xfc0007ff,	RD_1|RD_2|RD_3|SM,	0,		IL3A,		0,	0 },
{"gsswgtc1",		"T,b,d",	0xe800001d, 0xfc0007ff,	RD_1|RD_2|RD_3|SM,	0,		IL3A,		0,	0 },
{"gssdlec1",		"T,b,d",	0xe800001e, 0xfc0007ff,	RD_1|RD_2|RD_3|SM,	0,		IL3A,		0,	0 },
{"gssdgtc1",		"T,b,d",	0xe800001f, 0xfc0007ff,	RD_1|RD_2|RD_3|SM,	0,		IL3A,		0,	0 },
{"gslwlc1",		"T,+a(b)",	0xc8000004, 0xfc00c03f,	WR_1|RD_3|LDD,		0,		IL3A,		0,	0 },
{"gslwrc1",		"T,+a(b)",	0xc8000005, 0xfc00c03f,	WR_1|RD_3|LDD,		0,		IL3A,		0,	0 },
{"gsldlc1",		"T,+a(b)",	0xc8000006, 0xfc00c03f,	WR_1|RD_3|LDD,		0,		IL3A,		0,	0 },
{"gsldrc1",		"T,+a(b)",	0xc8000007, 0xfc00c03f,	WR_1|RD_3|LDD,		0,		IL3A,		0,	0 },
{"gsswlc1",		"T,+a(b)",	0xe8000004, 0xfc00c03f,	RD_1|RD_3|SM,		0,		IL3A,		0,	0 },
{"gsswrc1",		"T,+a(b)",	0xe8000005, 0xfc00c03f,	RD_1|RD_3|SM,		0,		IL3A,		0,	0 },
{"gssdlc1",		"T,+a(b)",	0xe8000006, 0xfc00c03f,	RD_1|RD_3|SM,		0,		IL3A,		0,	0 },
{"gssdrc1",		"T,+a(b)",	0xe8000007, 0xfc00c03f,	RD_1|RD_3|SM,		0,		IL3A,		0,	0 },
{"gslbx",		"t,+b(b,d)",	0xd8000000, 0xfc000007,	WR_1|RD_3|RD_4|LDD,	0,		IL3A,		0,	0 },
{"gslhx",		"t,+b(b,d)",	0xd8000001, 0xfc000007,	WR_1|RD_3|RD_4|LDD,	0,		IL3A,		0,	0 },
{"gslwx",		"t,+b(b,d)",	0xd8000002, 0xfc000007,	WR_1|RD_3|RD_4|LDD,	0,		IL3A,		0,	0 },
{"gsldx",		"t,+b(b,d)",	0xd8000003, 0xfc000007,	WR_1|RD_3|RD_4|LDD,	0,		IL3A,		0,	0 },
{"gssbx",		"t,+b(b,d)",	0xf8000000, 0xfc000007,	RD_1|RD_3|RD_4|SM,	0,		IL3A,		0,	0 },
{"gsshx",		"t,+b(b,d)",	0xf8000001, 0xfc000007,	RD_1|RD_3|RD_4|SM,	0,		IL3A,		0,	0 },
{"gsswx",		"t,+b(b,d)",	0xf8000002, 0xfc000007,	RD_1|RD_3|RD_4|SM,	0,		IL3A,		0,	0 },
{"gssdx",		"t,+b(b,d)",	0xf8000003, 0xfc000007,	RD_1|RD_3|RD_4|SM,	0,		IL3A,		0,	0 },
{"gslwxc1",		"T,+b(b,d)",	0xd8000006, 0xfc000007,	WR_1|RD_3|RD_4|LDD,	0,		IL3A,		0,	0 },
{"gsldxc1",		"T,+b(b,d)",	0xd8000007, 0xfc000007,	WR_1|RD_3|RD_4|LDD,	0,		IL3A,		0,	0 },
{"gsswxc1",		"T,+b(b,d)",	0xf8000006, 0xfc000007,	RD_1|RD_3|RD_4|SM,	0,		IL3A,		0,	0 },
{"gssdxc1",		"T,+b(b,d)",	0xf8000007, 0xfc000007,	RD_1|RD_3|RD_4|SM,	0,		IL3A,		0,	0 },
{"gslq",		"+z,t,+c(b)",	0xc8000020, 0xfc008020,	WR_1|WR_2|RD_4|LDD,	0,		IL3A,		0,	0 },
{"gssq",		"+z,t,+c(b)",	0xe8000020, 0xfc008020,	RD_1|RD_2|RD_4|SM,	0,		IL3A,		0,	0 },
{"gslqc1",		"+Z,T,+c(b)",	0xc8008020, 0xfc008020,	WR_1|WR_2|RD_4|LDD,	0,		IL3A,		0,	0 },
{"gssqc1",		"+Z,T,+c(b)",	0xe8008020, 0xfc008020,	RD_1|RD_2|RD_4|SM,	0,		IL3A,		0,	0 },

/* Loongson AMO */
{"amswap_sync.w",	"d,t,+d(s)",	0x70000039, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amswap_sync.d",	"d,t,+d(s)",	0x70000079, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amadd_sync.w",	"d,t,+d(s)",	0x700000b9, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amadd_sync.d",	"d,t,+d(s)",	0x700000f9, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amand_sync.w",	"d,t,+d(s)",	0x70000139, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amand_sync.d",	"d,t,+d(s)",	0x70000179, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amor_sync.w",		"d,t,+d(s)",	0x700001b9, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amor_sync.d",		"d,t,+d(s)",	0x700001f9, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amxor_sync.w",	"d,t,+d(s)",	0x70000239, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amxor_sync.d",	"d,t,+d(s)",	0x70000279, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"ammax_sync.w",	"d,t,+d(s)",	0x700002b9, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"ammax_sync.d",	"d,t,+d(s)",	0x700002f9, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"ammin_sync.w",	"d,t,+d(s)",	0x70000339, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"ammin_sync.d",	"d,t,+d(s)",	0x70000379, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"ammaxu_sync.w",	"d,t,+d(s)",	0x700003b9, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"ammaxu_sync.d",	"d,t,+d(s)",	0x700003f9, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amminu_sync.w",	"d,t,+d(s)",	0x70000439, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amminu_sync.d",	"d,t,+d(s)",	0x70000479, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amswap.w",		"d,t,+d(s)",	0x70000038, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amswap.d",		"d,t,+d(s)",	0x70000078, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amadd.w",		"d,t,+d(s)",	0x700000b8, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amadd.d",		"d,t,+d(s)",	0x700000f8, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amand.w",		"d,t,+d(s)",	0x70000138, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amand.d",		"d,t,+d(s)",	0x70000178, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amor.w",		"d,t,+d(s)",	0x700001b8, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amor.d",		"d,t,+d(s)",	0x700001f8, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amxor.w",		"d,t,+d(s)",	0x70000238, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amxor.d",		"d,t,+d(s)",	0x70000278, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"ammax.w",		"d,t,+d(s)",	0x700002b8, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"ammax.d",		"d,t,+d(s)",	0x700002f8, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"ammin.w",		"d,t,+d(s)",	0x70000338, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"ammin.d",		"d,t,+d(s)",	0x70000378, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"ammaxu.w",		"d,t,+d(s)",	0x700003b8, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"ammaxu.d",		"d,t,+d(s)",	0x700003f8, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amminu.w",		"d,t,+d(s)",	0x70000438, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
{"amminu.d",		"d,t,+d(s)",	0x70000478, 0xfc0007ff,	MOD_1|RD_2|SM,		0,		0,		LAMO,	0 },
 
/* Loongson cpucfg */
{"cpucfg",		"d,s",		0xc8080118, 0xfc1f07ff,	WR_1|RD_2|LDD,		0,		0,		LCSR,	0 },
/* Loongson csr */
{"rdcsr",		"d,s",		0xc8000118, 0xfc1f07ff,	WR_1|RD_2|LDD,		0,		0,		LCSR,	0 },
{"wrcsr",		"d,s",		0xc8010118, 0xfc1f07ff,	RD_1|RD_2|SM,		0,		0,		LCSR,	0 },
{"drdcsr",		"d,s",		0xc8020118, 0xfc1f07ff,	WR_1|RD_2|LDD,		0,		0,		LCSR,	0 },
{"dwrcsr",		"d,s",		0xc8030118, 0xfc1f07ff,	RD_1|RD_2|SM,		0,		0,		LCSR,	0 },
{"rdgcsr",		"d,s",		0xc8040118, 0xfc1f07ff,	WR_1|RD_2|LDD,		0,		0,		LCSR,	0 },
{"wrgcsr",		"d,s",		0xc8050118, 0xfc1f07ff,	RD_1|RD_2|SM,		0,		0,		LCSR,	0 },
{"drdgcsr",		"d,s",		0xc8060118, 0xfc1f07ff,	WR_1|RD_2|LDD,		0,		0,		LCSR,	0 },
{"dwrgcsr",		"d,s",		0xc8070118, 0xfc1f07ff,	RD_1|RD_2|SM,		0,		0,		LCSR,	0 },
{"dwrgcsr",		"d,s",		0xc8070118, 0xfc1f07ff,	RD_1|RD_2|SM,		0,		0,		LCSR,	0 },
{"drdtime",		"d,s",		0xc8090118, 0xfc1f07ff,	WR_1|WR_2|LDD,		0,		0,		LCSR,	0 },
{"rdtimel",		"d,s",		0xc80a0118, 0xfc1f07ff,	WR_1|WR_2|LDD,		0,		0,		LCSR,	0 },
{"rdtimeh",		"d,s",		0xc80b0118, 0xfc1f07ff,	WR_1|WR_2|LDD,		0,		0,		LCSR,	0 },

/* Loongson ext3 */
{"gsandn",		"d,s,t",	0x70000483, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		0,		LEXT3,	0 },
{"gsorn",		"d,s,t",	0x70000486, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		0,		LEXT3,	0 },
{"gsmulth",		"d,s,t",	0x7000001a, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		0,		LEXT3,	0 },
{"gsmulthu",		"d,s,t",	0x7000001b, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		0,		LEXT3,	0 },
{"gsdmulth",		"d,s,t",	0x70000018, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		0,		LEXT3,	0 },
{"gsdmulthu",		"d,s,t",	0x70000019, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		0,		LEXT3,	0 },
{"gsldpc",		"d",		0x7000002b, 0xffff07ff,	WR_1|LDD,		0,		0,		LEXT3,	0 },
{"gsdaui",		"t,s,u",	0x74000000, 0xfc000000,	WR_1|RD_2,		0,		0,		LEXT3,	0 },

/* Loongson spw */
{"lddir",		"t,s,h",	0xc8000098, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"lwdir",		"t,s,h",	0xc8000018, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	0,		IL3A,		0,	0 },
{"ldpte",		"s,h",		0xc80000d8, 0xfc1f07ff,	WR_1|RD_2|LDD,		0,		IL3A,		0,	0 },
{"lwpte",		"s,h",		0xc8000058, 0xfc1f07ff,	WR_1|RD_2|LDD,		0,		IL3A,		0,	0 },

/* R5900 VU0 Macromode instructions. */
{"vabs",		"+7+K,+6+K",	  0x4a0001fd, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vadd",		"+5+K,+6+K,+7+K", 0x4a000028, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vaddi",		"+5+K,+6+K,+y",	  0x4a000022, 0xfe1f003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vaddq",		"+5+K,+6+K,+q",	  0x4a000020, 0xfe1f003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vaddw",		"+5+K,+6+K,+7+N", 0x4a000003, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vaddx",		"+5+K,+6+K,+7+N", 0x4a000000, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vaddy",		"+5+K,+6+K,+7+N", 0x4a000001, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vaddz",		"+5+K,+6+K,+7+N", 0x4a000002, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vadda",		"+m+K,+7+K,+6+K", 0x4a0002bc, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vaddai",		"+m+K,+6+K,+y",	  0x4a00023e, 0xfe1f07ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vaddaq",		"+m+K,+6+K,+q",	  0x4a00023c, 0xfe1f07ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vaddaw",		"+m+K,+6+K,+7+N", 0x4a00003f, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vaddax",		"+m+K,+6+K,+7+N", 0x4a00003c, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vadday",		"+m+K,+6+K,+7+N", 0x4a00003d, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vaddaz",		"+m+K,+6+K,+7+N", 0x4a00003e, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vcallms",		"+f",		  0x4a000038, 0xffe0003f,	CP,		0,		VU0,		0,	0 },
{"vcallmsr",		"+9",		  0x4a000039, 0xffff07ff,	CP,		0,		VU0,		0,	0 },
{"vclipw.xyz",		"+6+K,+7+N",	  0x4bc001ff, 0xffe007ff,	CP,		0,		VU0,		0,	0 },
{"vclipw",		"+6+K,+7+N",	  0x4bc001ff, 0xffe007ff,	CP,		0,		VU0,		0,	0 },
{"vdiv",		"+q,+6+L,+7+M",	  0x4a0003bc, 0xfe0007ff,	CP,		0,		VU0,		0,	0 },
{"vftoi0",		"+7+K,+6+K",	  0x4a00017c, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vftoi4",		"+7+K,+6+K",	  0x4a00017d, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vftoi12",		"+7+K,+6+K",	  0x4a00017e, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vftoi15",		"+7+K,+6+K",	  0x4a00017f, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"viadd",		"+8,+9,+0",	  0x4a000030, 0xffe0003f,	CP,		0,		VU0,		0,	0 },
{"viaddi",		"+0,+9,+g",	  0x4a000032, 0xffe0003f,	CP,		0,		VU0,		0,	0 },
{"viand",		"+8,+9,+0",	  0x4a000034, 0xffe0003f,	CP,		0,		VU0,		0,	0 },
{"vilwr.w",		"+0,(+9)",	  0x4a2003fe, 0xffe007ff,	CP,		0,		VU0,		0,	0 },
{"vilwr.x",		"+0,(+9)",	  0x4b0003fe, 0xffe007ff,	CP,		0,		VU0,		0,	0 },
{"vilwr.y",		"+0,(+9)",	  0x4a8003fe, 0xffe007ff,	CP,		0,		VU0,		0,	0 },
{"vilwr.z",		"+0,(+9)",	  0x4a4003fe, 0xffe007ff,	CP,		0,		VU0,		0,	0 },
{"vior",		"+8,+9,+0",	  0x4a000035, 0xffe0003f,	CP,		0,		VU0,		0,	0 },
{"viswr.w",		"+0,(+9)",	  0x4a2003ff, 0xffe007ff,	CP,		0,		VU0,		0,	0 },
{"viswr.x",		"+0,(+9)",	  0x4b0003ff, 0xffe007ff,	CP,		0,		VU0,		0,	0 },
{"viswr.y",		"+0,(+9)",	  0x4a8003ff, 0xffe007ff,	CP,		0,		VU0,		0,	0 },
{"viswr.z",		"+0,(+9)",	  0x4a4003ff, 0xffe007ff,	CP,		0,		VU0,		0,	0 },
{"visub",		"+8,+9,+0",	  0x4a000031, 0xffe0003f,	CP,		0,		VU0,		0,	0 },
{"vitof0",		"+7+K,+6+K",	  0x4a00013c, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vitof4",		"+7+K,+6+K",	  0x4a00013d, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vitof12",		"+7+K,+6+K",	  0x4a00013e, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vitof15",		"+7+K,+6+K",	  0x4a00013f, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vlqd",		"+7+K,(#-+9)",	  0x4a00037e, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vlqi",		"+7+K,(+9#+)",	  0x4a00037c, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmadd",		"+5+K,+6+K,+7+K", 0x4a000029, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaddi",		"+5+K,+6+K,+y",	  0x4a000023, 0xfe1f003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaddq",		"+5+K,+6+K,+q",	  0x4a000021, 0xfe1f003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaddw",		"+5+K,+6+K,+7+N", 0x4a00000b, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaddx",		"+5+K,+6+K,+7+N", 0x4a000008, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaddy",		"+5+K,+6+K,+7+N", 0x4a000009, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaddz",		"+5+K,+6+K,+7+N", 0x4a00000a, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmadda",		"+m+K,+6+K,+7+K", 0x4a0002bd, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaddai",		"+m+K,+6+K,+y",	  0x4a00023f, 0xfe1f07ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaddaq",		"+m+K,+6+K,+q",	  0x4a00023d, 0xfe1f07ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaddaw",		"+m+K,+6+K,+7+N", 0x4a0000bf, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaddax",		"+m+K,+6+K,+7+N", 0x4a0000bc, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmadday",		"+m+K,+6+K,+7+N", 0x4a0000bd, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaddaz",		"+m+K,+6+K,+7+N", 0x4a0000be, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmax",		"+5+K,+6+K,+7+K", 0x4a00002b, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaxi",		"+5+K,+6+K,+y",	  0x4a00001d, 0xfe1f003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaxw",		"+5+K,+6+K,+7+N", 0x4a000013, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaxx",		"+5+K,+6+K,+7+N", 0x4a000010, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaxy",		"+5+K,+6+K,+7+N", 0x4a000011, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmaxz",		"+5+K,+6+K,+7+N", 0x4a000012, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmfir",		"+7+K,+9",	  0x4a0003fd, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmini",		"+5+K,+6+K,+7+K", 0x4a00002f, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vminii",		"+5+K,+6+K,+y",	  0x4a00001f, 0xfe1f003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vminiw",		"+5+K,+6+K,+7+N", 0x4a000017, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vminix",		"+5+K,+6+K,+7+N", 0x4a000014, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vminiy",		"+5+K,+6+K,+7+N", 0x4a000015, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vminiz",		"+5+K,+6+K,+7+N", 0x4a000016, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmove",		"+7+K,+6+K",	  0x4a00033c, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmr32",		"+7+K,+6+K",	  0x4a00033d, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsub",		"+5+K,+6+K,+7+K", 0x4a00002d, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsubi",		"+5+K,+6+K,+y",	  0x4a000027, 0xfe1f003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsubq",		"+5+K,+6+K,+q",	  0x4a000025, 0xfe1f003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsubw",		"+5+K,+6+K,+7+N", 0x4a00000f, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsubx",		"+5+K,+6+K,+7+N", 0x4a00000c, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsuby",		"+5+K,+6+K,+7+N", 0x4a00000d, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsubz",		"+5+K,+6+K,+7+N", 0x4a00000e, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsuba",		"+m+K,+7+K,+6+K", 0x4a0002fd, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsubai",		"+m+K,+6+K,+y",	  0x4a00027f, 0xfe1f07ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsubaq",		"+m+K,+6+K,+q",	  0x4a00027d, 0xfe1f07ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsubaw",		"+m+K,+6+K,+7+N", 0x4a0000ff, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsubax",		"+m+K,+6+K,+7+N", 0x4a0000fc, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsubay",		"+m+K,+6+K,+7+N", 0x4a0000fd, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmsubaz",		"+m+K,+6+K,+7+N", 0x4a0000fe, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmtir",		"+0,+6+L",	  0x4a0003fc, 0xff8007ff,	CP,		0,		VU0,		0,	0 },
{"vmul",		"+5+K,+6+K,+7+K", 0x4a00002a, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmuli",		"+5+K,+6+K,+y",	  0x4a00001e, 0xfe1f003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmulq",		"+5+K,+6+K,+q",	  0x4a00001c, 0xfe1f003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmulw",		"+5+K,+6+K,+7+N", 0x4a00001b, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmulx",		"+5+K,+6+K,+7+N", 0x4a000018, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmuly",		"+5+K,+6+K,+7+N", 0x4a000019, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmulz",		"+5+K,+6+K,+7+N", 0x4a00001a, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vmula",		"+m+K,+6+K,+7+K", 0x4a0002be, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmulai",		"+m+K,+6+K,+y",	  0x4a0001fe, 0xfe1f07ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmulaq",		"+m+K,+6+K,+q",	  0x4a0001fc, 0xfe1f07ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmulaw",		"+m+K,+6+K,+7+N", 0x4a0001bf, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmulax",		"+m+K,+6+K,+7+N", 0x4a0001bc, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmulay",		"+m+K,+6+K,+7+N", 0x4a0001bd, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vmulaz",		"+m+K,+6+K,+7+N", 0x4a0001be, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vnop",		"",		  0x4a0002ff, 0xffffffff,	CP,		0,		VU0,		0,	0 },
{"vopmula.xyz",		"+m+K,+6+K,+7+K", 0x4bc002fe, 0xffe007ff,	CP,		0,		VU0,		0,	0 },
{"vopmula",		"+m+K,+6+K,+7+K", 0x4bc002fe, 0xffe007ff,	CP,		0,		VU0,		0,	0 },
{"vopmsub.xyz",		"+5+K,+6+K,+7+K", 0x4bc0002e, 0xffe0003f,	CP,		0,		VU0,		0,	0 },
{"vopmsub",		"+5+K,+6+K,+7+K", 0x4bc0002e, 0xffe0003f,	CP,		0,		VU0,		0,	0 },
{"vrget",		"+7+K,+r",	  0x4a00043d, 0xfe00ffff,	CP,		VU0CH,		VU0,		0,	0 },
{"vrinit",		"+r,+6+L",	  0x4a00043e, 0xff9f07ff,	CP,		0,		VU0,		0,	0 },
{"vrnext",		"+7+K,+r",	  0x4a00043c, 0xfe00ffff,	CP,		VU0CH,		VU0,		0,	0 },
{"vrsqrt",		"+q,+6+L,+7+M",	  0x4a0003be, 0xfe0007ff,	CP,		0,		VU0,		0,	0 },
{"vrxor",		"+r,+6+L",	  0x4a00043f, 0xff9f07ff,	CP,		0,		VU0,		0,	0 },
{"vsqd",		"+6+K,(#-+0)",	  0x4a00037f, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vsqi",		"+6+K,(+0#+)",	  0x4a00037d, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vsqrt",		"+q,+7+M",	  0x4a2003bd, 0xfe60ffff,	CP,		0,		VU0,		0,	0 },
{"vsub",		"+5+K,+6+K,+7+K", 0x4a00002c, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vsubi",		"+5+K,+6+K,+y",	  0x4a000026, 0xfe1f003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vsubq",		"+5+K,+6+K,+q",	  0x4a000024, 0xfe1f003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vsubw",		"+5+K,+6+K,+7+N", 0x4a000007, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vsubx",		"+5+K,+6+K,+7+N", 0x4a000004, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vsuby",		"+5+K,+6+K,+7+N", 0x4a000005, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vsubz",		"+5+K,+6+K,+7+N", 0x4a000006, 0xfe00003f,	CP,		VU0CH,		VU0,		0,	0 },
{"vsuba",		"+m+K,+6+K,+7+K", 0x4a0002fc, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vsubai",		"+m+K,+6+K,+y",	  0x4a00027e, 0xfe1f07ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vsubaq",		"+m+K,+6+K,+q",	  0x4a00027c, 0xfe1f07ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vsubaw",		"+m+K,+6+K,+7+N", 0x4a00007f, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vsubax",		"+m+K,+6+K,+7+N", 0x4a00007c, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vsubay",		"+m+K,+6+K,+7+N", 0x4a00007d, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vsubaz",		"+m+K,+6+K,+7+N", 0x4a00007e, 0xfe0007ff,	CP,		VU0CH,		VU0,		0,	0 },
{"vwaitq",		"",		  0x4a0003bf, 0xffffffff,	CP,		0,		VU0,		0,	0 },

{"abs",			"d,v",		0,    (int) M_ABS,	INSN_MACRO,		0,		I1,		0,	0 },
{"abs.s",		"D,V",		0x46000005, 0xffff003f,	WR_1|RD_2|FP_S,		0,		I1,		0,	0 },
{"abs.d",		"D,V",		0x46200005, 0xffff003f,	WR_1|RD_2|FP_D,		0,		I1,		0,	SF },
{"abs.ps",		"D,V",		0x46c00005, 0xffff003f,	WR_1|RD_2|FP_D,		0,		I5_33|IL2F,	0,	0 },
{"abs.ps",		"D,V",		0x45600005, 0xffff003f,	WR_1|RD_2|FP_D,		0,		IL2E,		0,	0 },
{"aclr",		"\\,~(b)",	0x04070000, 0xfc1f8000,	RD_3|SM|NODS,		0,		0,		MC,	0 },
{"aclr",		"\\,A(b)",	0,    (int) M_ACLR_AB,	INSN_MACRO,		0,		0,		MC,	0 },
{"add",			"d,v,t",	0x00000020, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"add",			"t,r,I",	0,    (int) M_ADD_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"add",			"D,S,T",	0x45c00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2E,		0,	0 },
{"add",			"D,S,T",	0x4b40000c, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2F|IL3A,	0,	0 },
{"add.s",		"D,V,T",	0x46000000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		I1,		0,	0 },
{"add.d",		"D,V,T",	0x46200000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		I1,		0,	SF },
{"add.ob",		"X,Y,Q",	0x7800000b, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"add.ob",		"D,S,Q",	0x4800000b, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"add.ps",		"D,V,T",	0x46c00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"add.ps",		"D,V,T",	0x45600000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"add.qh",		"X,Y,Q",	0x7820000b, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"adda.ob",		"Y,Q",		0x78000037, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	SB1,		MX,	0 },
{"adda.qh",		"Y,Q",		0x78200037, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	0,		MX,	0 },
{"adda.s",		"S,T",		0x46000018, 0xffe007ff,	RD_1|RD_2|FP_S,		0,		EE,		0,	0 },
{"addi",		"t,r,j",	0x20000000, 0xfc000000,	WR_1|RD_2,		0,		I1,		0,	0 },
{"addiu",		"t,r,j",	0x24000000, 0xfc000000,	WR_1|RD_2,		0,		I1,		0,	0 },
{"addl.ob",		"Y,Q",		0x78000437, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	SB1,		MX,	0 },
{"addl.qh",		"Y,Q",		0x78200437, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	0,		MX,	0 },
{"addr.ps",		"D,S,T",	0x46c00018, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		M3D,	0 },
{"addu",		"d,v,t",	0x00000021, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"addu",		"t,r,I",	0,    (int) M_ADDU_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"addu",		"D,S,T",	0x45800000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2E,		0,	0 },
{"addu",		"D,S,T",	0x4b00000c, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2F|IL3A,	0,	0 },
{"alni.ob",		"X,Y,Z,O",	0x78000018, 0xff00003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"alni.ob",		"D,S,T,%",	0x48000018, 0xff00003f,	WR_1|RD_2|RD_3|FP_D, 	0,		N54,		0,	0 },
{"alni.qh",		"X,Y,Z,O",	0x7800001a, 0xff00003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"alnv.ps",		"D,V,T,s",	0x4c00001e, 0xfc00003f,	WR_1|RD_2|RD_3|RD_4|FP_D, 0,		I5_33,		0,	0 },
{"alnv.ob",		"X,Y,Z,s",	0x78000019, 0xfc00003f,	WR_1|RD_2|RD_3|RD_4|FP_D, 0,		SB1,		MX,	0 },
{"alnv.qh",		"X,Y,Z,s",	0x7800001b, 0xfc00003f,	WR_1|RD_2|RD_3|RD_4|FP_D, 0,		0,		MX,	0 },
{"and",			"d,v,t",	0x00000024, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"and",			"t,r,I",	0,    (int) M_AND_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"and",			"D,S,T",	0x47c00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"and",			"D,S,T",	0x4bc00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"and.ob",		"X,Y,Q",	0x7800000c, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"and.ob",		"D,S,Q",	0x4800000c, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"and.qh",		"X,Y,Q",	0x7820000c, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"andi",		"t,r,i",	0x30000000, 0xfc000000,	WR_1|RD_2,		0,		I1,		0,	0 },
{"aset",		"\\,~(b)",	0x04078000, 0xfc1f8000,	RD_3|SM|NODS,		0,		0,		MC,	0 },
{"aset",		"\\,A(b)",	0,    (int) M_ASET_AB,	INSN_MACRO,		0,		0,		MC,	0 },
{"baddu",		"d,v,t",	0x70000028, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		IOCT,		0,	0 },
/* b is at the top of the table.  */
/* bal is at the top of the table.  */
{"bbit032",		"s,+x,p",	0xd8000000, 0xfc000000, RD_1|CBD,		0,		IOCT,		0,	0 },
{"bbit0",		"s,+X,p",	0xd8000000, 0xfc000000, RD_1|CBD,		0,		IOCT,		0,	0 }, /* bbit032 */
{"bbit0",		"s,+x,p",	0xc8000000, 0xfc000000, RD_1|CBD,		0,		IOCT,		0,	0 },
{"bbit132",		"s,+x,p",	0xf8000000, 0xfc000000, RD_1|CBD,		0,		IOCT,		0,	0 },
{"bbit1",		"s,+X,p",	0xf8000000, 0xfc000000, RD_1|CBD,		0,		IOCT,		0,	0 }, /* bbit132 */
{"bbit1",		"s,+x,p",	0xe8000000, 0xfc000000, RD_1|CBD,		0,		IOCT,		0,	0 },
/* bc0[tf]l? are at the bottom of the table.  */
{"bc1any2f",		"N,p",		0x45200000, 0xffe30000,	RD_CC|CBD|FP_S,		0,		0,		M3D,	0 },
{"bc1any2t",		"N,p",		0x45210000, 0xffe30000,	RD_CC|CBD|FP_S,		0,		0,		M3D,	0 },
{"bc1any4f",		"N,p",		0x45400000, 0xffe30000,	RD_CC|CBD|FP_S,		0,		0,		M3D,	0 },
{"bc1any4t",		"N,p",		0x45410000, 0xffe30000,	RD_CC|CBD|FP_S,		0,		0,		M3D,	0 },
{"bc1f",		"p",		0x45000000, 0xffff0000,	RD_CC|CBD|FP_S,		0,		I1,		0,	0 },
{"bc1f",		"N,p",		0x45000000, 0xffe30000, RD_CC|CBD|FP_S, 	0,		I4_32,		0,	0 },
{"bc1fl",		"p",		0x45020000, 0xffff0000,	RD_CC|CBL|FP_S,		0,		I2|T3,		0,	0 },
{"bc1fl",		"N,p",		0x45020000, 0xffe30000, RD_CC|CBL|FP_S, 	0,		I4_32,		0,	0 },
{"bc1t",		"p",		0x45010000, 0xffff0000,	RD_CC|CBD|FP_S,		0,		I1,		0,	0 },
{"bc1t",		"N,p",		0x45010000, 0xffe30000, RD_CC|CBD|FP_S, 	0,		I4_32,		0,	0 },
{"bc1tl",		"p",		0x45030000, 0xffff0000,	RD_CC|CBL|FP_S,		0,		I2|T3,		0,	0 },
{"bc1tl",		"N,p",		0x45030000, 0xffe30000, RD_CC|CBL|FP_S, 	0,		I4_32,		0,	0 },
/* bc2* are at the bottom of the table.  */
/* bc3* are at the bottom of the table.  */
{"beqz",		"s,p",		0x10000000, 0xfc1f0000,	RD_1|CBD,		0,		I1,		0,	0 },
{"beqzl",		"s,p",		0x50000000, 0xfc1f0000,	RD_1|CBL,		0,		I2|T3,		0,	0 },
{"beq",			"s,t,p",	0x10000000, 0xfc000000,	RD_1|RD_2|CBD,		0,		I1,		0,	0 },
{"beq",			"s,I,p",	0,    (int) M_BEQ_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"beql",		"s,t,p",	0x50000000, 0xfc000000,	RD_1|RD_2|CBL,		0,		I2|T3,		0,	0 },
{"beql",		"s,I,p",	0,    (int) M_BEQL_I,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bge",			"s,t,p",	0,    (int) M_BGE,	INSN_MACRO,		0,		I1,		0,	0 },
{"bge",			"s,I,p",	0,    (int) M_BGE_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"bgel",		"s,t,p",	0,    (int) M_BGEL,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bgel",		"s,I,p",	0,    (int) M_BGEL_I,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bgeu",		"s,t,p",	0,    (int) M_BGEU,	INSN_MACRO,		0,		I1,		0,	0 },
{"bgeu",		"s,I,p",	0,    (int) M_BGEU_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"bgeul",		"s,t,p",	0,    (int) M_BGEUL,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bgeul",		"s,I,p",	0,    (int) M_BGEUL_I,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bgez",		"s,p",		0x04010000, 0xfc1f0000,	RD_1|CBD,		0,		I1,		0,	0 },
{"bgezl",		"s,p",		0x04030000, 0xfc1f0000,	RD_1|CBL,		0,		I2|T3,		0,	0 },
{"bgezal",		"s,p",		0x04110000, 0xfc1f0000,	RD_1|WR_31|CBD,		0,		I1,		0,	0 },
{"bgezall",		"s,p",		0x04130000, 0xfc1f0000,	RD_1|WR_31|CBL,		0,		I2|T3,		0,	0 },
{"bgt",			"s,t,p",	0,    (int) M_BGT,	INSN_MACRO,		0,		I1,		0,	0 },
{"bgt",			"s,I,p",	0,    (int) M_BGT_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"bgtl",		"s,t,p",	0,    (int) M_BGTL,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bgtl",		"s,I,p",	0,    (int) M_BGTL_I,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bgtu",		"s,t,p",	0,    (int) M_BGTU,	INSN_MACRO,		0,		I1,		0,	0 },
{"bgtu",		"s,I,p",	0,    (int) M_BGTU_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"bgtul",		"s,t,p",	0,    (int) M_BGTUL,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bgtul",		"s,I,p",	0,    (int) M_BGTUL_I,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bgtz",		"s,p",		0x1c000000, 0xfc1f0000,	RD_1|CBD,		0,		I1,		0,	0 },
{"bgtzl",		"s,p",		0x5c000000, 0xfc1f0000,	RD_1|CBL,		0,		I2|T3,		0,	0 },
{"ble",			"s,t,p",	0,    (int) M_BLE,	INSN_MACRO,		0,		I1,		0,	0 },
{"ble",			"s,I,p",	0,    (int) M_BLE_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"blel",		"s,t,p",	0,    (int) M_BLEL,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"blel",		"s,I,p",	0,    (int) M_BLEL_I,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bleu",		"s,t,p",	0,    (int) M_BLEU,	INSN_MACRO,		0,		I1,		0,	0 },
{"bleu",		"s,I,p",	0,    (int) M_BLEU_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"bleul",		"s,t,p",	0,    (int) M_BLEUL,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bleul",		"s,I,p",	0,    (int) M_BLEUL_I,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"blez",		"s,p",		0x18000000, 0xfc1f0000,	RD_1|CBD,		0,		I1,		0,	0 },
{"blezl",		"s,p",		0x58000000, 0xfc1f0000,	RD_1|CBL,		0,		I2|T3,		0,	0 },
{"blt",			"s,t,p",	0,    (int) M_BLT,	INSN_MACRO,		0,		I1,		0,	0 },
{"blt",			"s,I,p",	0,    (int) M_BLT_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"bltl",		"s,t,p",	0,    (int) M_BLTL,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bltl",		"s,I,p",	0,    (int) M_BLTL_I,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bltu",		"s,t,p",	0,    (int) M_BLTU,	INSN_MACRO,		0,		I1,		0,	0 },
{"bltu",		"s,I,p",	0,    (int) M_BLTU_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"bltul",		"s,t,p",	0,    (int) M_BLTUL,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bltul",		"s,I,p",	0,    (int) M_BLTUL_I,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"bltz",		"s,p",		0x04000000, 0xfc1f0000,	RD_1|CBD,		0,		I1,		0,	0 },
{"bltzl",		"s,p",		0x04020000, 0xfc1f0000,	RD_1|CBL,		0,		I2|T3,		0,	0 },
{"bltzal",		"s,p",		0x04100000, 0xfc1f0000,	RD_1|WR_31|CBD,		0,		I1,		0,	0 },
{"bltzall",		"s,p",		0x04120000, 0xfc1f0000,	RD_1|WR_31|CBL,		0,		I2|T3,		0,	0 },
{"bnez",		"s,p",		0x14000000, 0xfc1f0000,	RD_1|CBD,		0,		I1,		0,	0 },
{"bnezl",		"s,p",		0x54000000, 0xfc1f0000,	RD_1|CBL,		0,		I2|T3,		0,	0 },
{"bne",			"s,t,p",	0x14000000, 0xfc000000,	RD_1|RD_2|CBD,		0,		I1,		0,	0 },
{"bne",			"s,I,p",	0,    (int) M_BNE_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"bnel",		"s,t,p",	0x54000000, 0xfc000000,	RD_1|RD_2|CBL, 		0,		I2|T3,		0,	0 },
{"bnel",		"s,I,p",	0,    (int) M_BNEL_I,	INSN_MACRO,		0,		I2|T3,		0,	0 },
{"break",		"",		0x0000000d, 0xffffffff,	TRAP,			0,		I1,		0,	0 },
{"break",		"c",		0x0000000d, 0xfc00ffff,	TRAP,			0,		I1,		0,	0 },
{"break",		"c,q",		0x0000000d, 0xfc00003f,	TRAP,			0,		I1,		0,	0 },
{"c.f.d",		"S,T",		0x46200030, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.f.d",		"M,S,T",	0x46200030, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.f.s",		"S,T",      	0x46000030, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	0 },
{"c.f.s",		"M,S,T",	0x46000030, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.f.ps",		"S,T",		0x46c00030, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.f.ps",		"S,T",		0x45600030, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.f.ps",		"M,S,T",	0x46c00030, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.un.d",		"S,T",		0x46200031, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.un.d",		"M,S,T",	0x46200031, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.un.s",		"S,T",		0x46000031, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	EE },
{"c.un.s",		"M,S,T",	0x46000031, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.un.ps",		"S,T",		0x46c00031, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.un.ps",		"S,T",		0x45600031, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.un.ps",		"M,S,T",	0x46c00031, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.eq.d",		"S,T",		0x46200032, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.eq.d",		"M,S,T",	0x46200032, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.eq.s",		"S,T",		0x46000032, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	0 },
{"c.eq.s",		"M,S,T",	0x46000032, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.eq.ob",		"Y,Q",		0x78000001, 0xfc2007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		SB1,		MX,	0 },
{"c.eq.ob",		"S,Q",		0x48000001, 0xfc2007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		N54,		0,	0 },
{"c.eq.ps",		"S,T",		0x46c00032, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.eq.ps",		"S,T",		0x45600032, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.eq.ps",		"M,S,T",	0x46c00032, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.eq.qh",		"Y,Q",		0x78200001, 0xfc2007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		0,		MX,	0 },
{"c.ueq.d",		"S,T",		0x46200033, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.ueq.d",		"M,S,T",	0x46200033, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.ueq.s",		"S,T",		0x46000033, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	EE },
{"c.ueq.s",		"M,S,T",	0x46000033, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.ueq.ps",		"S,T",		0x46c00033, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.ueq.ps",		"S,T",		0x45600033, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.ueq.ps",		"M,S,T",	0x46c00033, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.olt.d",		"S,T",		0x46200034, 0xffe007ff, RD_1|RD_2|WR_CC|FP_D,   0,		I1,		0,	SF },
{"c.olt.d",		"M,S,T",	0x46200034, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.olt.s",		"S,T",		0x46000034, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_S,	0,		I1,		0,	EE },
{"c.olt.s",		"M,S,T",	0x46000034, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.olt.ps",		"S,T",		0x46c00034, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.olt.ps",		"S,T",		0x45600034, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.olt.ps",		"M,S,T",	0x46c00034, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.ult.d",		"S,T",		0x46200035, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.ult.d",		"M,S,T",	0x46200035, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.ult.s",		"S,T",		0x46000035, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	EE },
{"c.ult.s",		"M,S,T",	0x46000035, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.ult.ps",		"S,T",		0x46c00035, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.ult.ps",		"S,T",		0x45600035, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.ult.ps",		"M,S,T",	0x46c00035, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.ole.d",		"S,T",		0x46200036, 0xffe007ff, RD_1|RD_2|WR_CC|FP_D,   0,		I1,		0,	SF },
{"c.ole.d",		"M,S,T",	0x46200036, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.ole.s",		"S,T",		0x46000036, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	EE },
{"c.ole.s",		"M,S,T",	0x46000036, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.ole.ps",		"S,T",		0x46c00036, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.ole.ps",		"S,T",		0x45600036, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.ole.ps",		"M,S,T",	0x46c00036, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.ule.d",		"S,T",		0x46200037, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.ule.d",		"M,S,T",	0x46200037, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.ule.s",		"S,T",		0x46000037, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	EE },
{"c.ule.s",		"M,S,T",	0x46000037, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.ule.ps",		"S,T",		0x46c00037, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.ule.ps",		"S,T",		0x45600037, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.ule.ps",		"M,S,T",	0x46c00037, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.sf.d",		"S,T",		0x46200038, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.sf.d",		"M,S,T",	0x46200038, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.sf.s",		"S,T",		0x46000038, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	EE },
{"c.sf.s",		"M,S,T",	0x46000038, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.sf.ps",		"S,T",		0x46c00038, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.sf.ps",		"S,T",		0x45600038, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.sf.ps",		"M,S,T",	0x46c00038, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.ngle.d",		"S,T",		0x46200039, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.ngle.d",		"M,S,T",	0x46200039, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.ngle.s",		"S,T",		0x46000039, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	EE },
{"c.ngle.s",		"M,S,T",	0x46000039, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.ngle.ps",		"S,T",		0x46c00039, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.ngle.ps",		"S,T",		0x45600039, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.ngle.ps",		"M,S,T",	0x46c00039, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.seq.d",		"S,T",		0x4620003a, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.seq.d",		"M,S,T",	0x4620003a, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.seq.s",		"S,T",		0x4600003a, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	EE },
{"c.seq.s",		"M,S,T",	0x4600003a, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.seq.ps",		"S,T",		0x46c0003a, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.seq.ps",		"S,T",		0x4560003a, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.seq.ps",		"M,S,T",	0x46c0003a, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.ngl.d",		"S,T",		0x4620003b, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.ngl.d",		"M,S,T",	0x4620003b, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.ngl.s",		"S,T",		0x4600003b, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	EE },
{"c.ngl.s",		"M,S,T",	0x4600003b, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.ngl.ps",		"S,T",		0x46c0003b, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.ngl.ps",		"S,T",		0x4560003b, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.ngl.ps",		"M,S,T",	0x46c0003b, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.lt.d",		"S,T",		0x4620003c, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.lt.d",		"M,S,T",	0x4620003c, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.lt.s",		"S,T",		0x46000034, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_S,	0,		EE,		0,	0 },
{"c.lt.s",		"S,T",		0x4600003c, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_S,	0,		I1,		0,	EE },
{"c.lt.s",		"M,S,T",	0x4600003c, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.lt.ob",		"Y,Q",		0x78000004, 0xfc2007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		SB1,		MX,	0 },
{"c.lt.ob",		"S,Q",		0x48000004, 0xfc2007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		N54,		0,	0 },
{"c.lt.ps",		"S,T",		0x46c0003c, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.lt.ps",		"S,T",		0x4560003c, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.lt.ps",		"M,S,T",	0x46c0003c, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.lt.qh",		"Y,Q",		0x78200004, 0xfc2007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		0,		MX,	0 },
{"c.nge.d",		"S,T",		0x4620003d, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.nge.d",		"M,S,T",	0x4620003d, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.nge.s",		"S,T",		0x4600003d, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	EE },
{"c.nge.s",		"M,S,T",	0x4600003d, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.nge.ps",		"S,T",		0x46c0003d, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.nge.ps",		"S,T",		0x4560003d, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.nge.ps",		"M,S,T",	0x46c0003d, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.le.d",		"S,T",		0x4620003e, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.le.d",		"M,S,T",	0x4620003e, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.le.s",		"S,T",		0x46000036, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_S,	0,		EE,		0,	0 },
{"c.le.s",		"S,T",		0x4600003e, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_S,	0,		I1,		0,	EE },
{"c.le.s",		"M,S,T",	0x4600003e, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.le.ob",		"Y,Q",		0x78000005, 0xfc2007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		SB1,		MX,	0 },
{"c.le.ob",		"S,Q",		0x48000005, 0xfc2007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		N54,		0,	0 },
{"c.le.ps",		"S,T",		0x46c0003e, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.le.ps",		"S,T",		0x4560003e, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.le.ps",		"M,S,T",	0x46c0003e, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"c.le.qh",		"Y,Q",		0x78200005, 0xfc2007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		0,		MX,	0 },
{"c.ngt.d",		"S,T",		0x4620003f, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I1,		0,	SF },
{"c.ngt.d",		"M,S,T",	0x4620003f, 0xffe000ff, RD_2|RD_3|WR_CC|FP_D,   0,		I4_32,		0,	0 },
{"c.ngt.s",		"S,T",		0x4600003f, 0xffe007ff, RD_1|RD_2|WR_CC|FP_S,   0,		I1,		0,	EE },
{"c.ngt.s",		"M,S,T",	0x4600003f, 0xffe000ff, RD_2|RD_3|WR_CC|FP_S,   0,		I4_32,		0,	0 },
{"c.ngt.ps",		"S,T",		0x46c0003f, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"c.ngt.ps",		"S,T",		0x4560003f, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"c.ngt.ps",		"M,S,T",	0x46c0003f, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		I5_33,		0,	0 },
{"cabs.eq.d",		"M,S,T",	0x46200072, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.eq.ps",		"M,S,T",	0x46c00072, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.eq.s",		"M,S,T",	0x46000072, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.f.d",		"M,S,T",	0x46200070, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.f.ps",		"M,S,T",	0x46c00070, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.f.s",		"M,S,T",	0x46000070, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.le.d",		"M,S,T",	0x4620007e, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.le.ps",		"M,S,T",	0x46c0007e, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.le.s",		"M,S,T",	0x4600007e, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.lt.d",		"M,S,T",	0x4620007c, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.lt.ps",		"M,S,T",	0x46c0007c, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.lt.s",		"M,S,T",	0x4600007c, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.nge.d",		"M,S,T",	0x4620007d, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.nge.ps",		"M,S,T",	0x46c0007d, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.nge.s",		"M,S,T",	0x4600007d, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.ngl.d",		"M,S,T",	0x4620007b, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ngl.ps",		"M,S,T",	0x46c0007b, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ngl.s",		"M,S,T",	0x4600007b, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.ngle.d",		"M,S,T",	0x46200079, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ngle.ps",	"M,S,T",	0x46c00079, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ngle.s",		"M,S,T",	0x46000079, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.ngt.d",		"M,S,T",	0x4620007f, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ngt.ps",		"M,S,T",	0x46c0007f, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ngt.s",		"M,S,T",	0x4600007f, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.ole.d",		"M,S,T",	0x46200076, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ole.ps",		"M,S,T",	0x46c00076, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ole.s",		"M,S,T",	0x46000076, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.olt.d",		"M,S,T",	0x46200074, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.olt.ps",		"M,S,T",	0x46c00074, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.olt.s",		"M,S,T",	0x46000074, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.seq.d",		"M,S,T",	0x4620007a, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.seq.ps",		"M,S,T",	0x46c0007a, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.seq.s",		"M,S,T",	0x4600007a, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.sf.d",		"M,S,T",	0x46200078, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.sf.ps",		"M,S,T",	0x46c00078, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.sf.s",		"M,S,T",	0x46000078, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.ueq.d",		"M,S,T",	0x46200073, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ueq.ps",		"M,S,T",	0x46c00073, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ueq.s",		"M,S,T",	0x46000073, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.ule.d",		"M,S,T",	0x46200077, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ule.ps",		"M,S,T",	0x46c00077, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ule.s",		"M,S,T",	0x46000077, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.ult.d",		"M,S,T",	0x46200075, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ult.ps",		"M,S,T",	0x46c00075, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.ult.s",		"M,S,T",	0x46000075, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
{"cabs.un.d",		"M,S,T",	0x46200071, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.un.ps",		"M,S,T",	0x46c00071, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_D,	0,		0,		M3D,	0 },
{"cabs.un.s",		"M,S,T",	0x46000071, 0xffe000ff,	RD_2|RD_3|WR_CC|FP_S,	0,		0,		M3D,	0 },
/* CW4010 instructions which are aliases for the cache instruction.  */
{"flushi",		"",		0xbc010000, 0xffffffff, 0,			0,		L1,		0,	0 },
{"flushd",		"",		0xbc020000, 0xffffffff, 0, 			0,		L1,		0,	0 },
{"flushid",		"",		0xbc030000, 0xffffffff, 0, 			0,		L1,		0,	0 },
{"wb",			"o(b)",		0xbc040000, 0xfc1f0000, RD_2|SM,		0,		L1,		0,	0 },
{"cache",		"k,o(b)",	0xbc000000, 0xfc000000, RD_3,           	0,		I3_32|T3,	0,	0},
{"cache",		"k,A(b)",	0,    (int) M_CACHE_AB, INSN_MACRO,		0,		I3_32|T3,	0,	0},
{"ceil.l.d",		"D,S",		0x4620000a, 0xffff003f, WR_1|RD_2|FP_D,		0,		I3_33,		0,	0 },
{"ceil.l.s",		"D,S",		0x4600000a, 0xffff003f, WR_1|RD_2|FP_S|FP_D,	0,		I3_33,		0,	0 },
{"ceil.w.d",		"D,S",		0x4620000e, 0xffff003f, WR_1|RD_2|FP_S|FP_D,	0,		I2,		0,	SF },
{"ceil.w.s",		"D,S",		0x4600000e, 0xffff003f, WR_1|RD_2|FP_S,		0,		I2,		0,	EE },
{"cfc0",		"t,G",		0x40400000, 0xffe007ff,	WR_1|RD_C0|LCD,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"cfc1",		"t,G",		0x44400000, 0xffe007ff,	WR_1|RD_C1|LCD|FP_S,	0,		I1,		0,	0 },
{"cfc1",		"t,S",		0x44400000, 0xffe007ff,	WR_1|RD_C1|LCD|FP_S,	0,		I1,		0,	0 },
/* cfc2 is at the bottom of the table.  */
/* cfc3 is at the bottom of the table.  */
{"cftc1",		"d,E",		0x41000023, 0xffe007ff, WR_1|RD_C1|TRAP|LCD|FP_S, 0,		0,		MT32,	0 },
{"cftc1",		"d,T",		0x41000023, 0xffe007ff, WR_1|RD_C1|TRAP|LCD|FP_S, 0,		0,		MT32,	0 },
{"cftc2",		"d,E",		0x41000025, 0xffe007ff,	WR_1|RD_C2|TRAP|LCD,	0,		0,		MT32,	IOCT|IOCTP|IOCT2 },
{"cins32",		"t,r,+p,+s",	0x70000033, 0xfc00003f, WR_1|RD_2,		0,		IOCT,		0,	0 },
{"cins",		"t,r,+P,+S",	0x70000033, 0xfc00003f, WR_1|RD_2,		0,		IOCT,		0,	0 }, /* cins32 */
{"cins",		"t,r,+p,+S",	0x70000032, 0xfc00003f, WR_1|RD_2,		0,		IOCT,		0,	0 },
{"clo",			"U,s",		0x70000021, 0xfc0007ff, WR_1|RD_2, 	0,		I32|N55,	0,	0 },
{"clz",			"U,s",		0x70000020, 0xfc0007ff, WR_1|RD_2, 	0,		I32|N55,	0,	0 },
{"ctc0",		"t,G",		0x40c00000, 0xffe007ff,	RD_1|WR_CC|COD,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"ctc1",		"t,G",		0x44c00000, 0xffe007ff,	RD_1|WR_CC|COD|FP_S,	0,		I1,		0,	0 },
{"ctc1",		"t,S",		0x44c00000, 0xffe007ff,	RD_1|WR_CC|COD|FP_S,	0,		I1,		0,	0 },
/* ctc2 is at the bottom of the table.  */
/* ctc3 is at the bottom of the table.  */
{"cttc1",		"t,g",		0x41800023, 0xffe007ff, RD_1|WR_CC|TRAP|COD|FP_S, 0,		0,		MT32,	0 },
{"cttc1",		"t,S",		0x41800023, 0xffe007ff, RD_1|WR_CC|TRAP|COD|FP_S, 0,		0,		MT32,	0 },
{"cttc2",		"t,g",		0x41800025, 0xffe007ff,	RD_1|WR_CC|TRAP|COD,	0,		0,		MT32,	IOCT|IOCTP|IOCT2 },
{"cvt.d.l",		"D,S",		0x46a00021, 0xffff003f,	WR_1|RD_2|FP_D,		0,		I3_33,		0,	0 },
{"cvt.d.s",		"D,S",		0x46000021, 0xffff003f,	WR_1|RD_2|FP_S|FP_D,	0,		I1,		0,	SF },
{"cvt.d.w",		"D,S",		0x46800021, 0xffff003f,	WR_1|RD_2|FP_S|FP_D,	0,		I1,		0,	SF },
{"cvt.l.d",		"D,S",		0x46200025, 0xffff003f,	WR_1|RD_2|FP_D,		0,		I3_33,		0,	0 },
{"cvt.l.s",		"D,S",		0x46000025, 0xffff003f,	WR_1|RD_2|FP_S|FP_D,	0,		I3_33,		0,	0 },
{"cvt.s.l",		"D,S",		0x46a00020, 0xffff003f,	WR_1|RD_2|FP_S|FP_D,	0,		I3_33,		0,	0 },
{"cvt.s.d",		"D,S",		0x46200020, 0xffff003f,	WR_1|RD_2|FP_S|FP_D,	0,		I1,		0,	SF },
{"cvt.s.w",		"D,S",		0x46800020, 0xffff003f,	WR_1|RD_2|FP_S,		0,		I1,		0,	0 },
{"cvt.s.pl",		"D,S",		0x46c00028, 0xffff003f,	WR_1|RD_2|FP_S|FP_D,	0,		I5_33,		0,	0 },
{"cvt.s.pu",		"D,S",		0x46c00020, 0xffff003f,	WR_1|RD_2|FP_S|FP_D,	0,		I5_33,		0,	0 },
{"cvt.w.d",		"D,S",		0x46200024, 0xffff003f,	WR_1|RD_2|FP_S|FP_D,	0,		I1,		0,	SF },
{"cvt.w.s",		"D,S",		0x46000024, 0xffff003f,	WR_1|RD_2|FP_S,		0,		I1,		0,	EE },
{"cvt.ps.pw",		"D,S",		0x46800026, 0xffff003f,	WR_1|RD_2|FP_S|FP_D,	0,		0,		M3D,	0 },
{"cvt.ps.s",		"D,V,T",	0x46000026, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S|FP_D, 0,		I5_33,		0,	0 },
{"cvt.pw.ps",		"D,S",		0x46c00024, 0xffff003f,	WR_1|RD_2|FP_S|FP_D,	0,		0,		M3D,	0 },
{"dabs",		"d,v",		0,    (int) M_DABS,	INSN_MACRO,		0,		I3,		0,	0 },
{"dadd",		"d,v,t",	0x0000002c, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		I3,		0,	0 },
{"dadd",		"t,r,I",	0,    (int) M_DADD_I,	INSN_MACRO,		0,		I3,		0,	0 },
{"dadd",		"D,S,T",	0x45e00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"dadd",		"D,S,T",	0x4b60000c, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"daddi",		"t,r,j",	0x60000000, 0xfc000000, WR_1|RD_2,		0,		I3,		0,	0 },
{"daddiu",		"t,r,j",	0x64000000, 0xfc000000, WR_1|RD_2,		0,		I3,		0,	0 },
{"daddu",		"d,v,t",	0x0000002d, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		I3,		0,	0 },
{"daddu",		"t,r,I",	0,    (int) M_DADDU_I,	INSN_MACRO,		0,		I3,		0,	0 },
{"daddwc",		"d,s,t", 	0x70000038, 0xfc0007ff, WR_1|RD_2|RD_3|WR_C0|RD_C0, 0,		XLR,		0,	0 },
{"dbreak",		"",		0x7000003f, 0xffffffff,	0,			0,		N5,		0,	0 },
{"dclo",		"U,s",	 	0x70000025, 0xfc0007ff, WR_1|RD_2, 	0,		I64|N55,	0,	0 },
{"dclz",		"U,s",	 	0x70000024, 0xfc0007ff, WR_1|RD_2, 	0,		I64|N55,	0,	0 },
/* dctr and dctw are used on the r5000.  */
{"dctr",		"o(b)",	 	0xbc050000, 0xfc1f0000, RD_2,			0,		I3,		0,	0 },
{"dctw",		"o(b)",		0xbc090000, 0xfc1f0000, RD_2,			0,		I3,		0,	0 },
{"deret",		"",		0x4200001f, 0xffffffff, NODS, 			0,		I32|G2,		0,	0 },
{"dext",		"t,r,+A,+H",	0x7c000003, 0xfc00003f, WR_1|RD_2,    		0,		I65,		0,	0 },
{"dext",		"t,r,+A,+G",	0x7c000001, 0xfc00003f, WR_1|RD_2,    		0,		I65,		0,	0 }, /* dextm */
{"dext",		"t,r,+E,+H",	0x7c000002, 0xfc00003f, WR_1|RD_2,    		0,		I65,		0,	0 }, /* dextu */
{"dextm",		"t,r,+A,+G",	0x7c000001, 0xfc00003f, WR_1|RD_2,    		0,		I65,		0,	0 },
{"dextu",		"t,r,+E,+H",	0x7c000002, 0xfc00003f, WR_1|RD_2,    		0,		I65,		0,	0 },
/* For ddiv, see the comments about div.  */
{"ddiv",		"z,s,t",	0x0000001e, 0xfc00ffff, RD_2|RD_3|WR_HILO,      0,		I3,		0,	M32 },
{"ddiv",		"d,v,t",	0,    (int) M_DDIV_3,	INSN_MACRO,		0,		I3,		0,	M32 },
{"ddiv",		"d,v,I",	0,    (int) M_DDIV_3I,	INSN_MACRO,		0,		I3,		0,	M32 },
/* For ddivu, see the comments about div.  */
{"ddivu",		"z,s,t",	0x0000001f, 0xfc00ffff, RD_2|RD_3|WR_HILO,      0,		I3,		0,	M32 },
{"ddivu",		"d,v,t",	0,    (int) M_DDIVU_3,	INSN_MACRO,		0,		I3,		0,	M32 },
{"ddivu",		"d,v,I",	0,    (int) M_DDIVU_3I,	INSN_MACRO,		0,		I3,		0,	M32 },
{"di",			"",		0x42000039, 0xffffffff,	WR_C0,			0,		EE,		0,	0 },
{"di",			"",		0x41606000, 0xffffffff,	WR_C0,			0,		I33,		0,	0 },
{"di",			"t",		0x41606000, 0xffe0ffff,	WR_1|WR_C0,		0,		I33,		0,	0 },
{"dins",		"t,r,+A,+B",	0x7c000007, 0xfc00003f, WR_1|RD_2,    		0,		I65,		0,	0 },
{"dins",		"t,r,+A,+F",	0x7c000005, 0xfc00003f, WR_1|RD_2,    		0,		I65,		0,	0 }, /* dinsm */
{"dins",		"t,r,+E,+F",	0x7c000006, 0xfc00003f, WR_1|RD_2,    		0,		I65,		0,	0 }, /* dinsu */
{"dinsm",		"t,r,+A,+F",	0x7c000005, 0xfc00003f, WR_1|RD_2,    		0,		I65,		0,	0 },
{"dinsu",		"t,r,+E,+F",	0x7c000006, 0xfc00003f, WR_1|RD_2,    		0,		I65,		0,	0 },
/* The MIPS assembler treats the div opcode with two operands as
   though the first operand appeared twice (the first operand is both
   a source and a destination).  To get the div machine instruction,
   you must use an explicit destination of $0.  */
{"div",			"z,s,t",	0x0000001a, 0xfc00ffff, RD_2|RD_3|WR_HILO,      0,		I1,		0,	0 },
{"div",			"z,t",		0x0000001a, 0xffe0ffff, RD_2|WR_HILO,		0,		I1,		0,	0 },
{"div",			"d,v,t",	0,    (int) M_DIV_3,	INSN_MACRO,		0,		I1,		0,	0 },
{"div",			"d,v,I",	0,    (int) M_DIV_3I,	INSN_MACRO,		0,		I1,		0,	0 },
{"div1",		"z,s,t",	0x7000001a, 0xfc00ffff, RD_2|RD_3|WR_HILO,      0,		EE,		0,	0 },
{"div1",		"z,t",		0x7000001a, 0xffe0ffff, RD_2|WR_HILO,		0,		EE,		0,	0 },
{"div.d",		"D,V,T",	0x46200003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		I1,		0,	SF },
{"div.s",		"D,V,T",	0x46000003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		I1,		0,	0 },
{"div.ps",		"D,V,T",	0x46c00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		0,	0 },
/* For divu, see the comments about div.  */
{"divu",		"z,s,t",	0x0000001b, 0xfc00ffff, RD_2|RD_3|WR_HILO,      0,		I1,		0,	0 },
{"divu",		"z,t",		0x0000001b, 0xffe0ffff, RD_2|WR_HILO,		0,		I1,		0,	0 },
{"divu",		"d,v,t",	0,    (int) M_DIVU_3,	INSN_MACRO,		0,		I1,		0,	0 },
{"divu",		"d,v,I",	0,    (int) M_DIVU_3I,	INSN_MACRO,		0,		I1,		0,	0 },
{"divu1",		"z,s,t",	0x7000001b, 0xfc00ffff, RD_2|RD_3|WR_HILO,      0,		EE,		0,	0 },
{"divu1",		"z,t",		0x7000001b, 0xffe0ffff, RD_2|WR_HILO,		0,		EE,		0,	0 },
{"dla",			"t,A(b)",	0,    (int) M_DLA_AB,	INSN_MACRO,		0,		I3,		0,	0 },
{"dlca",		"t,A(b)",	0,    (int) M_DLCA_AB,	INSN_MACRO,		0,		I3,		0,	0 },
{"dli",			"t,j",		0x24000000, 0xffe00000, WR_1,			0,		I3,		0,	0 }, /* addiu */
{"dli",			"t,i",		0x34000000, 0xffe00000, WR_1,			0,		I3,		0,	0 }, /* ori */
{"dli",			"t,I",		0,    (int) M_DLI,	INSN_MACRO,		0,		I3,		0,	0 },
{"dmacc",		"d,s,t",	0x00000029, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_LO,	0,		N412,		0,	0 },
{"dmacchi",		"d,s,t",	0x00000229, 0xfc0007ff, WR_1|RD_2|RD_3|WR_LO,	0,		N412,		0,	0 },
{"dmacchis",		"d,s,t",	0x00000629, 0xfc0007ff, WR_1|RD_2|RD_3|WR_LO,	0,		N412,		0,	0 },
{"dmacchiu",		"d,s,t",	0x00000269, 0xfc0007ff, WR_1|RD_2|RD_3|WR_LO,	0,		N412,		0,	0 },
{"dmacchius",		"d,s,t",	0x00000669, 0xfc0007ff, WR_1|RD_2|RD_3|WR_LO,	0,		N412,		0,	0 },
{"dmaccs",		"d,s,t",	0x00000429, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_LO,	0,		N412,		0,	0 },
{"dmaccu",		"d,s,t",	0x00000069, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_LO,	0,		N412,		0,	0 },
{"dmaccus",		"d,s,t",	0x00000469, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_LO,	0,		N412,		0,	0 },
{"dmadd16",		"s,t",		0x00000029, 0xfc00ffff, RD_1|RD_2|MOD_LO,       0,		N411,		0,	0 },
{"dmfc0",		"t,G",		0x40200000, 0xffe007ff,	WR_1|RD_C0|LCD,		0,		I3,		0,	EE },
{"dmfc0",		"t,G,H",	0x40200000, 0xffe007f8,	WR_1|RD_C0|LCD,		0,		I64,		0,	0 },
{"dmfgc0",		"t,G",		0x40600100, 0xffe007ff, WR_1|RD_C0|LCD,		0,		0,		IVIRT64, 0 },
{"dmfgc0",		"t,G,H",	0x40600100, 0xffe007f8, WR_1|RD_C0|LCD, 	0,		0,		IVIRT64, 0 },
{"dmt",			"",		0x41600bc1, 0xffffffff, TRAP,			0,		0,		MT32,	0 },
{"dmt",			"t",		0x41600bc1, 0xffe0ffff, WR_1|TRAP,		0,		0,		MT32,	0 },
{"dmtc0",		"t,G",		0x40a00000, 0xffe007ff,	RD_1|WR_C0|WR_CC|COD,	0,		I3,		0,	EE },
{"dmtc0",		"t,G,H",	0x40a00000, 0xffe007f8,	RD_1|WR_C0|WR_CC|COD,	0,		I64,		0,	0 },
{"dmtgc0",		"t,G",		0x40600300, 0xffe007ff, RD_1|WR_C0|WR_CC|COD,	0,		0,		IVIRT64, 0 },
{"dmtgc0",		"t,G,H",	0x40600300, 0xffe007f8, RD_1|WR_C0|WR_CC|COD,   0,		0,		IVIRT64, 0 },
{"dmfc1",		"t,S",		0x44200000, 0xffe007ff, WR_1|RD_2|LCD|FP_D,	0,		I3,		0,	SF },
{"dmfc1",		"t,G",		0x44200000, 0xffe007ff, WR_1|RD_2|LCD|FP_D,     0,		I3,		0,	SF },
{"dmtc1",		"t,S",		0x44a00000, 0xffe007ff, RD_1|WR_2|COD|FP_D,	0,		I3,		0,	SF },
{"dmtc1",		"t,G",		0x44a00000, 0xffe007ff, RD_1|WR_2|COD|FP_D,     0,		I3,		0,	SF },
/* dmfc2 is at the bottom of the table.  */
/* dmtc2 is at the bottom of the table.  */
/* dmfc3 is at the bottom of the table.  */
/* dmtc3 is at the bottom of the table.  */
{"dmul",		"d,v,t",	0x70000003, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	0,		IOCT,		0,	0 },
{"dmul",		"d,v,t",	0,    (int) M_DMUL,	INSN_MACRO,		0,		I3,		0,	M32 },
{"dmul",		"d,v,I",	0,    (int) M_DMUL_I,	INSN_MACRO,		0,		I3,		0,	M32 },
{"dmulo",		"d,v,t",	0,    (int) M_DMULO,	INSN_MACRO,		0,		I3,		0,	M32 },
{"dmulo",		"d,v,I",	0,    (int) M_DMULO_I,	INSN_MACRO,		0,		I3,		0,	M32 },
{"dmulou",		"d,v,t",	0,    (int) M_DMULOU,	INSN_MACRO,		0,		I3,		0,	M32 },
{"dmulou",		"d,v,I",	0,    (int) M_DMULOU_I,	INSN_MACRO,		0,		I3,		0,	M32 },
{"dmult",		"s,t",		0x0000001c, 0xfc00ffff, RD_1|RD_2|WR_HILO,      0,		I3,		0,	M32 },
{"dmultu",		"s,t",		0x0000001d, 0xfc00ffff, RD_1|RD_2|WR_HILO,      0,		I3,		0,	M32 },
{"dneg",		"d,w",		0x0000002e, 0xffe007ff,	WR_1|RD_2,		0,		I3,		0,	0 }, /* dsub 0 */
{"dnegu",		"d,w",		0x0000002f, 0xffe007ff,	WR_1|RD_2,		0,		I3,		0,	0 }, /* dsubu 0*/
{"dpop",		"d,v",		0x7000002d, 0xfc1f07ff, WR_1|RD_2,		0,		IOCT,		0,	0 },
{"drem",		"z,s,t",	0x0000001e, 0xfc00ffff, RD_2|RD_3|WR_HILO,      0,		I3,		0,	M32 },
{"drem",		"d,v,t",	0,    (int) M_DREM_3,	INSN_MACRO,		0,		I3,		0,	M32 },
{"drem",		"d,v,I",	0,    (int) M_DREM_3I,	INSN_MACRO,		0,		I3,		0,	M32 },
{"dremu",		"z,s,t",	0x0000001f, 0xfc00ffff, RD_2|RD_3|WR_HILO,      0,		I3,		0,	M32 },
{"dremu",		"d,v,t",	0,    (int) M_DREMU_3,	INSN_MACRO,		0,		I3,		0,	M32 },
{"dremu",		"d,v,I",	0,    (int) M_DREMU_3I,	INSN_MACRO,		0,		I3,		0,	M32 },
{"dret",		"",		0x7000003e, 0xffffffff,	0,			0,		N5,		0,	0 },
{"drol",		"d,v,t",	0,    (int) M_DROL,	INSN_MACRO,		0,		I3,		0,	0 },
{"drol",		"d,v,I",	0,    (int) M_DROL_I,	INSN_MACRO,		0,		I3,		0,	0 },
{"dror",		"d,v,t",	0,    (int) M_DROR,	INSN_MACRO,		0,		I3,		0,	0 },
{"dror",		"d,v,I",	0,    (int) M_DROR_I,	INSN_MACRO,		0,		I3,		0,	0 },
{"dror",		"d,w,<",	0x0020003a, 0xffe0003f,	WR_1|RD_2,		0,		N5|I65,		0,	0 },
{"drorv",		"d,t,s",	0x00000056, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		N5|I65,		0,	0 },
{"dror32",		"d,w,<",	0x0020003e, 0xffe0003f,	WR_1|RD_2,		0,		N5|I65,		0,	0 },
{"drotl",		"d,v,t",	0,    (int) M_DROL,	INSN_MACRO,		0,		I65,		0,	0 },
{"drotl",		"d,v,I",	0,    (int) M_DROL_I,	INSN_MACRO,		0,		I65,		0,	0 },
{"drotr",		"d,v,t",	0,    (int) M_DROR,	INSN_MACRO,		0,		I65,		0,	0 },
{"drotr",		"d,v,I",	0,    (int) M_DROR_I,	INSN_MACRO,		0,		I65,		0,	0 },
{"drotrv",		"d,t,s",	0x00000056, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I65,		0,	0 },
{"drotr32",		"d,w,<",	0x0020003e, 0xffe0003f,	WR_1|RD_2,		0,		I65,		0,	0 },
{"dsbh",		"d,w",		0x7c0000a4, 0xffe007ff,	WR_1|RD_2,		0,		I65,		0,	0 },
{"dshd",		"d,w",		0x7c000164, 0xffe007ff,	WR_1|RD_2,		0,		I65,		0,	0 },
{"dsllv",		"d,t,s",	0x00000014, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I3,		0,	0 },
{"dsll32",		"d,w,<",	0x0000003c, 0xffe0003f, WR_1|RD_2,		0,		I3,		0,	0 },
{"dsll",		"d,w,s",	0x00000014, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I3,		0,	0 }, /* dsllv */
{"dsll",		"d,w,>",	0x0000003c, 0xffe0003f, WR_1|RD_2,		0,		I3,		0,	0 }, /* dsll32 */
{"dsll",		"d,w,<",	0x00000038, 0xffe0003f,	WR_1|RD_2,		0,		I3,		0,	0 },
{"dsll",		"D,S,T",	0x45a00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"dsll",		"D,S,T",	0x4b20000e, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"dsrav",		"d,t,s",	0x00000017, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I3,		0,	0 },
{"dsra32",		"d,w,<",	0x0000003f, 0xffe0003f, WR_1|RD_2,		0,		I3,		0,	0 },
{"dsra",		"d,w,s",	0x00000017, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I3,		0,	0 }, /* dsrav */
{"dsra",		"d,w,>",	0x0000003f, 0xffe0003f, WR_1|RD_2,		0,		I3,		0,	0 }, /* dsra32 */
{"dsra",		"d,w,<",	0x0000003b, 0xffe0003f,	WR_1|RD_2,		0,		I3,		0,	0 },
{"dsra",		"D,S,T",	0x45e00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"dsra",		"D,S,T",	0x4b60000f, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"dsrlv",		"d,t,s",	0x00000016, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I3,		0,	0 },
{"dsrl32",		"d,w,<",	0x0000003e, 0xffe0003f, WR_1|RD_2,		0,		I3,		0,	0 },
{"dsrl",		"d,w,s",	0x00000016, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I3,		0,	0 }, /* dsrlv */
{"dsrl",		"d,w,>",	0x0000003e, 0xffe0003f, WR_1|RD_2,		0,		I3,		0,	0 }, /* dsrl32 */
{"dsrl",		"d,w,<",	0x0000003a, 0xffe0003f,	WR_1|RD_2,		0,		I3,		0,	0 },
{"dsrl",		"D,S,T",	0x45a00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"dsrl",		"D,S,T",	0x4b20000f, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"dsub",		"d,v,t",	0x0000002e, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I3,		0,	0 },
{"dsub",		"d,v,I",	0,    (int) M_DSUB_I,	INSN_MACRO,		0,		I3,		0,	0 },
{"dsub",		"D,S,T",	0x45e00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"dsub",		"D,S,T",	0x4b60000d, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"dsubu",		"d,v,t",	0x0000002f, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I3,		0,	0 },
{"dsubu",		"d,v,I",	0,    (int) M_DSUBU_I,	INSN_MACRO,		0,		I3,		0,	0 },
{"dvpe",		"",		0x41600001, 0xffffffff, TRAP,			0,		0,		MT32,	0 },
{"dvpe",		"t",		0x41600001, 0xffe0ffff, WR_1|TRAP,		0,		0,		MT32,	0 },
{"ei",			"",		0x42000038, 0xffffffff,	WR_C0,			0,		EE,		0,	0 },
{"ei",			"",		0x41606020, 0xffffffff,	WR_C0,			0,		I33,		0,	0 },
{"ei",			"t",		0x41606020, 0xffe0ffff,	WR_1|WR_C0,		0,		I33,		0,	0 },
{"emt",			"",		0x41600be1, 0xffffffff, TRAP,			0,		0,		MT32,	0 },
{"emt",			"t",		0x41600be1, 0xffe0ffff, WR_1|TRAP,		0,		0,		MT32,	0 },
{"eret",		"",		0x42000018, 0xffffffff, NODS,      		0,		I3_32,		0,	0 },
{"evpe",		"",		0x41600021, 0xffffffff, TRAP,			0,		0,		MT32,	0 },
{"evpe",		"t",		0x41600021, 0xffe0ffff, WR_1|TRAP,		0,		0,		MT32,	0 },
{"ext",			"t,r,+A,+C",	0x7c000000, 0xfc00003f, WR_1|RD_2,    		0,		I33,		0,	0 },
{"exts32",		"t,r,+p,+s",	0x7000003b, 0xfc00003f, WR_1|RD_2,		0,		IOCT,		0,	0 },
{"exts",		"t,r,+P,+S",	0x7000003b, 0xfc00003f, WR_1|RD_2,		0,		IOCT,		0,	0 }, /* exts32 */
{"exts",		"t,r,+p,+S",	0x7000003a, 0xfc00003f, WR_1|RD_2,		0,		IOCT,		0,	0 },
{"floor.l.d",		"D,S",		0x4620000b, 0xffff003f, WR_1|RD_2|FP_D,		0,		I3_33,		0,	0 },
{"floor.l.s",		"D,S",		0x4600000b, 0xffff003f, WR_1|RD_2|FP_S|FP_D,	0,		I3_33,		0,	0 },
{"floor.w.d",		"D,S",		0x4620000f, 0xffff003f, WR_1|RD_2|FP_S|FP_D,	0,		I2,		0,	SF },
{"floor.w.s",		"D,S",		0x4600000f, 0xffff003f, WR_1|RD_2|FP_S,		0,		I2,		0,	0 },
{"hibernate",		"",		0x42000023, 0xffffffff,	0, 			0,		V1,		0,	0 },
{"hypcall",		"",		0x42000028, 0xffffffff, TRAP,			0,		0,		IVIRT,	0 },
{"hypcall",		"+J",		0x42000028, 0xffe007ff, TRAP,			0,		0,		IVIRT,	0 },
{"ins",			"t,r,+A,+B",	0x7c000004, 0xfc00003f, WR_1|RD_2,    		0,		I33,		0,	0 },
{"iret",		"",		0x42000038, 0xffffffff,	NODS,			0,		0,		MC,	0 },
{"jr",			"s",		0x00000008, 0xfc1fffff,	RD_1|UBD,		0,		I1,		0,	0 },
/* jr.hb is officially MIPS{32,64}R2, but it works on R1 as jr with
   the same hazard barrier effect.  */
{"jr.hb",		"s",		0x00000408, 0xfc1fffff,	RD_1|UBD,		0,		I32,		0,	0 },
{"j",			"s",		0x00000008, 0xfc1fffff,	RD_1|UBD,		0,		I1,		0,	0 }, /* jr */
/* SVR4 PIC code requires special handling for j, so it must be a
   macro.  */
{"j",			"a",		0,     (int) M_J_A,	INSN_MACRO,		0,		I1,		0,	0 },
/* This form of j is used by the disassembler and internally by the
   assembler, but will never match user input (because the line above
   will match first).  */
{"j",			"a",		0x08000000, 0xfc000000,	UBD,			0,		I1,		0,	0 },
{"jalr",		"s",		0x0000f809, 0xfc1fffff,	RD_1|WR_31|UBD,		0,		I1,		0,	0 },
{"jalr",		"d,s",		0x00000009, 0xfc1f07ff,	WR_1|RD_2|UBD,		0,		I1,		0,	0 },
/* jalr.hb is officially MIPS{32,64}R2, but it works on R1 as jalr
   with the same hazard barrier effect.  */
{"jalr.hb",		"s",		0x0000fc09, 0xfc1fffff,	RD_1|WR_31|UBD,		0,		I32,		0,	0 },
{"jalr.hb",		"d,s",		0x00000409, 0xfc1f07ff,	WR_1|RD_2|UBD,		0,		I32,		0,	0 },
/* SVR4 PIC code requires special handling for jal, so it must be a
   macro.  */
{"jal",			"d,s",		0,     (int) M_JAL_2,	INSN_MACRO,		0,		I1,		0,	0 },
{"jal",			"s",		0,     (int) M_JAL_1,	INSN_MACRO,		0,		I1,		0,	0 },
{"jal",			"a",		0,     (int) M_JAL_A,	INSN_MACRO,		0,		I1,		0,	0 },
/* This form of jal is used by the disassembler and internally by the
   assembler, but will never match user input (because the line above
   will match first).  */
{"jal",			"a",		0x0c000000, 0xfc000000,	WR_31|UBD,		0,		I1,		0,	0 },
{"jalx",		"+i",		0x74000000, 0xfc000000, WR_31|UBD,		0,		I1,		0,	0 },
{"la",			"t,A(b)",	0,    (int) M_LA_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"laa",			"d,(b),t",	0x7000049f, 0xfc0007ff, WR_1|RD_2|RD_3|LDD|SM,	0,		IOCT2,		0,	0 },
{"laad",		"d,(b),t",	0x700004df, 0xfc0007ff, WR_1|RD_2|RD_3|LDD|SM,	0,		IOCT2,		0,	0 },
{"lac",			"d,(b)",	0x7000039f, 0xfc1f07ff, WR_1|RD_2|LDD|SM,	0,		IOCT2,		0,	0 },
{"lacd",		"d,(b)",	0x700003df, 0xfc1f07ff, WR_1|RD_2|LDD|SM,	0,		IOCT2,		0,	0 },
{"lad",			"d,(b)",	0x7000019f, 0xfc1f07ff, WR_1|RD_2|LDD|SM,	0,		IOCT2,		0,	0 },
{"ladd",		"d,(b)",	0x700001df, 0xfc1f07ff, WR_1|RD_2|LDD|SM,	0,		IOCT2,		0,	0 },
{"lai",			"d,(b)",	0x7000009f, 0xfc1f07ff, WR_1|RD_2|LDD|SM,	0,		IOCT2,		0,	0 },
{"laid",		"d,(b)",	0x700000df, 0xfc1f07ff, WR_1|RD_2|LDD|SM,	0,		IOCT2,		0,	0 },
{"las",			"d,(b)",	0x7000029f, 0xfc1f07ff, WR_1|RD_2|LDD|SM,	0,		IOCT2,		0,	0 },
{"lasd",		"d,(b)",	0x700002df, 0xfc1f07ff, WR_1|RD_2|LDD|SM,	0,		IOCT2,		0,	0 },
{"law",			"d,(b),t",	0x7000059f, 0xfc0007ff, WR_1|RD_2|RD_3|LDD|SM,	0,		IOCT2,		0,	0 },
{"lawd",		"d,(b),t",	0x700005df, 0xfc0007ff, WR_1|RD_2|RD_3|LDD|SM,	0,		IOCT2,		0,	0 },
{"lb",			"t,o(b)",	0x80000000, 0xfc000000,	WR_1|RD_3|LDD,		0,		I1,		0,	0 },
{"lb",			"t,A(b)",	0,    (int) M_LB_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"lbu",			"t,o(b)",	0x90000000, 0xfc000000,	WR_1|RD_3|LDD,		0,		I1,		0,	0 },
{"lbu",			"t,A(b)",	0,    (int) M_LBU_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"lbx",			"d,t(b)",	0x7c00058a, 0xfc0007ff, WR_1|RD_2|RD_3|LDD,	0,		IOCT2,		0,	0 },
{"lbux",		"d,t(b)",	0x7c00018a, 0xfc0007ff, WR_1|RD_2|RD_3|LDD,	0,		IOCT2,		D32,	0},
{"ldx",			"d,t(b)",	0x7c00020a, 0xfc0007ff, WR_1|RD_2|RD_3|LDD,	0,		IOCT2,		D64,	0},
{"lhx",			"d,t(b)",	0x7c00010a, 0xfc0007ff, WR_1|RD_2|RD_3|LDD,	0,		IOCT2,		D32,	0},
{"lhux",		"d,t(b)",	0x7c00050a, 0xfc0007ff, WR_1|RD_2|RD_3|LDD,	0,		IOCT2,		0,	0 },
{"lwx",			"d,t(b)",	0x7c00000a, 0xfc0007ff, WR_1|RD_2|RD_3|LDD,	0,		IOCT2,		D32,	0},
{"lwux",		"d,t(b)",	0x7c00040a, 0xfc0007ff, WR_1|RD_2|RD_3|LDD,	0,		IOCT2,		0,	0 },
{"lca",			"t,A(b)",	0,    (int) M_LCA_AB,	INSN_MACRO,		0,		I1,		0,	0 },
/* The macro has to be first to handle o32 correctly.  */
{"ld",			"t,A(b)",	0,    (int) M_LD_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"ld",			"t,o(b)",	0xdc000000, 0xfc000000, WR_1|RD_3|LDD,		0,		I3,		0,	0 },
{"ldaddw",		"t,b",		0x70000010, 0xfc00ffff,	MOD_1|RD_2|SM,		0,		XLR,		0,	0 },
{"ldaddwu",		"t,b",		0x70000011, 0xfc00ffff,	MOD_1|RD_2|SM,		0,		XLR,		0,	0 },
{"ldaddd",		"t,b",		0x70000012, 0xfc00ffff,	MOD_1|RD_2|SM,		0,		XLR,		0,	0 },
{"ldc1",		"T,o(b)",	0xd4000000, 0xfc000000, WR_1|RD_3|CLD|FP_D,	0,		I2,		0,	SF },
{"ldc1",		"E,o(b)",	0xd4000000, 0xfc000000, WR_1|RD_3|CLD|FP_D,	0,		I2,		0,	SF },
{"ldc1",		"T,A(b)",	0,    (int) M_LDC1_AB,	INSN_MACRO,		INSN2_M_FP_D,	I2,		0,	SF },
{"ldc1",		"E,A(b)",	0,    (int) M_LDC1_AB,	INSN_MACRO,		INSN2_M_FP_D,	I2,		0,	SF },
{"l.d",			"T,o(b)",	0xd4000000, 0xfc000000, WR_1|RD_3|CLD|FP_D,	0,		I2,		0,	SF }, /* ldc1 */
{"l.d",			"T,A(b)",	0,    (int) M_L_DAB,	INSN_MACRO,		INSN2_M_FP_D,	I1,		0,	0 },
{"ldc2",		"E,o(b)",	0xd8000000, 0xfc000000,	RD_3|WR_CC|CLD,		0,		I2,		0,	IOCT|IOCTP|IOCT2|EE },
{"ldc2",		"E,A(b)",	0,    (int) M_LDC2_AB,	INSN_MACRO,		0,		I2,		0,	IOCT|IOCTP|IOCT2|EE },
{"ldc3",		"E,o(b)",	0xdc000000, 0xfc000000,	RD_3|WR_CC|CLD,		0,		I2,		0,	IOCT|IOCTP|IOCT2|EE },
{"ldc3",		"E,A(b)",	0,    (int) M_LDC3_AB,	INSN_MACRO,		0,		I2,		0,	IOCT|IOCTP|IOCT2|EE },
{"ldl",			"t,o(b)",	0x68000000, 0xfc000000, WR_1|RD_3|LDD,		0,		I3,		0,	0 },
{"ldl",			"t,A(b)",	0,    (int) M_LDL_AB,	INSN_MACRO,		0,		I3,		0,	0 },
{"ldr",			"t,o(b)",	0x6c000000, 0xfc000000, WR_1|RD_3|LDD,		0,		I3,		0,	0 },
{"ldr",			"t,A(b)",	0,    (int) M_LDR_AB,	INSN_MACRO,		0,		I3,		0,	0 },
{"ldxc1",		"D,t(b)",	0x4c000001, 0xfc00f83f, WR_1|RD_2|RD_3|LDD|FP_D, 0,		I4_33,		0,	0 },
{"lh",			"t,o(b)",	0x84000000, 0xfc000000,	WR_1|RD_3|LDD,		0,		I1,		0,	0 },
{"lh",			"t,A(b)",	0,    (int) M_LH_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"lhu",			"t,o(b)",	0x94000000, 0xfc000000,	WR_1|RD_3|LDD,		0,		I1,		0,	0 },
{"lhu",			"t,A(b)",	0,    (int) M_LHU_AB,	INSN_MACRO,		0,		I1,		0,	0 },
/* li is at the start of the table.  */
{"li.d",		"t,F",		0,    (int) M_LI_D,	INSN_MACRO,		INSN2_M_FP_D,	I1,		0,	SF },
{"li.d",		"T,L",		0,    (int) M_LI_DD,	INSN_MACRO,		INSN2_M_FP_D,	I1,		0,	SF },
{"li.s",		"t,f",		0,    (int) M_LI_S,	INSN_MACRO,		INSN2_M_FP_S,	I1,		0,	0 },
{"li.s",		"T,l",		0,    (int) M_LI_SS,	INSN_MACRO,		INSN2_M_FP_S,	I1,		0,	0 },
{"ll",			"t,o(b)",	0xc0000000, 0xfc000000, WR_1|RD_3|LDD,		0,		I2,		0,	EE },
{"ll",			"t,A(b)",	0,    (int) M_LL_AB,	INSN_MACRO,		0,		I2,		0,	EE },
{"lld",			"t,o(b)",	0xd0000000, 0xfc000000, WR_1|RD_3|LDD,		0,		I3,		0,	EE },
{"lld",			"t,A(b)",	0,    (int) M_LLD_AB,	INSN_MACRO,		0,		I3,		0,	EE },
{"lq",			"t,o(b)",	0x78000000, 0xfc000000, WR_1|RD_3,		0,		MMI,		0,	0 },
{"lq",			"t,A(b)",	0,    (int) M_LQ_AB,	INSN_MACRO,		0,		MMI,		0,	0 },
{"lqc2",		"+7,o(b)",	0xd8000000, 0xfc000000,	RD_3|WR_C2,		0,		EE,		0,	0 },
{"lqc2",		"+7,A(b)",	0,    (int) M_LQC2_AB,	INSN_MACRO,		0,		EE,		0,	0 },
{"lui",			"t,u",		0x3c000000, 0xffe00000,	WR_1,			0,		I1,		0,	0 },
{"luxc1",		"D,t(b)",	0x4c000005, 0xfc00f83f, WR_1|RD_2|RD_3|LDD|FP_D, 0,		I5_33|N55,	0,	0},
{"lw",			"t,o(b)",	0x8c000000, 0xfc000000,	WR_1|RD_3|LDD,		0,		I1,		0,	0 },
{"lw",			"t,A(b)",	0,    (int) M_LW_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"lwc0",		"E,o(b)",	0xc0000000, 0xfc000000,	RD_3|WR_CC|CLD,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"lwc0",		"E,A(b)",	0,    (int) M_LWC0_AB,	INSN_MACRO,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"lwc1",		"T,o(b)",	0xc4000000, 0xfc000000,	WR_1|RD_3|CLD|FP_S,	0,		I1,		0,	0 },
{"lwc1",		"E,o(b)",	0xc4000000, 0xfc000000,	WR_1|RD_3|CLD|FP_S,	0,		I1,		0,	0 },
{"lwc1",		"T,A(b)",	0,    (int) M_LWC1_AB,	INSN_MACRO,		INSN2_M_FP_S,	I1,		0,	0 },
{"lwc1",		"E,A(b)",	0,    (int) M_LWC1_AB,	INSN_MACRO,		INSN2_M_FP_S,	I1,		0,	0 },
{"l.s",			"T,o(b)",	0xc4000000, 0xfc000000,	WR_1|RD_3|CLD|FP_S,	0,		I1,		0,	0 }, /* lwc1 */
{"l.s",			"T,A(b)",	0,    (int) M_LWC1_AB,	INSN_MACRO,		INSN2_M_FP_S,	I1,		0,	0 },
{"lwc2",		"E,o(b)",	0xc8000000, 0xfc000000,	RD_3|WR_CC|CLD,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"lwc2",		"E,A(b)",	0,    (int) M_LWC2_AB,	INSN_MACRO,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"lwc3",		"E,o(b)",	0xcc000000, 0xfc000000,	RD_3|WR_CC|CLD,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"lwc3",		"E,A(b)",	0,    (int) M_LWC3_AB,	INSN_MACRO,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"lwl",			"t,o(b)",	0x88000000, 0xfc000000,	WR_1|RD_3|LDD,		0,		I1,		0,	0 },
{"lwl",			"t,A(b)",	0,    (int) M_LWL_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"lcache",		"t,o(b)",	0x88000000, 0xfc000000,	WR_1|RD_3|LDD,		0,		I2,		0,	0 }, /* same */
{"lcache",		"t,A(b)",	0,    (int) M_LWL_AB,	INSN_MACRO,		0,		I2,		0,	0 }, /* as lwl */
{"lwr",			"t,o(b)",	0x98000000, 0xfc000000,	WR_1|RD_3|LDD,		0,		I1,		0,	0 },
{"lwr",			"t,A(b)",	0,    (int) M_LWR_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"flush",		"t,o(b)",	0x98000000, 0xfc000000,	WR_1|RD_3|LDD,		0,		I2,		0,	0 }, /* same */
{"flush",		"t,A(b)",	0,    (int) M_LWR_AB,	INSN_MACRO,		0,		I2,		0,	0 }, /* as lwr */
{"fork",		"d,s,t",	0x7c000008, 0xfc0007ff, WR_1|RD_2|RD_3|TRAP,	0,		0,		MT32,	0 },
{"lwu",			"t,o(b)",	0x9c000000, 0xfc000000,	WR_1|RD_3|LDD,		0,		I3,		0,	0 },
{"lwu",			"t,A(b)",	0,    (int) M_LWU_AB,	INSN_MACRO,		0,		I3,		0,	0 },
{"lwxc1",		"D,t(b)",	0x4c000000, 0xfc00f83f, WR_1|RD_2|RD_3|LDD|FP_S,     0,		I4_33,		0,	0 },
{"lwxs",		"d,t(b)",	0x70000088, 0xfc0007ff,	WR_1|RD_2|RD_3|LDD,	     0,		0,		SMT,	0 },
{"macc",		"d,s,t",	0x00000028, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	     0,		N412,		0,	0 },
{"macc",		"d,s,t",	0x00000158, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	     0,		N5,		0,	0 },
{"maccs",		"d,s,t",	0x00000428, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	     0,		N412,		0,	0 },
{"macchi",		"d,s,t",	0x00000228, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	     0,		N412,		0,	0 },
{"macchi",		"d,s,t",	0x00000358, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	     0,		N5,		0,	0 },
{"macchis",		"d,s,t",	0x00000628, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	     0,		N412,		0,	0 },
{"macchiu",		"d,s,t",	0x00000268, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	     0,		N412,		0,	0 },
{"macchiu",		"d,s,t",	0x00000359, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	     0,		N5,		0,	0 },
{"macchius",		"d,s,t",	0x00000668, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	     0,		N412,		0,	0 },
{"maccu",		"d,s,t",	0x00000068, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	     0,		N412,		0,	0 },
{"maccu",		"d,s,t",	0x00000159, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	     0,		N5,		0,	0 },
{"maccus",		"d,s,t",	0x00000468, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	     0,		N412,		0,	0 },
{"mad",			"s,t",		0x70000000, 0xfc00ffff, RD_1|RD_2|MOD_HILO,	     0,		P3,		0,	0 },
{"madu",		"s,t",		0x70000001, 0xfc00ffff, RD_1|RD_2|MOD_HILO,	     0,		P3,		0,	0 },
{"madd.d",		"D,R,S,T",	0x4c000021, 0xfc00003f, WR_1|RD_2|RD_3|RD_4|FP_D,    0,		I4_33,		0,	0 },
{"madd.d",		"D,S,T",	0x46200018, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	     0,		IL2E,		0,	0 },
{"madd.d",		"D,S,T",	0x72200018, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	     0,		IL2F,		0,	0 },
{"madd.s",		"D,R,S,T",	0x4c000020, 0xfc00003f, WR_1|RD_2|RD_3|RD_4|FP_S,    0,		I4_33,		0,	0 },
{"madd.s",		"D,S,T",	0x46000018, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	     0,		IL2E,		0,	0 },
{"madd.s",		"D,S,T",	0x72000018, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	     0,		IL2F,		0,	0 },
{"madd.s",		"D,S,T",	0x4600001c, 0xffe0003f, WR_1|RD_2|RD_3|FP_S,	     0,		EE,		0,	0 },
{"madd.ps",		"D,R,S,T",	0x4c000026, 0xfc00003f, WR_1|RD_2|RD_3|RD_4|FP_D,    0,		I5_33,		0,	0 },
{"madd.ps",		"D,S,T",	0x45600018, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	     0,		IL2E,		0,	0 },
{"madd.ps",		"D,S,T",	0x72c00018, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	     0,		IL2F,		0,	0 },
{"madd",		"s,t",		0x0000001c, 0xfc00ffff, RD_1|RD_2|WR_HILO,           0,		L1,		0,	0 },
{"madd",		"s,t",		0x70000000, 0xfc00ffff, RD_1|RD_2|MOD_HILO,          0,		I32|N55,	0,	0 },
{"madd",		"s,t",		0x70000000, 0xfc00ffff, RD_1|RD_2|WR_HILO|IS_M,      0,		G1,		0,	0 },
{"madd",		"7,s,t",	0x70000000, 0xfc00e7ff, RD_2|RD_3|MOD_a,             0,         0,		D32,	0 },
{"madd",		"d,s,t",	0x70000000, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO|IS_M, 0,		G1,		0,	0 },
{"madd1",		"s,t",		0x70000020, 0xfc00ffff, RD_1|RD_2|WR_HILO|IS_M,      0,		EE,		0,	0 },
{"madd1",		"d,s,t",	0x70000020, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO|IS_M, 0,		EE,		0,	0 },
{"madda.s",		"S,T",		0x4600001e, 0xffe007ff, RD_1|RD_2|FP_S,		     0,		EE,		0,	0 },
{"maddp",		"s,t",		0x70000441, 0xfc00ffff,	RD_1|RD_2|MOD_HILO,	     0,		0,		SMT,	0 },
{"maddu",		"s,t",		0x0000001d, 0xfc00ffff, RD_1|RD_2|WR_HILO,           0,		L1,		0,	0 },
{"maddu",		"s,t",		0x70000001, 0xfc00ffff, RD_1|RD_2|MOD_HILO,          0,		I32|N55,	0,	0 },
{"maddu",		"s,t",		0x70000001, 0xfc00ffff, RD_1|RD_2|WR_HILO|IS_M,      0,		G1,		0,	0 },
{"maddu",		"7,s,t",	0x70000001, 0xfc00e7ff, RD_2|RD_3|MOD_a,             0,         0,		D32,	0 },
{"maddu",		"d,s,t",	0x70000001, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO|IS_M, 0,		G1,		0,	0 },
{"maddu1",		"s,t",		0x70000021, 0xfc00ffff, RD_1|RD_2|WR_HILO|IS_M,      0,		EE,		0,	0 },
{"maddu1",		"d,s,t",	0x70000021, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO|IS_M, 0,		EE,		0,	0 },
{"madd16",		"s,t",		0x00000028, 0xfc00ffff, RD_1|RD_2|MOD_HILO,	0,		N411,		0,	0 },
{"max.ob",		"X,Y,Q",	0x78000007, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"max.ob",		"D,S,Q",	0x48000007, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"max.qh",		"X,Y,Q",	0x78200007, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"max.s",		"D,S,T",	0x46000028, 0xffe0003f, WR_1|RD_2|RD_3|FP_S,	0,		EE,		0,	0 },
{"mfbpc",		"t",		0x4000c000, 0xffe0ffff,	WR_1|RD_C0|LCD,		0,		EE,		0,	0 },
{"mfdab",		"t",		0x4000c004, 0xffe0ffff,	WR_1|RD_C0|LCD,		0,		EE,		0,	0 },
{"mfdabm",		"t",		0x4000c005, 0xffe0ffff,	WR_1|RD_C0|LCD,		0,		EE,		0,	0 },
{"mfdvb",		"t",		0x4000c006, 0xffe0ffff,	WR_1|RD_C0|LCD,		0,		EE,		0,	0 },
{"mfdvbm",		"t",		0x4000c007, 0xffe0ffff,	WR_1|RD_C0|LCD,		0,		EE,		0,	0 },
{"mfiab",		"t",		0x4000c002, 0xffe0ffff,	WR_1|RD_C0|LCD,		0,		EE,		0,	0 },
{"mfiabm",		"t",		0x4000c003, 0xffe0ffff,	WR_1|RD_C0|LCD,		0,		EE,		0,	0 },
{"mfpc",		"t,P",		0x4000c801, 0xffe0ffc1,	WR_1|RD_C0|LCD,		0,		M1|N5|EE,	0,	0 },
{"mfps",		"t,P",		0x4000c800, 0xffe0ffc1,	WR_1|RD_C0|LCD,		0,		M1|N5|EE,	0,	0 },
{"mftacx",		"d",		0x41020021, 0xffff07ff, WR_1|RD_a|TRAP,		0,		0,		MT32,	0 },
{"mftacx",		"d,*",		0x41020021, 0xfff307ff, WR_1|RD_a|TRAP,		0,		0,		MT32,	0 },
{"mftc0",		"d,+t",		0x41000000, 0xffe007ff, WR_1|RD_C0|TRAP|LCD,	0,		0,		MT32,	0 },
{"mftc0",		"d,E,H",	0x41000000, 0xffe007f8, WR_1|RD_C0|TRAP|LCD,	0,		0,		MT32,	0 },
{"mftc1",		"d,T",		0x41000022, 0xffe007ff, WR_1|RD_2|TRAP|LCD|FP_S, 0,		0,		MT32,	0 },
{"mftc1",		"d,E",		0x41000022, 0xffe007ff, WR_1|RD_2|TRAP|LCD|FP_S, 0,		0,		MT32,	0 },
{"mftc2",		"d,E",		0x41000024, 0xffe007ff,	WR_1|RD_C2|TRAP|LCD,	0,		0,		MT32,	IOCT|IOCTP|IOCT2 },
{"mftdsp",		"d",		0x41100021, 0xffff07ff, WR_1|TRAP,		0,		0,		MT32,	0 },
{"mftgpr",		"d,t",		0x41000020, 0xffe007ff, WR_1|RD_2|TRAP,		0,		0,		MT32,	0 },
{"mfthc1",		"d,T",		0x41000032, 0xffe007ff, WR_1|RD_2|TRAP|LCD|FP_D, 0,		0,		MT32,	0 },
{"mfthc1",		"d,E",		0x41000032, 0xffe007ff, WR_1|RD_2|TRAP|LCD|FP_D, 0,		0,		MT32,	0 },
{"mfthc2",		"d,E",		0x41000034, 0xffe007ff,	WR_1|RD_C2|TRAP|LCD,	0,		0,		MT32,	IOCT|IOCTP|IOCT2 },
{"mfthi",		"d",		0x41010021, 0xffff07ff, WR_1|RD_a|TRAP,		0,		0,		MT32,	0 },
{"mfthi",		"d,*",		0x41010021, 0xfff307ff, WR_1|RD_a|TRAP,		0,		0,		MT32,	0 },
{"mftlo",		"d",		0x41000021, 0xffff07ff, WR_1|RD_a|TRAP,		0,		0,		MT32,	0 },
{"mftlo",		"d,*",		0x41000021, 0xfff307ff, WR_1|RD_a|TRAP,		0,		0,		MT32,	0 },
{"mftr",		"d,t,!,H,$",	0x41000000, 0xffe007c8, WR_1|TRAP,		0,		0,		MT32,	0 },
{"mfc0",		"t,G",		0x40000000, 0xffe007ff,	WR_1|RD_C0|LCD,		0,		I1,		0,	0 },
{"mfc0",		"t,G,H",	0x40000000, 0xffe007f8,	WR_1|RD_C0|LCD,		0,		I32,		0,	0 },
{"mfgc0",		"t,G",		0x40600000, 0xffe007ff,	WR_1|RD_C0|LCD,		0,		0,		IVIRT,	0 },
{"mfgc0",		"t,G,H",	0x40600000, 0xffe007f8, WR_1|RD_C0|LCD, 	0,		0,		IVIRT,	0 },
{"mfc1",		"t,S",		0x44000000, 0xffe007ff,	WR_1|RD_2|LCD|FP_S,	0,		I1,		0,	0 },
{"mfc1",		"t,G",		0x44000000, 0xffe007ff,	WR_1|RD_2|LCD|FP_S,	0,		I1,		0,	0 },
{"mfhc1",		"t,S",		0x44600000, 0xffe007ff,	WR_1|RD_2|LCD|FP_D,	0,		I33,		0,	0 },
{"mfhc1",		"t,G",		0x44600000, 0xffe007ff,	WR_1|RD_2|LCD|FP_D,	0,		I33,		0,	0 },
/* mfc2 is at the bottom of the table.  */
/* mfhc2 is at the bottom of the table.  */
/* mfc3 is at the bottom of the table.  */
{"mfdr",		"t,G",		0x7000003d, 0xffe007ff,	WR_1|RD_C0|LCD,		0,		N5,		0,	0 },
{"mfhi",		"d",		0x00000010, 0xffff07ff,	WR_1|RD_HI,		0,		I1,		0,	0 },
{"mfhi",		"d,9",		0x00000010, 0xff9f07ff, WR_1|RD_HI,		0,		0,		D32,	0 },
{"mfhi1",		"d",		0x70000010, 0xffff07ff,	WR_1|RD_HI,		0,		EE,		0,	0 },
{"mflo",		"d",		0x00000012, 0xffff07ff,	WR_1|RD_LO,		0,		I1,		0,	0 },
{"mflo",		"d,9",		0x00000012, 0xff9f07ff, WR_1|RD_LO,		0,		0,		D32,	0 },
{"mflo1",		"d",		0x70000012, 0xffff07ff,	WR_1|RD_LO,		0,		EE,		0,	0 },
{"mflhxu",		"d",		0x00000052, 0xffff07ff,	WR_1|MOD_HILO,		0,		0,		SMT,	0 },
{"mfcr",		"t,s",		0x70000018, 0xfc00ffff, WR_1,			0,		XLR,		0,	0 },
{"mfsa",		"d",		0x00000028, 0xffff07ff,	WR_1,			0,		EE,		0,	0 },
{"min.ob",		"X,Y,Q",	0x78000006, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"min.ob",		"D,S,Q",	0x48000006, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"min.qh",		"X,Y,Q",	0x78200006, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"min.s",		"D,S,T",	0x46000029, 0xffe0003f, WR_1|RD_2|RD_3|FP_S,	0,		EE,		0,	0 },
{"mov.d",		"D,S",		0x46200006, 0xffff003f,	WR_1|RD_2|FP_D,		0,		I1,		0,	SF },
{"mov.s",		"D,S",		0x46000006, 0xffff003f,	WR_1|RD_2|FP_S,		0,		I1,		0,	0 },
{"mov.ps",		"D,S",		0x46c00006, 0xffff003f,	WR_1|RD_2|FP_D,		0,		I5_33|IL2F,	0,	0 },
{"mov.ps",		"D,S",		0x45600006, 0xffff003f,	WR_1|RD_2|FP_D,		0,		IL2E,		0,	0 },
{"movf",		"d,s,N",	0x00000001, 0xfc0307ff, WR_1|RD_2|RD_CC|FP_S|FP_D, 0,		I4_32,		0,	0  },
{"movf.d",		"D,S,N",	0x46200011, 0xffe3003f, WR_1|RD_2|RD_CC|FP_D,   0,		I4_32,		0,	0 },
{"movf.l",		"D,S,N",	0x46a00011, 0xffe3003f, WR_1|RD_2|RD_CC|FP_D,	0,		SB1,		MX,	0 },
{"movf.l",		"X,Y,N",	0x46a00011, 0xffe3003f, WR_1|RD_2|RD_CC|FP_D,	0,		SB1,		MX,	0 },
{"movf.s",		"D,S,N",	0x46000011, 0xffe3003f, WR_1|RD_2|RD_CC|FP_S,   0,		I4_32,		0,	0 },
{"movf.ps",		"D,S,N",	0x46c00011, 0xffe3003f, WR_1|RD_2|RD_CC|FP_D,	0,		I5_33,		0,	0 },
{"movn",		"d,v,t",	0x0000000b, 0xfc0007ff, WR_1|RD_2|RD_3, 	0,		I4_32|IL2E|IL2F|EE, 0,	0 },
{"movnz",		"d,v,t",	0x0000000b, 0xfc0007ff, WR_1|RD_2|RD_3, 	0,		IL2E|IL2F|IL3A,	0,	0 },
{"ffc",			"d,v",		0x0000000b, 0xfc1f07ff,	WR_1|RD_2,		0,		L1,		0,	0 },
{"movn.d",		"D,S,t",	0x46200013, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,    0,		I4_32,		0,	0 },
{"movn.l",		"D,S,t",	0x46a00013, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,    0,		SB1,		MX,	0 },
{"movn.l",		"X,Y,t",	0x46a00013, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,    0,		SB1,		MX,	0 },
{"movn.s",		"D,S,t",	0x46000013, 0xffe0003f, WR_1|RD_2|RD_3|FP_S,    0,		I4_32,		0,	0 },
{"movn.ps",		"D,S,t",	0x46c00013, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,    0,		I5_33,		0,	0 },
{"movt",		"d,s,N",	0x00010001, 0xfc0307ff, WR_1|RD_2|RD_CC|FP_S|FP_D, 0,		I4_32,		0,	0 },
{"movt.d",		"D,S,N",	0x46210011, 0xffe3003f, WR_1|RD_2|RD_CC|FP_D,   0,		I4_32,		0,	0 },
{"movt.l",		"D,S,N",	0x46a10011, 0xffe3003f, WR_1|RD_2|RD_CC|FP_D,   0,		SB1,		MX,	0 },
{"movt.l",		"X,Y,N",	0x46a10011, 0xffe3003f, WR_1|RD_2|RD_CC|FP_D,   0,		SB1,		MX,	0 },
{"movt.s",		"D,S,N",	0x46010011, 0xffe3003f, WR_1|RD_2|RD_CC|FP_S,   0,		I4_32,		0,	0 },
{"movt.ps",		"D,S,N",	0x46c10011, 0xffe3003f, WR_1|RD_2|RD_CC|FP_D,	0,		I5_33,		0,	0 },
{"movz",		"d,v,t",	0x0000000a, 0xfc0007ff, WR_1|RD_2|RD_3, 	0,		I4_32|IL2E|IL2F|EE, 0,	0 },
{"ffs",			"d,v",		0x0000000a, 0xfc1f07ff,	WR_1|RD_2,		0,		L1,		0,	0 },
{"movz.d",		"D,S,t",	0x46200012, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,    0,		I4_32,		0,	0 },
{"movz.l",		"D,S,t",	0x46a00012, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,    0,		SB1,		MX,	0 },
{"movz.l",		"X,Y,t",	0x46a00012, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,    0,		SB1,		MX,	0 },
{"movz.s",		"D,S,t",	0x46000012, 0xffe0003f, WR_1|RD_2|RD_3|FP_S,    0,		I4_32,		0,	0 },
{"movz.ps",		"D,S,t",	0x46c00012, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,    0,		I5_33,		0,	0 },
{"msac",		"d,s,t",	0x000001d8, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	0,		N5,		0,	0 },
{"msacu",		"d,s,t",	0x000001d9, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	0,		N5,		0,	0 },
{"msachi",		"d,s,t",	0x000003d8, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	0,		N5,		0,	0 },
{"msachiu",		"d,s,t",	0x000003d9, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	0,		N5,		0,	0 },
/* move is at the top of the table.  */
{"msgn.qh",		"X,Y,Q",	0x78200000, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"msgsnd",		"t",		0,    (int) M_MSGSND,	INSN_MACRO,		0,		XLR,		0,	0 },
{"msgld",		"", 		0,    (int) M_MSGLD,	INSN_MACRO,		0,		XLR,		0,	0 },
{"msgld",		"t",		0,    (int) M_MSGLD_T,	INSN_MACRO,		0,		XLR,		0,	0 },
{"msgwait",		"", 		0,    (int) M_MSGWAIT,	INSN_MACRO,		0,		XLR,		0,	0 },
{"msgwait",		"t",		0,    (int) M_MSGWAIT_T,INSN_MACRO,		0,		XLR,		0,	0 },
{"msub.d",		"D,R,S,T",	0x4c000029, 0xfc00003f, WR_1|RD_2|RD_3|RD_4|FP_D, 0,		I4_33,		0,	0 },
{"msub.d",		"D,S,T",	0x46200019, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"msub.d",		"D,S,T",	0x72200019, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F,		0,	0 },
{"msub.s",		"D,R,S,T",	0x4c000028, 0xfc00003f, WR_1|RD_2|RD_3|RD_4|FP_S, 0,		I4_33,		0,	0 },
{"msub.s",		"D,S,T",	0x46000019, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2E,		0,	0 },
{"msub.s",		"D,S,T",	0x72000019, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2F,		0,	0 },
{"msub.s",		"D,S,T",	0x4600001d, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		EE,		0,	0 },
{"msub.ps",		"D,R,S,T",	0x4c00002e, 0xfc00003f, WR_1|RD_2|RD_3|RD_4|FP_D, 0,		I5_33,		0,	0 },
{"msub.ps",		"D,S,T",	0x45600019, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"msub.ps",		"D,S,T",	0x72c00019, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F,		0,	0 },
{"msub",		"s,t",		0x0000001e, 0xfc00ffff, RD_1|RD_2|WR_HILO,	0,		L1,		0,	0 },
{"msub",		"s,t",		0x70000004, 0xfc00ffff, RD_1|RD_2|MOD_HILO,     0,		I32|N55,	0,	0 },
{"msub",		"7,s,t",	0x70000004, 0xfc00e7ff, RD_2|RD_3|MOD_a,        0,              0,		D32,	0 },
{"msuba.s",		"S,T",		0x4600001f, 0xffe007ff,	RD_1|RD_2|FP_S,		0,		EE,		0,	0 },
{"msubu",		"s,t",		0x0000001f, 0xfc00ffff, RD_1|RD_2|WR_HILO,	0,		L1,		0,	0 },
{"msubu",		"s,t",		0x70000005, 0xfc00ffff, RD_1|RD_2|MOD_HILO,     0,		I32|N55,	0,	0 },
{"msubu",		"7,s,t",	0x70000005, 0xfc00e7ff, RD_2|RD_3|MOD_a,        0,              0,		D32,	0 },
{"mtbpc",		"t",		0x4080c000, 0xffe0ffff,	RD_1|WR_C0|COD,		0,		EE,		0,	0 },
{"mtdab",		"t",		0x4080c004, 0xffe0ffff,	RD_1|WR_C0|COD,		0,		EE,		0,	0 },
{"mtdabm",		"t",		0x4080c005, 0xffe0ffff,	RD_1|WR_C0|COD,		0,		EE,		0,	0 },
{"mtdvb",		"t",		0x4080c006, 0xffe0ffff,	RD_1|WR_C0|COD,		0,		EE,		0,	0 },
{"mtdvbm",		"t",		0x4080c007, 0xffe0ffff,	RD_1|WR_C0|COD,		0,		EE,		0,	0 },
{"mtiab",		"t",		0x4080c002, 0xffe0ffff,	RD_1|WR_C0|COD,		0,		EE,		0,	0 },
{"mtiabm",		"t",		0x4080c003, 0xffe0ffff,	RD_1|WR_C0|COD,		0,		EE,		0,	0 },
{"mtpc",		"t,P",		0x4080c801, 0xffe0ffc1,	RD_1|WR_C0|COD,		0,		M1|N5|EE,	0,	0 },
{"mtps",		"t,P",		0x4080c800, 0xffe0ffc1,	RD_1|WR_C0|COD,		0,		M1|N5|EE,	0,	0 },
{"mtc0",		"t,G",		0x40800000, 0xffe007ff,	RD_1|WR_C0|WR_CC|COD,	0,		I1,		0,	0 },
{"mtc0",		"t,G,H",	0x40800000, 0xffe007f8,	RD_1|WR_C0|WR_CC|COD,	0,		I32,		0,	0 },
{"mtgc0",		"t,G",		0x40600200, 0xffe007ff,	RD_1|WR_C0|WR_CC|COD,	0,		0,		IVIRT,	0 },
{"mtgc0",		"t,G,H",	0x40600200, 0xffe007f8, RD_1|WR_C0|WR_CC|COD,   0,		0,		IVIRT,	0 },
{"mtc1",		"t,S",		0x44800000, 0xffe007ff,	RD_1|WR_2|COD|FP_S,	0,		I1,		0,	0 },
{"mtc1",		"t,G",		0x44800000, 0xffe007ff,	RD_1|WR_2|COD|FP_S,	0,		I1,		0,	0 },
{"mthc1",		"t,S",		0x44e00000, 0xffe007ff,	RD_1|WR_2|COD|FP_D,	0,		I33,		0,	0 },
{"mthc1",		"t,G",		0x44e00000, 0xffe007ff,	RD_1|WR_2|COD|FP_D,	0,		I33,		0,	0 },
/* mtc2 is at the bottom of the table.  */
/* mthc2 is at the bottom of the table.  */
/* mtc3 is at the bottom of the table.  */
{"mtdr",		"t,G",		0x7080003d, 0xffe007ff,	RD_1|WR_C0|COD,		0,		N5,		0,	0 },
{"mthi",		"s",		0x00000011, 0xfc1fffff,	RD_1|WR_HI,		0,		I1,		0,	0 },
{"mthi",		"s,7",		0x00000011, 0xfc1fe7ff, RD_1|WR_HI,		0,		0,		D32,	0 },
{"mthi1",		"s",		0x70000011, 0xfc1fffff,	RD_1|WR_HI,		0,		EE,		0,	0 },
{"mtlo",		"s",		0x00000013, 0xfc1fffff,	RD_1|WR_LO,		0,		I1,		0,	0 },
{"mtlo",		"s,7",		0x00000013, 0xfc1fe7ff, RD_1|WR_LO,		0,		0,		D32,	0 },
{"mtlo1",		"s",		0x70000013, 0xfc1fffff,	RD_1|WR_LO,		0,		EE,		0,	0 },
{"mtlhx",		"s",		0x00000053, 0xfc1fffff,	RD_1|MOD_HILO,		0,		0,		SMT,	0 },
{"mtcr",		"t,s",		0x70000019, 0xfc00ffff, RD_1,			0,		XLR,		0,	0 },
{"mtm0",		"s",		0x70000008, 0xfc1fffff, RD_1,			0,		IOCT,		0,	0 },
{"mtm1",		"s",		0x7000000c, 0xfc1fffff, RD_1,			0,		IOCT,		0,	0 },
{"mtm2",		"s",		0x7000000d, 0xfc1fffff, RD_1,			0,		IOCT,		0,	0 },
{"mtp0",		"s",		0x70000009, 0xfc1fffff, RD_1,			0,		IOCT,		0,	0 },
{"mtp1",		"s",		0x7000000a, 0xfc1fffff, RD_1,			0,		IOCT,		0,	0 },
{"mtp2",		"s",		0x7000000b, 0xfc1fffff, RD_1,			0,		IOCT,		0,	0 },
{"mtsa",		"s",		0x00000029, 0xfc1fffff,	RD_1,			0,		EE,		0,	0 },
{"mtsab",		"s,j",		0x04180000, 0xfc1f0000,	RD_1,			0,		EE,		0,	0 },
{"mtsah",		"s,j",		0x04190000, 0xfc1f0000,	RD_1,			0,		EE,		0,	0 },
{"mttc0",		"t,G",		0x41800000, 0xffe007ff, RD_1|WR_C0|WR_CC|TRAP|COD, 0,		0,		MT32,	0 },
{"mttc0",		"t,G,H",	0x41800000, 0xffe007f8, RD_1|WR_C0|WR_CC|TRAP|COD, 0,		0,		MT32,	0 },
{"mttc1",		"t,S",		0x41800022, 0xffe007ff, RD_1|WR_2|TRAP|COD|FP_S, 0,		0,		MT32,	0 },
{"mttc1",		"t,G",		0x41800022, 0xffe007ff, RD_1|WR_2|TRAP|COD|FP_S, 0,		0,		MT32,	0 },
{"mttc2",		"t,g",		0x41800024, 0xffe007ff,	RD_1|WR_C2|WR_CC|TRAP|COD, 0,		0,		MT32,	IOCT|IOCTP|IOCT2 },
{"mttacx",		"t",		0x41801021, 0xffe0ffff, RD_1|WR_a|TRAP,		0,		0,		MT32,	0 },
{"mttacx",		"t,&",		0x41801021, 0xffe09fff, RD_1|WR_a|TRAP,		0,		0,		MT32,	0 },
{"mttdsp",		"t",		0x41808021, 0xffe0ffff, RD_1|TRAP,		0,		0,		MT32,	0 },
{"mttgpr",		"t,d",		0x41800020, 0xffe007ff, RD_1|WR_2|TRAP,		0,		0,		MT32,	0 },
{"mtthc1",		"t,S",		0x41800032, 0xffe007ff, RD_1|WR_2|TRAP|COD|FP_D, 0,		0,		MT32,	0 },
{"mtthc1",		"t,G",		0x41800032, 0xffe007ff, RD_1|WR_2|TRAP|COD|FP_D, 0,		0,		MT32,	0 },
{"mtthc2",		"t,g",		0x41800034, 0xffe007ff,	RD_1|WR_C2|WR_CC|TRAP|COD, 0,		0,		MT32,	IOCT|IOCTP|IOCT2 },
{"mtthi",		"t",		0x41800821, 0xffe0ffff, RD_1|WR_a|TRAP,		0,		0,		MT32,	0 },
{"mtthi",		"t,&",		0x41800821, 0xffe09fff, RD_1|WR_a|TRAP,		0,		0,		MT32,	0 },
{"mttlo",		"t",		0x41800021, 0xffe0ffff, RD_1|WR_a|TRAP,		0,		0,		MT32,	0 },
{"mttlo",		"t,&",		0x41800021, 0xffe09fff, RD_1|WR_a|TRAP,		0,		0,		MT32,	0 },
{"mttr",		"t,d,!,H,$",	0x41800000, 0xffe007c8, RD_1|TRAP,		0,		0,		MT32,	0 },
{"mul.d",		"D,V,T",	0x46200002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		I1,		0,	SF },
{"mul.s",		"D,V,T",	0x46000002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		I1,		0,	0 },
{"mul.ob",		"X,Y,Q",	0x78000030, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"mul.ob",		"D,S,Q",	0x48000030, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"mul.ps",		"D,V,T",	0x46c00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"mul.ps",		"D,V,T",	0x45600002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"mul.qh",		"X,Y,Q",	0x78200030, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"mul",			"d,v,t",	0x70000002, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,		I32|P3|N55,	0,	0},
{"mul",			"d,s,t",	0x00000058, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	0,		N54,		0,	0 },
{"mul",			"d,v,t",	0,    (int) M_MUL,	INSN_MACRO,		0,		I1,		0,	0 },
{"mul",			"d,v,I",	0,    (int) M_MUL_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"mula.ob",		"Y,Q",		0x78000033, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	SB1,		MX,	0 },
{"mula.ob",		"S,Q",		0x48000033, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	N54,		0,	0 },
{"mula.qh",		"Y,Q",		0x78200033, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	0,		MX,	0 },
{"mula.s",		"S,T",		0x4600001a, 0xffe007ff,	RD_1|RD_2|FP_S,		0,		EE,		0,	0 },
{"mulhi",		"d,s,t",	0x00000258, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	0,		N5,		0,	0 },
{"mulhiu",		"d,s,t",	0x00000259, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	0,		N5,		0,	0 },
{"mull.ob",		"Y,Q",		0x78000433, 0xfc2007ff,	RD_1|RD_2|FP_D, 	WR_MACC,	SB1,		MX,	0 },
{"mull.ob",		"S,Q",		0x48000433, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	N54,		0,	0 },
{"mull.qh",		"Y,Q",		0x78200433, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	0,		MX,	0 },
{"mulo",		"d,v,t",	0,    (int) M_MULO,	INSN_MACRO,		0,		I1,		0,	0 },
{"mulo",		"d,v,I",	0,    (int) M_MULO_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"mulou",		"d,v,t",	0,    (int) M_MULOU,	INSN_MACRO,		0,		I1,		0,	0 },
{"mulou",		"d,v,I",	0,    (int) M_MULOU_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"mulr.ps",		"D,S,T",	0x46c0001a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		M3D,	0 },
{"muls",		"d,s,t",	0x000000d8, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	0,		N5,		0,	0 },
{"mulsu",		"d,s,t",	0x000000d9, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	0,		N5,		0,	0 },
{"mulshi",		"d,s,t",	0x000002d8, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	0,		N5,		0,	0 },
{"mulshiu",		"d,s,t",	0x000002d9, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	0,		N5,		0,	0 },
{"muls.ob",		"Y,Q",		0x78000032, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	SB1,		MX,	0 },
{"muls.ob",		"S,Q",		0x48000032, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	N54,		0,	0 },
{"muls.qh",		"Y,Q",		0x78200032, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	0,		MX,	0 },
{"mulsl.ob",		"Y,Q",		0x78000432, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	SB1,		MX,	0 },
{"mulsl.ob",		"S,Q",		0x48000432, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	N54,		0,	0 },
{"mulsl.qh",		"Y,Q",		0x78200432, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	0,		MX,	0 },
{"mult",		"s,t",		0x00000018, 0xfc00ffff, RD_1|RD_2|WR_HILO|IS_M, 0,		I1,		0,	0 },
{"mult",		"7,s,t",	0x00000018, 0xfc00e7ff, RD_2|RD_3|WR_a,         0,              0,		D32,	0 },
{"mult",		"d,s,t",	0x00000018, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO|IS_M, 0,		G1,		0,	0 },
{"mult1",		"s,t",		0x70000018, 0xfc00ffff, RD_1|RD_2|WR_HILO|IS_M, 0,		EE,		0,	0 },
{"mult1",		"d,s,t",	0x70000018, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO|IS_M, 0,		EE,		0,	0 },
{"multp",		"s,t",		0x00000459, 0xfc00ffff,	RD_1|RD_2|MOD_HILO,	0,		0,		SMT,	0 },
{"multu",		"s,t",		0x00000019, 0xfc00ffff, RD_1|RD_2|WR_HILO|IS_M, 0,		I1,		0,	0 },
{"multu",		"7,s,t",	0x00000019, 0xfc00e7ff, RD_2|RD_3|WR_a,         0,              0,		D32,	0 },
{"multu",		"d,s,t",	0x00000019, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO|IS_M, 0,		G1,		0,	0 },
{"multu1",		"s,t",		0x70000019, 0xfc00ffff, RD_1|RD_2|WR_HILO|IS_M, 0,		EE,		0,	0 },
{"multu1",		"d,s,t",	0x70000019, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO|IS_M, 0,		EE,		0,	0 },
{"mulu",		"d,s,t",	0x00000059, 0xfc0007ff,	WR_1|RD_2|RD_3|WR_HILO,	0,		N5,		0,	0 },
{"neg",			"d,w",		0x00000022, 0xffe007ff,	WR_1|RD_2,		0,		I1,		0,	0 }, /* sub 0 */
{"negu",		"d,w",		0x00000023, 0xffe007ff,	WR_1|RD_2,		0,		I1,		0,	0 }, /* subu 0 */
{"neg.d",		"D,V",		0x46200007, 0xffff003f,	WR_1|RD_2|FP_D,		0,		I1,		0,	SF },
{"neg.s",		"D,V",		0x46000007, 0xffff003f,	WR_1|RD_2|FP_S,		0,		I1,		0,	0 },
{"neg.ps",		"D,V",		0x46c00007, 0xffff003f,	WR_1|RD_2|FP_D,		0,		I5_33|IL2F,	0,	0 },
{"neg.ps",		"D,V",		0x45600007, 0xffff003f,	WR_1|RD_2|FP_D,		0,		IL2E,		0,	0 },
{"nmadd.d",		"D,R,S,T",	0x4c000031, 0xfc00003f, WR_1|RD_2|RD_3|RD_4|FP_D, 0,		I4_33,		0,	0 },
{"nmadd.d",		"D,S,T",	0x4620001a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"nmadd.d",		"D,S,T",	0x7220001a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F,		0,	0 },
{"nmadd.s",		"D,R,S,T",	0x4c000030, 0xfc00003f, WR_1|RD_2|RD_3|RD_4|FP_S, 0,		I4_33,		0,	0 },
{"nmadd.s",		"D,S,T",	0x4600001a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2E,		0,	0 },
{"nmadd.s",		"D,S,T",	0x7200001a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2F,		0,	0 },
{"nmadd.ps",		"D,R,S,T",	0x4c000036, 0xfc00003f, WR_1|RD_2|RD_3|RD_4|FP_D, 0,		I5_33,		0,	0 },
{"nmadd.ps",		"D,S,T",	0x4560001a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"nmadd.ps",		"D,S,T",	0x72c0001a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F,		0,	0 },
{"nmsub.d",		"D,R,S,T",	0x4c000039, 0xfc00003f, WR_1|RD_2|RD_3|RD_4|FP_D, 0,		I4_33,		0,	0 },
{"nmsub.d",		"D,S,T",	0x4620001b, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"nmsub.d",		"D,S,T",	0x7220001b, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F,		0,	0 },
{"nmsub.s",		"D,R,S,T",	0x4c000038, 0xfc00003f, WR_1|RD_2|RD_3|RD_4|FP_S, 0,		I4_33,		0,	0 },
{"nmsub.s",		"D,S,T",	0x4600001b, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2E,		0,	0 },
{"nmsub.s",		"D,S,T",	0x7200001b, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2F,		0,	0 },
{"nmsub.ps",		"D,R,S,T",	0x4c00003e, 0xfc00003f, WR_1|RD_2|RD_3|RD_4|FP_D, 0,		I5_33,		0,	0 },
{"nmsub.ps",		"D,S,T",	0x4560001b, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"nmsub.ps",		"D,S,T",	0x72c0001b, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F,		0,	0 },
/* nop is at the start of the table.  */
{"nor",			"d,v,t",	0x00000027, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"nor",			"t,r,I",	0,    (int) M_NOR_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"nor",			"D,S,T",	0x47a00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"nor",			"D,S,T",	0x4ba00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"nor.ob",		"X,Y,Q",	0x7800000f, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"nor.ob",		"D,S,Q",	0x4800000f, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"nor.qh",		"X,Y,Q",	0x7820000f, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"not",			"d,v",		0x00000027, 0xfc1f07ff,	WR_1|RD_2,		0,		I1,		0,	0 },/*nor d,s,0*/
{"or",			"d,v,t",	0x00000025, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"or",			"t,r,I",	0,    (int) M_OR_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"or",			"D,S,T",	0x45a00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"or",			"D,S,T",	0x4b20000c, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"or.ob",		"X,Y,Q",	0x7800000e, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"or.ob",		"D,S,Q",	0x4800000e, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"or.qh",		"X,Y,Q",	0x7820000e, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"ori",			"t,r,i",	0x34000000, 0xfc000000,	WR_1|RD_2,		0,		I1,		0,	0 },
{"pabsdiff.ob",		"X,Y,Q",	0x78000009, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		0,	0 },
{"pabsdiffc.ob",	"Y,Q",		0x78000035, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	SB1,		0,	0 },
{"pause",		"",		0x00000140, 0xffffffff, TRAP,			0,		I33,		0,	0 },
{"pavg.ob",		"X,Y,Q",	0x78000008, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		0,	0 },
{"pabsh",		"d,t",		0x70000168, 0xffe007ff, WR_1|RD_2,		0,		MMI,		0,	0 },
{"pabsw",		"d,t",		0x70000068, 0xffe007ff, WR_1|RD_2,		0,		MMI,		0,	0 },
{"paddsw",		"d,s,t",	0x70000408, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"paddub",		"d,s,t",	0x70000628, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"padduh",		"d,s,t",	0x70000528, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"padduw",		"d,s,t",	0x70000428, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"padsbh",		"d,s,t",	0x70000128, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pand",		"d,s,t",	0x70000489, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pand",		"D,S,T",	0x4bc00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* and  */
{"pceqb",		"d,s,t",	0x700002a8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pceqh",		"d,s,t",	0x700001a8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pceqw",		"d,s,t",	0x700000a8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pcgtb",		"d,s,t",	0x70000288, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pcgth",		"d,s,t",	0x70000188, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pcgtw",		"d,s,t",	0x70000088, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pcpyh",		"d,t",		0x700006e9, 0xffe007ff, WR_1|RD_2,		0,		MMI,		0,	0 },
{"pcpyld",		"d,s,t",	0x70000389, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pcpyud",		"d,s,t",	0x700003a9, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pdivbw",		"s,t",		0x70000749, 0xfc00ffff, RD_1|RD_2|WR_HILO,	0,		MMI,		0,	0 },
{"pdivuw",		"s,t",		0x70000369, 0xfc00ffff, RD_1|RD_2|WR_HILO,	0,		MMI,		0,	0 },
{"pdivw",		"s,t",		0x70000349, 0xfc00ffff, RD_1|RD_2|WR_HILO,	0,		MMI,		0,	0 },
{"pexch",		"d,t",		0x700006a9, 0xffe007ff, WR_1|RD_2,		0,		MMI,		0,	0 },
{"pexcw",		"d,t",		0x700007a9, 0xffe007ff, WR_1|RD_2,		0,		MMI,		0,	0 },
{"pexeh",		"d,t",		0x70000689, 0xffe007ff, WR_1|RD_2,		0,		MMI,		0,	0 },
{"pexew",		"d,t",		0x70000789, 0xffe007ff, WR_1|RD_2,		0,		MMI,		0,	0 },
{"pext5",		"d,t",		0x70000788, 0xffe007ff, WR_1|RD_2,		0,		MMI,		0,	0 },
{"pextlb",		"d,s,t",	0x70000688, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pextlh",		"d,s,t",	0x70000588, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pextlw",		"d,s,t",	0x70000488, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pextub",		"d,s,t",	0x700006a8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pextuh",		"d,s,t",	0x700005a8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pextuw",		"d,s,t",	0x700004a8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"phmadh",		"d,s,t",	0x70000449, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	0,		MMI,		0,	0 },
{"phmsbh",		"d,s,t",	0x70000549, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	0,		MMI,		0,	0 },
{"pickf.ob",		"X,Y,Q",	0x78000002, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"pickf.ob",		"D,S,Q",	0x48000002, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"pickf.qh",		"X,Y,Q",	0x78200002, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"pickt.ob",		"X,Y,Q",	0x78000003, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"pickt.ob",		"D,S,Q",	0x48000003, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"pickt.qh",		"X,Y,Q",	0x78200003, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"pinteh",		"d,s,t",	0x700002a9, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pinth",		"d,s,t",	0x70000289, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pll.ps",		"D,V,T",	0x46c0002c, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		I5_33,		0,	0 },
{"plu.ps",		"D,V,T",	0x46c0002d, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		I5_33,		0,	0 },
{"plzcw",		"d,s",		0x70000004, 0xfc1f07ff, WR_1|RD_2,		0,		MMI,		0,	0 },
{"pmaddh",		"d,s,t",	0x70000409, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	0,		MMI,		0,	0 },
{"pmadduw",		"d,s,t",	0x70000029, 0xfc0007ff, WR_1|RD_2|RD_3|MOD_HILO, 0,		MMI,		0,	0 },
{"pmaddw",		"d,s,t",	0x70000009, 0xfc0007ff, WR_1|RD_2|RD_3|MOD_HILO, 0,		MMI,		0,	0 },
{"pmaxh",		"d,s,t",	0x700001c8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pmaxw",		"d,s,t",	0x700000c8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pmfhi",		"d",		0x70000209, 0xffff07ff, WR_1|RD_HI,		0,		MMI,		0,	0 },
{"pmfhl.lh",		"d",		0x700000f0, 0xffff07ff, WR_1|RD_HILO,		0,		MMI,		0,	0 },
{"pmfhl.lw",		"d",		0x70000030, 0xffff07ff, WR_1|RD_HILO,		0,		MMI,		0,	0 },
{"pmfhl.sh",		"d",		0x70000130, 0xffff07ff, WR_1|RD_HILO,		0,		MMI,		0,	0 },
{"pmfhl.slw",		"d",		0x700000b0, 0xffff07ff, WR_1|RD_HILO,		0,		MMI,		0,	0 },
{"pmfhl.uw",		"d",		0x70000070, 0xffff07ff, WR_1|RD_HILO,		0,		MMI,		0,	0 },
{"pmflo",		"d",		0x70000249, 0xffff07ff, WR_1|RD_LO,		0,		MMI,		0,	0 },
{"pminh",		"d,s,t",	0x700001e8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pminw",		"d,s,t",	0x700000e8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pmsubh",		"d,s,t",	0x70000509, 0xfc0007ff, WR_1|RD_2|RD_3|MOD_HILO, 0,		MMI,		0,	0 },
{"pmsubw",		"d,s,t",	0x70000109, 0xfc0007ff, WR_1|RD_2|RD_3|MOD_HILO, 0,		MMI,		0,	0 },
{"pmthi",		"s",		0x70000229, 0xfc1fffff, RD_1|WR_HI,		0,		MMI,		0,	0 },
{"pmthl.lw",		"s",		0x70000031, 0xfc1fffff, RD_1|MOD_HILO,		0,		MMI,		0,	0 },
{"pmtlo",		"s",		0x70000269, 0xfc1fffff, RD_1|WR_LO,		0,		MMI,		0,	0 },
{"pmulth",		"d,s,t",	0x70000709, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	0,		MMI,		0,	0 },
{"pmultuw",		"d,s,t",	0x70000329, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	0,		MMI,		0,	0 },
{"pmultw",		"d,s,t",	0x70000309, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	0,		MMI,		0,	0 },
{"pnor",		"d,s,t",	0x700004e9, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pnor",		"D,S,T",	0x4ba00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* nor */
{"pop",			"d,v",		0x7000002c, 0xfc1f07ff, WR_1|RD_2,		0,		IOCT,		0,	0 },
{"por",			"d,s,t",	0x700004a9, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"por",			"D,S,T",	0x4b20000c, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* or */
{"ppac5",		"d,t",		0x700007c8, 0xffe007ff, WR_1|RD_2,		0,		MMI,		0,	0 },
{"ppacb",		"d,s,t",	0x700006c8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"ppach",		"d,s,t",	0x700005c8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"ppacw",		"d,s,t",	0x700004c8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"prevh",		"d,t",		0x700006c9, 0xffe007ff, WR_1|RD_2,		0,		MMI,		0,	0 },
{"prot3w",		"d,t",		0x700007c9, 0xffe007ff, WR_1|RD_2,		0,		MMI,		0,	0 },
{"psllvw",		"d,t,s",	0x70000089, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"psravw",		"d,t,s",	0x700000e9, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"psrlvw",		"d,t,s",	0x700000c9, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"psubsw",		"d,s,t",	0x70000448, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"psubub",		"d,s,t",	0x70000668, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"psubuh",		"d,s,t",	0x70000568, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"psubuw",		"d,s,t",	0x70000468, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pxor",		"d,s,t",	0x700004c9, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"pxor",		"D,S,T",	0x4b800002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* xor */
  /* pref and prefx are at the start of the table.  */
{"pul.ps",		"D,V,T",	0x46c0002e, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		I5_33,		0,	0 },
{"puu.ps",		"D,V,T",	0x46c0002f, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		I5_33,		0,	0 },
{"pperm",		"s,t",		0x70000481, 0xfc00ffff,	RD_1|RD_2|MOD_HILO,	0,		0,		SMT,	0 },
{"qfsrv",		"d,s,t",	0x700006e8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"qmac.00",		"s,t",		0x70000412, 0xfc00ffff, RD_1|RD_2|MOD_HILO,	0,		IOCT2,		0,	0 },
{"qmac.01",		"s,t",		0x70000452, 0xfc00ffff, RD_1|RD_2|MOD_HILO,	0,		IOCT2,		0,	0 },
{"qmac.02",		"s,t",		0x70000492, 0xfc00ffff, RD_1|RD_2|MOD_HILO,	0,		IOCT2,		0,	0 },
{"qmac.03",		"s,t",		0x700004d2, 0xfc00ffff, RD_1|RD_2|MOD_HILO,	0,		IOCT2,		0,	0 },
{"qmacs.00",		"s,t",		0x70000012, 0xfc00ffff, RD_1|RD_2|MOD_HILO,	0,		IOCT2,		0,	0 },
{"qmacs.01",		"s,t",		0x70000052, 0xfc00ffff, RD_1|RD_2|MOD_HILO,	0,		IOCT2,		0,	0 },
{"qmacs.02",		"s,t",		0x70000092, 0xfc00ffff, RD_1|RD_2|MOD_HILO,	0,		IOCT2,		0,	0 },
{"qmacs.03",		"s,t",		0x700000d2, 0xfc00ffff, RD_1|RD_2|MOD_HILO,	0,		IOCT2,		0,	0 },
{"rach.ob",		"X",		0x7a00003f, 0xfffff83f,	WR_1|FP_D,		RD_MACC,	SB1,		MX,	0 },
{"rach.ob",		"D",		0x4a00003f, 0xfffff83f,	WR_1|FP_D,		RD_MACC,	N54,		0,	0 },
{"rach.qh",		"X",		0x7a20003f, 0xfffff83f,	WR_1|FP_D,		RD_MACC,	0,		MX,	0 },
{"racl.ob",		"X",		0x7800003f, 0xfffff83f,	WR_1|FP_D,		RD_MACC,	SB1,		MX,	0 },
{"racl.ob",		"D",		0x4800003f, 0xfffff83f,	WR_1|FP_D,		RD_MACC,	N54,		0,	0 },
{"racl.qh",		"X",		0x7820003f, 0xfffff83f,	WR_1|FP_D,		RD_MACC,	0,		MX,	0 },
{"racm.ob",		"X",		0x7900003f, 0xfffff83f,	WR_1|FP_D,		RD_MACC,	SB1,		MX,	0 },
{"racm.ob",		"D",		0x4900003f, 0xfffff83f,	WR_1|FP_D,		RD_MACC,	N54,		0,	0 },
{"racm.qh",		"X",		0x7920003f, 0xfffff83f,	WR_1|FP_D,		RD_MACC,	0,		MX,	0 },
{"recip.d",		"D,S",		0x46200015, 0xffff003f, WR_1|RD_2|FP_D,		0,		I4_33,		0,	0 },
{"recip.ps",		"D,S",		0x46c00015, 0xffff003f, WR_1|RD_2|FP_D,		0,		SB1,		0,	0 },
{"recip.s",		"D,S",		0x46000015, 0xffff003f, WR_1|RD_2|FP_S,		0,		I4_33,		0,	0 },
{"recip1.d",		"D,S",		0x4620001d, 0xffff003f,	WR_1|RD_2|FP_D,		0,		0,		M3D,	0 },
{"recip1.ps",		"D,S",		0x46c0001d, 0xffff003f,	WR_1|RD_2|FP_S,		0,		0,		M3D,	0 },
{"recip1.s",		"D,S",		0x4600001d, 0xffff003f,	WR_1|RD_2|FP_S,		0,		0,		M3D,	0 },
{"recip2.d",		"D,S,T",	0x4620001c, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		M3D,	0 },
{"recip2.ps",		"D,S,T",	0x46c0001c, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		0,		M3D,	0 },
{"recip2.s",		"D,S,T",	0x4600001c, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		0,		M3D,	0 },
{"rem",			"z,s,t",	0x0000001a, 0xfc00ffff, RD_2|RD_3|WR_HILO,      0,		I1,		0,	0 },
{"rem",			"d,v,t",	0,    (int) M_REM_3,	INSN_MACRO,		0,		I1,		0,	0 },
{"rem",			"d,v,I",	0,    (int) M_REM_3I,	INSN_MACRO,		0,		I1,		0,	0 },
{"remu",		"z,s,t",	0x0000001b, 0xfc00ffff, RD_2|RD_3|WR_HILO,      0,		I1,		0,	0 },
{"remu",		"d,v,t",	0,    (int) M_REMU_3,	INSN_MACRO,		0,		I1,		0,	0 },
{"remu",		"d,v,I",	0,    (int) M_REMU_3I,	INSN_MACRO,		0,		I1,		0,	0 },
{"rdhwr",		"t,K",		0x7c00003b, 0xffe007ff, WR_1,			0,		I33,		0,	0 },
{"rdpgpr",		"d,w",		0x41400000, 0xffe007ff, WR_1,			0,		I33,		0,	0 },
/* rfe is moved below as it now conflicts with tlbgp */
{"rnas.qh",		"X,Q",		0x78200025, 0xfc20f83f,	WR_1|RD_2|FP_D,		RD_MACC,	0,		MX,	0 },
{"rnau.ob",		"X,Q",		0x78000021, 0xfc20f83f,	WR_1|RD_2|FP_D,		RD_MACC,	SB1,		MX,	0 },
{"rnau.qh",		"X,Q",		0x78200021, 0xfc20f83f,	WR_1|RD_2|FP_D,		RD_MACC,	0,		MX,	0 },
{"rnes.qh",		"X,Q",		0x78200026, 0xfc20f83f,	WR_1|RD_2|FP_D,		RD_MACC,	0,		MX,	0 },
{"rneu.ob",		"X,Q",		0x78000022, 0xfc20f83f,	WR_1|RD_2|FP_D,		RD_MACC,	SB1,		MX,	0 },
{"rneu.qh",		"X,Q",		0x78200022, 0xfc20f83f,	WR_1|RD_2|FP_D,		RD_MACC,	0,		MX,	0 },
{"rol",			"d,v,t",	0,    (int) M_ROL,	INSN_MACRO,		0,		I1,		0,	0 },
{"rol",			"d,v,I",	0,    (int) M_ROL_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"ror",			"d,v,t",	0,    (int) M_ROR,	INSN_MACRO,		0,		I1,		0,	0 },
{"ror",			"d,v,I",	0,    (int) M_ROR_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"ror",			"d,w,<",	0x00200002, 0xffe0003f,	WR_1|RD_2,		0,		N5|I33,		SMT,	0 },
{"rorv",		"d,t,s",	0x00000046, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		N5|I33,		SMT,	0 },
{"rotl",		"d,v,t",	0,    (int) M_ROL,	INSN_MACRO,		0,		I33,		SMT,	0 },
{"rotl",		"d,v,I",	0,    (int) M_ROL_I,	INSN_MACRO,		0,		I33,		SMT,	0 },
{"rotr",		"d,v,t",	0,    (int) M_ROR,	INSN_MACRO,		0,		I33,		SMT,	0 },
{"rotr",		"d,v,I",	0,    (int) M_ROR_I,	INSN_MACRO,		0,		I33,		SMT,	0 },
{"rotrv",		"d,t,s",	0x00000046, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I33,		SMT,	0 },
{"round.l.d",		"D,S",		0x46200008, 0xffff003f, WR_1|RD_2|FP_D,		0,		I3_33,		0,	0 },
{"round.l.s",		"D,S",		0x46000008, 0xffff003f, WR_1|RD_2|FP_S|FP_D,	0,		I3_33,		0,	0 },
{"round.w.d",		"D,S",		0x4620000c, 0xffff003f, WR_1|RD_2|FP_S|FP_D,	0,		I2,		0,	SF },
{"round.w.s",		"D,S",		0x4600000c, 0xffff003f, WR_1|RD_2|FP_S,		0,		I2,		0,	0 },
{"rsqrt.d",		"D,S",		0x46200016, 0xffff003f, WR_1|RD_2|FP_D,		0,		I4_33,		0,	0 },
{"rsqrt.ps",		"D,S",		0x46c00016, 0xffff003f, WR_1|RD_2|FP_D,		0,		SB1,		0,	0 },
{"rsqrt.s",		"D,S",		0x46000016, 0xffff003f, WR_1|RD_2|FP_S,		0,		I4_33,		0,	0 },
{"rsqrt.s",		"D,S,T",	0x46000016, 0xffe0003f, WR_1|RD_2|RD_3|FP_S,	0,		EE,		0,	0 },
{"rsqrt1.d",		"D,S",		0x4620001e, 0xffff003f,	WR_1|RD_2|FP_D,		0,		0,		M3D,	0 },
{"rsqrt1.ps",		"D,S",		0x46c0001e, 0xffff003f,	WR_1|RD_2|FP_S,		0,		0,		M3D,	0 },
{"rsqrt1.s",		"D,S",		0x4600001e, 0xffff003f,	WR_1|RD_2|FP_S,		0,		0,		M3D,	0 },
{"rsqrt2.d",		"D,S,T",	0x4620001f, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		M3D,	0 },
{"rsqrt2.ps",		"D,S,T",	0x46c0001f, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		0,		M3D,	0 },
{"rsqrt2.s",		"D,S,T",	0x4600001f, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		0,		M3D,	0 },
{"rzs.qh",		"X,Q",		0x78200024, 0xfc20f83f,	WR_1|RD_2|FP_D,		RD_MACC,	0,		MX,	0 },
{"rzu.ob",		"X,Q",		0x78000020, 0xfc20f83f,	WR_1|RD_2|FP_D,		RD_MACC,	SB1,		MX,	0 },
{"rzu.ob",		"D,Q",		0x48000020, 0xfc20f83f,	WR_1|RD_2|FP_D,		RD_MACC,	N54,		0,	0 },
{"rzu.qh",		"X,Q",		0x78200020, 0xfc20f83f,	WR_1|RD_2|FP_D,		RD_MACC,	0,		MX,	0 },
{"saa",			"t,A(b)",	0,    (int) M_SAA_AB,	INSN_MACRO,		0,		IOCTP,		0,	0 },
{"saa",			"t,(b)",	0x70000018, 0xfc00ffff, RD_1|RD_2|SM,		0,		IOCTP,		0,	0 },
{"saad",		"t,A(b)",	0,    (int) M_SAAD_AB,	INSN_MACRO,		0,		IOCTP,		0,	0 },
{"saad",		"t,(b)",	0x70000019, 0xfc00ffff,	RD_1|RD_2|SM,		0,		IOCTP,		0,	0 },
{"sb",			"t,o(b)",	0xa0000000, 0xfc000000,	RD_1|RD_3|SM,		0,		I1,		0,	0 },
{"sb",			"t,A(b)",	0,    (int) M_SB_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"sc",			"t,o(b)",	0xe0000000, 0xfc000000, MOD_1|RD_3|SM,		0,		I2,		0,	EE },
{"sc",			"t,A(b)",	0,    (int) M_SC_AB,	INSN_MACRO,		0,		I2,		0,	EE },
{"scd",			"t,o(b)",	0xf0000000, 0xfc000000, MOD_1|RD_3|SM,		0,		I3,		0,	EE },
{"scd",			"t,A(b)",	0,    (int) M_SCD_AB,	INSN_MACRO,		0,		I3,		0,	EE },
/* The macro has to be first to handle o32 correctly.  */
{"sd",			"t,A(b)",	0,    (int) M_SD_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"sd",			"t,o(b)",	0xfc000000, 0xfc000000,	RD_1|RD_3|SM,		0,		I3,		0,	0 },
{"sdbbp",		"",		0x0000000e, 0xffffffff,	TRAP,           	0,		G2,		0,	0 },
{"sdbbp",		"c",		0x0000000e, 0xfc00ffff,	TRAP,			0,		G2,		0,	0 },
{"sdbbp",		"c,q",		0x0000000e, 0xfc00003f,	TRAP,			0,		G2,		0,	0 },
{"sdbbp",		"",		0x7000003f, 0xffffffff, TRAP,           	0,		I32,		0,	0 },
{"sdbbp",		"B",		0x7000003f, 0xfc00003f, TRAP,           	0,		I32,		0,	0 },
{"sdc1",		"T,o(b)",	0xf4000000, 0xfc000000, RD_1|RD_3|SM|FP_D,	0,		I2,		0,	SF },
{"sdc1",		"E,o(b)",	0xf4000000, 0xfc000000, RD_1|RD_3|SM|FP_D,	0,		I2,		0,	SF },
{"sdc1",		"T,A(b)",	0,    (int) M_SDC1_AB,	INSN_MACRO,		INSN2_M_FP_D,	I2,		0,	SF },
{"sdc1",		"E,A(b)",	0,    (int) M_SDC1_AB,	INSN_MACRO,		INSN2_M_FP_D,	I2,		0,	SF },
{"sdc2",		"E,o(b)",	0xf8000000, 0xfc000000,	RD_3|RD_C2|SM,		0,		I2,		0,	IOCT|IOCTP|IOCT2|EE },
{"sdc2",		"E,A(b)",	0,    (int) M_SDC2_AB,	INSN_MACRO,		0,		I2,		0,	IOCT|IOCTP|IOCT2|EE },
{"sdc3",		"E,o(b)",	0xfc000000, 0xfc000000,	RD_3|RD_C3|SM,		0,		I2,		0,	IOCT|IOCTP|IOCT2|EE },
{"sdc3",		"E,A(b)",	0,    (int) M_SDC3_AB,	INSN_MACRO,		0,		I2,		0,	IOCT|IOCTP|IOCT2|EE },
{"s.d",			"T,o(b)",	0xf4000000, 0xfc000000, RD_1|RD_3|SM|FP_D,	0,		I2,		0,	SF },
{"s.d",			"T,A(b)",	0,    (int) M_S_DAB,	INSN_MACRO,		INSN2_M_FP_D,	I1,		0,	0 },
{"sdl",			"t,o(b)",	0xb0000000, 0xfc000000,	RD_1|RD_3|SM,		0,		I3,		0,	0 },
{"sdl",			"t,A(b)",	0,    (int) M_SDL_AB,	INSN_MACRO,		0,		I3,		0,	0 },
{"sdr",			"t,o(b)",	0xb4000000, 0xfc000000,	RD_1|RD_3|SM,		0,		I3,		0,	0 },
{"sdr",			"t,A(b)",	0,    (int) M_SDR_AB,	INSN_MACRO,		0,		I3,		0,	0 },
{"sdxc1",		"S,t(b)",	0x4c000009, 0xfc0007ff, RD_1|RD_2|RD_3|SM|FP_D,	0,		I4_33,		0,	0 },
{"seb",			"d,w",		0x7c000420, 0xffe007ff,	WR_1|RD_2,		0,		I33,		0,	0 },
{"seh",			"d,w",		0x7c000620, 0xffe007ff,	WR_1|RD_2,		0,		I33,		0,	0 },
{"selsl",		"d,v,t",	0x00000005, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		L1,		0,	0 },
{"selsr",		"d,v,t",	0x00000001, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		L1,		0,	0 },
{"seq",			"d,v,t",	0x7000002a, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		IOCT,		0,	0 },
{"seq",			"d,v,t",	0,    (int) M_SEQ,	INSN_MACRO,		0,		I1,		0,	0 },
{"seq",			"d,v,I",	0,    (int) M_SEQ_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"seq",			"S,T",		0x46a00032, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"seq",			"S,T",		0x4ba0000c, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"seqi",		"t,r,+Q",	0x7000002e, 0xfc00003f, WR_1|RD_2,		0,		IOCT,		0,	0 },
{"sge",			"d,v,t",	0,    (int) M_SGE,	INSN_MACRO,		0,		I1,		0,	0 },
{"sge",			"d,v,I",	0,    (int) M_SGE_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"sgeu",		"d,v,t",	0,    (int) M_SGEU,	INSN_MACRO,		0,		I1,		0,	0 },
{"sgeu",		"d,v,I",	0,    (int) M_SGEU_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"sgt",			"d,v,t",	0,    (int) M_SGT,	INSN_MACRO,		0,		I1,		0,	0 },
{"sgt",			"d,v,I",	0,    (int) M_SGT_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"sgtu",		"d,v,t",	0,    (int) M_SGTU,	INSN_MACRO,		0,		I1,		0,	0 },
{"sgtu",		"d,v,I",	0,    (int) M_SGTU_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"sh",			"t,o(b)",	0xa4000000, 0xfc000000,	RD_1|RD_3|SM,		0,		I1,		0,	0 },
{"sh",			"t,A(b)",	0,    (int) M_SH_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"shfl.bfla.qh",	"X,Y,Z",	0x7a20001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"shfl.mixh.ob",	"X,Y,Z",	0x7980001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"shfl.mixh.ob",	"D,S,T",	0x4980001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D, 	0,		N54,		0,	0 },
{"shfl.mixh.qh",	"X,Y,Z",	0x7820001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"shfl.mixl.ob",	"X,Y,Z",	0x79c0001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"shfl.mixl.ob",	"D,S,T",	0x49c0001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D, 	0,		N54,		0,	0 },
{"shfl.mixl.qh",	"X,Y,Z",	0x78a0001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"shfl.pach.ob",	"X,Y,Z",	0x7900001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"shfl.pach.ob",	"D,S,T",	0x4900001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D, 	0,		N54,		0,	0 },
{"shfl.pach.qh",	"X,Y,Z",	0x7920001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"shfl.pacl.ob",	"D,S,T",	0x4940001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D, 	0,		N54,		0,	0 },
{"shfl.repa.qh",	"X,Y,Z",	0x7b20001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"shfl.repb.qh",	"X,Y,Z",	0x7ba0001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"shfl.upsl.ob",	"X,Y,Z",	0x78c0001f, 0xffe0003f, WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"sle",			"d,v,t",	0,    (int) M_SLE,	INSN_MACRO,		0,		I1,		0,	0 },
{"sle",			"d,v,I",	0,    (int) M_SLE_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"sle",			"S,T",		0x46a0003e, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"sle",			"S,T",		0x4ba0000e, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"sleu",		"d,v,t",	0,    (int) M_SLEU,	INSN_MACRO,		0,		I1,		0,	0 },
{"sleu",		"d,v,I",	0,    (int) M_SLEU_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"sleu",		"S,T",		0x4680003e, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"sleu",		"S,T",		0x4b80000e, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"sllv",		"d,t,s",	0x00000004, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"sll",			"d,w,s",	0x00000004, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 }, /* sllv */
{"sll",			"d,w,<",	0x00000000, 0xffe0003f,	WR_1|RD_2,		0,		I1,		0,	0 },
{"sll",			"D,S,T",	0x45800002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"sll",			"D,S,T",	0x4b00000e, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"sll.ob",		"X,Y,Q",	0x78000010, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"sll.ob",		"D,S,Q",	0x48000010, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"sll.qh",		"X,Y,Q",	0x78200010, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"slt",			"d,v,t",	0x0000002a, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"slt",			"d,v,I",	0,    (int) M_SLT_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"slt",			"S,T",		0x46a0003c, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"slt",			"S,T",		0x4ba0000d, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"slti",		"t,r,j",	0x28000000, 0xfc000000,	WR_1|RD_2,		0,		I1,		0,	0 },
{"sltiu",		"t,r,j",	0x2c000000, 0xfc000000,	WR_1|RD_2,		0,		I1,		0,	0 },
{"sltu",		"d,v,t",	0x0000002b, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"sltu",		"d,v,I",	0,    (int) M_SLTU_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"sltu",		"S,T",		0x4680003c, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"sltu",		"S,T",		0x4b80000d, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"sne",			"d,v,t",	0x7000002b, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		IOCT,		0,	0 },
{"sne",			"d,v,t",	0,    (int) M_SNE,	INSN_MACRO,		0,		I1,		0,	0 },
{"sne",			"d,v,I",	0,    (int) M_SNE_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"snei",		"t,r,+Q",	0x7000002f, 0xfc00003f, WR_1|RD_2,		0,		IOCT,		0,	0 },
{"sq",			"t,o(b)",	0x7c000000, 0xfc000000,	RD_1|RD_3|SM,		0,		MMI,		0,	0 },
{"sq",			"t,A(b)",	0,    (int) M_SQ_AB,	INSN_MACRO,		0,		MMI,		0,	0 },
{"sqc2",		"+7,o(b)",	0xf8000000, 0xfc000000,	RD_3|RD_C2|SM,		0,		EE,		0,	0 },
{"sqc2",		"+7,A(b)",	0,    (int) M_SQC2_AB,	INSN_MACRO,		0,		EE,		0,	0 },
{"sqrt.d",		"D,S",		0x46200004, 0xffff003f, WR_1|RD_2|FP_D,		0,		I2,		0,	SF },
{"sqrt.s",		"D,S",		0x46000004, 0xffff003f, WR_1|RD_2|FP_S,		0,		I2,		0,	0 },
{"sqrt.ps",		"D,S",		0x46c00004, 0xffff003f, WR_1|RD_2|FP_D,		0,		SB1,		0,	0 },
{"srav",		"d,t,s",	0x00000007, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"sra",			"d,w,s",	0x00000007, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 }, /* srav */
{"sra",			"d,w,<",	0x00000003, 0xffe0003f,	WR_1|RD_2,		0,		I1,		0,	0 },
{"sra",			"D,S,T",	0x45c00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"sra",			"D,S,T",	0x4b40000f, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"sra.qh",		"X,Y,Q",	0x78200013, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"srlv",		"d,t,s",	0x00000006, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"srl",			"d,w,s",	0x00000006, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 }, /* srlv */
{"srl",			"d,w,<",	0x00000002, 0xffe0003f,	WR_1|RD_2,		0,		I1,		0,	0 },
{"srl",			"D,S,T",	0x45800003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"srl",			"D,S,T",	0x4b00000f, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"srl.ob",		"X,Y,Q",	0x78000012, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"srl.ob",		"D,S,Q",	0x48000012, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"srl.qh",		"X,Y,Q",	0x78200012, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
/* ssnop is at the start of the table.  */
{"standby",		"",		0x42000021, 0xffffffff,	0,			0,		V1,		0,	0 },
{"sub",			"d,v,t",	0x00000022, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"sub",			"d,v,I",	0,    (int) M_SUB_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"sub",			"D,S,T",	0x45c00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2E,		0,	0 },
{"sub",			"D,S,T",	0x4b40000d, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2F|IL3A,	0,	0 },
{"sub.d",		"D,V,T",	0x46200001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		I1,		0,	SF },
{"sub.s",		"D,V,T",	0x46000001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		I1,		0,	0 },
{"sub.ob",		"X,Y,Q",	0x7800000a, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"sub.ob",		"D,S,Q",	0x4800000a, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"sub.ps",		"D,V,T",	0x46c00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		I5_33|IL2F,	0,	0 },
{"sub.ps",		"D,V,T",	0x45600001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"sub.qh",		"X,Y,Q",	0x7820000a, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"suba.ob",		"Y,Q",		0x78000036, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	SB1,		MX,	0 },
{"suba.qh",		"Y,Q",		0x78200036, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	0,		MX,	0 },
{"subl.ob",		"Y,Q",		0x78000436, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	SB1,		MX,	0 },
{"subl.qh",		"Y,Q",		0x78200436, 0xfc2007ff,	RD_1|RD_2|FP_D,		WR_MACC,	0,		MX,	0 },
{"suba.s",		"S,T",		0x46000019, 0xffe007ff,	RD_1|RD_2|FP_S,		0,		EE,		0,	0 },
{"subu",		"d,v,t",	0x00000023, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"subu",		"d,v,I",	0,    (int) M_SUBU_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"subu",		"D,S,T",	0x45800001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2E,		0,	0 },
{"subu",		"D,S,T",	0x4b00000d, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	0,		IL2F|IL3A,	0,	0 },
{"suspend",		"",		0x42000022, 0xffffffff,	0,			0,		V1,		0,	0 },
{"suxc1",		"S,t(b)",	0x4c00000d, 0xfc0007ff, RD_1|RD_2|RD_3|SM|FP_D,	0,		I5_33|N55,	0,	0},
{"sw",			"t,o(b)",	0xac000000, 0xfc000000,	RD_1|RD_3|SM,		0,		I1,		0,	0 },
{"sw",			"t,A(b)",	0,    (int) M_SW_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"swapw",		"t,b",		0x70000014, 0xfc00ffff, MOD_1|RD_2|SM,		0,		XLR,		0,	0 },
{"swapwu",		"t,b",		0x70000015, 0xfc00ffff, MOD_1|RD_2|SM,		0,		XLR,		0,	0 },
{"swapd",		"t,b",		0x70000016, 0xfc00ffff, MOD_1|RD_2|SM,		0,		XLR,		0,	0 },
{"swc0",		"E,o(b)",	0xe0000000, 0xfc000000,	RD_3|RD_C0|SM,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"swc0",		"E,A(b)",	0,    (int) M_SWC0_AB,	INSN_MACRO,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"swc1",		"T,o(b)",	0xe4000000, 0xfc000000,	RD_1|RD_3|SM|FP_S,	0,		I1,		0,	0 },
{"swc1",		"E,o(b)",	0xe4000000, 0xfc000000,	RD_1|RD_3|SM|FP_S,	0,		I1,		0,	0 },
{"swc1",		"T,A(b)",	0,    (int) M_SWC1_AB,	INSN_MACRO,		INSN2_M_FP_S,	I1,		0,	0 },
{"swc1",		"E,A(b)",	0,    (int) M_SWC1_AB,	INSN_MACRO,		INSN2_M_FP_S,	I1,		0,	0 },
{"s.s",			"T,o(b)",	0xe4000000, 0xfc000000,	RD_1|RD_3|SM|FP_S,	0,		I1,		0,	0 }, /* swc1 */
{"s.s",			"T,A(b)",	0,    (int) M_SWC1_AB,	INSN_MACRO,		INSN2_M_FP_S,	I1,		0,	0 },
{"swc2",		"E,o(b)",	0xe8000000, 0xfc000000,	RD_3|RD_C2|SM,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"swc2",		"E,A(b)",	0,    (int) M_SWC2_AB,	INSN_MACRO,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"swc3",		"E,o(b)",	0xec000000, 0xfc000000,	RD_3|RD_C3|SM,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"swc3",		"E,A(b)",	0,    (int) M_SWC3_AB,	INSN_MACRO,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"swl",			"t,o(b)",	0xa8000000, 0xfc000000,	RD_1|RD_3|SM,		0,		I1,		0,	0 },
{"swl",			"t,A(b)",	0,    (int) M_SWL_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"scache",		"t,o(b)",	0xa8000000, 0xfc000000,	RD_1|RD_3,		0,		I2,		0,	0 }, /* same */
{"scache",		"t,A(b)",	0,    (int) M_SWL_AB,	INSN_MACRO,		0,		I2,		0,	0 }, /* as swl */
{"swr",			"t,o(b)",	0xb8000000, 0xfc000000,	RD_1|RD_3|SM,		0,		I1,		0,	0 },
{"swr",			"t,A(b)",	0,    (int) M_SWR_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"invalidate",		"t,o(b)",	0xb8000000, 0xfc000000,	RD_1|RD_3,		0,		I2,		0,	0 }, /* same */
{"invalidate",		"t,A(b)",	0,    (int) M_SWR_AB,	INSN_MACRO,		0,		I2,		0,	0 }, /* as swr */
{"swxc1",		"S,t(b)",	0x4c000008, 0xfc0007ff, RD_1|RD_2|RD_3|SM|FP_S,	0,		I4_33,		0,	0 },
{"synciobdma",		"",		0x0000008f, 0xffffffff,	NODS,			0,		IOCT,		0,	0 },
{"syncs",		"",		0x0000018f, 0xffffffff,	NODS,			0,		IOCT,		0,	0 },
{"syncw",		"",		0x0000010f, 0xffffffff,	NODS,			0,		IOCT,		0,	0 },
{"syncws",		"",		0x0000014f, 0xffffffff,	NODS,			0,		IOCT,		0,	0 },
{"sync_acquire",	"",		0x0000044f, 0xffffffff,	NODS,			0,		I33,		0,	0 },
{"sync_mb",		"",		0x0000040f, 0xffffffff,	NODS,			0,		I33,		0,	0 },
{"sync_release",	"",		0x0000048f, 0xffffffff,	NODS,			0,		I33,		0,	0 },
{"sync_rmb",		"",		0x000004cf, 0xffffffff,	NODS,			0,		I33,		0,	0 },
{"sync_wmb",		"",		0x0000010f, 0xffffffff,	NODS,			0,		I33,		0,	0 },
{"sync",		"",		0x0000000f, 0xffffffff,	NODS,			0,		I2|G1,		0,	0 },
{"sync",		"1",		0x0000000f, 0xfffff83f,	NODS,			0,		I32,		0,	0 },
{"sync.p",		"",		0x0000040f, 0xffffffff,	NODS,			0,		I2,		0,	0 },
{"sync.l",		"",		0x0000000f, 0xffffffff,	NODS,			0,		I2,		0,	0 },
{"synci",		"o(b)",		0x041f0000, 0xfc1f0000,	RD_2|SM,		0,		I33,		0,	0 },
{"syscall",		"",		0x0000000c, 0xffffffff,	TRAP,			0,		I1,		0,	0 },
{"syscall",		"B",		0x0000000c, 0xfc00003f,	TRAP,			0,		I1,		0,	0 },
{"teqi",		"s,j",		0x040c0000, 0xfc1f0000, RD_1|TRAP,		0,		I2,		0,	0 },
{"teq",			"s,t",		0x00000034, 0xfc00ffff, RD_1|RD_2|TRAP,		0,		I2,		0,	0 },
{"teq",			"s,t,q",	0x00000034, 0xfc00003f, RD_1|RD_2|TRAP,		0,		I2,		0,	0 },
{"teq",			"s,j",		0x040c0000, 0xfc1f0000, RD_1|TRAP,		0,		I2,		0,	0 }, /* teqi */
{"teq",			"s,I",		0,    (int) M_TEQ_I,	INSN_MACRO,		0,		I2,		0,	0 },
{"tgei",		"s,j",		0x04080000, 0xfc1f0000, RD_1|TRAP,		0,		I2,		0,	0 },
{"tge",			"s,t",		0x00000030, 0xfc00ffff,	RD_1|RD_2|TRAP,		0,		I2,		0,	0 },
{"tge",			"s,t,q",	0x00000030, 0xfc00003f,	RD_1|RD_2|TRAP,		0,		I2,		0,	0 },
{"tge",			"s,j",		0x04080000, 0xfc1f0000, RD_1|TRAP,		0,		I2,		0,	0 }, /* tgei */
{"tge",			"s,I",		0,    (int) M_TGE_I,    INSN_MACRO,		0,		I2,		0,	0 },
{"tgeiu",		"s,j",		0x04090000, 0xfc1f0000, RD_1|TRAP,		0,		I2,		0,	0 },
{"tgeu",		"s,t",		0x00000031, 0xfc00ffff, RD_1|RD_2|TRAP,		0,		I2,		0,	0 },
{"tgeu",		"s,t,q",	0x00000031, 0xfc00003f, RD_1|RD_2|TRAP,		0,		I2,		0,	0 },
{"tgeu",		"s,j",		0x04090000, 0xfc1f0000, RD_1|TRAP,		0,		I2,		0,	0 }, /* tgeiu */
{"tgeu",		"s,I",		0,    (int) M_TGEU_I,	INSN_MACRO,		0,		I2,		0,	0 },
{"tlbinv",		"",		0x42000003, 0xffffffff, INSN_TLB,       	0,		0,		TLBINV,	0 },
{"tlbinvf",		"",		0x42000004, 0xffffffff, INSN_TLB,       	0,		0,		TLBINV,	0 },
{"tlbp",		"",		0x42000008, 0xffffffff, INSN_TLB,       	0,		I1,		0,	0 },
{"tlbr",		"",		0x42000001, 0xffffffff, INSN_TLB,       	0,		I1,		0,	0 },
{"tlbwi",		"",		0x42000002, 0xffffffff, INSN_TLB,       	0,		I1,		0,	0 },
{"tlbwr",		"",		0x42000006, 0xffffffff, INSN_TLB,       	0,		I1,		0,	0 },
{"tlbgr",		"",		0x42000009, 0xffffffff, INSN_TLB,       	0,		0,		IVIRT,	0 },
{"tlbgwi",		"",		0x4200000a, 0xffffffff, INSN_TLB,       	0,		0,		IVIRT,	0 },
{"tlbginv",		"",		0x4200000b, 0xffffffff, INSN_TLB,       	0,		0,		IVIRT,	0 },
{"tlbginvf",		"",		0x4200000c, 0xffffffff, INSN_TLB,       	0,		0,		IVIRT,	0 },
{"tlbgwr",		"",		0x4200000e, 0xffffffff, INSN_TLB,       	0,		0,		IVIRT,	0 },
{"tlbgp",		"",		0x42000010, 0xffffffff, INSN_TLB,       	0,		0,		IVIRT,	0 },
{"tlti",		"s,j",		0x040a0000, 0xfc1f0000,	RD_1|TRAP,		0,		I2,		0,	0 },
{"tlt",			"s,t",		0x00000032, 0xfc00ffff, RD_1|RD_2|TRAP,		0,		I2,		0,	0 },
{"tlt",			"s,t,q",	0x00000032, 0xfc00003f, RD_1|RD_2|TRAP,		0,		I2,		0,	0 },
{"tlt",			"s,j",		0x040a0000, 0xfc1f0000,	RD_1|TRAP,		0,		I2,		0,	0 }, /* tlti */
{"tlt",			"s,I",		0,    (int) M_TLT_I,	INSN_MACRO,		0,		I2,		0,	0 },
{"tltiu",		"s,j",		0x040b0000, 0xfc1f0000, RD_1|TRAP,		0,		I2,		0,	0 },
{"tltu",		"s,t",		0x00000033, 0xfc00ffff, RD_1|RD_2|TRAP,		0,		I2,		0,	0 },
{"tltu",		"s,t,q",	0x00000033, 0xfc00003f, RD_1|RD_2|TRAP,		0,		I2,		0,	0 },
{"tltu",		"s,j",		0x040b0000, 0xfc1f0000, RD_1|TRAP,		0,		I2,		0,	0 }, /* tltiu */
{"tltu",		"s,I",		0,    (int) M_TLTU_I,	INSN_MACRO,		0,		I2,		0,	0 },
{"tnei",		"s,j",		0x040e0000, 0xfc1f0000, RD_1|TRAP,		0,		I2,		0,	0 },
{"tne",			"s,t",		0x00000036, 0xfc00ffff, RD_1|RD_2|TRAP,		0,		I2,		0,	0 },
{"tne",			"s,t,q",	0x00000036, 0xfc00003f, RD_1|RD_2|TRAP,		0,		I2,		0,	0 },
{"tne",			"s,j",		0x040e0000, 0xfc1f0000, RD_1|TRAP,		0,		I2,		0,	0 }, /* tnei */
{"tne",			"s,I",		0,    (int) M_TNE_I,	INSN_MACRO,		0,		I2,		0,	0 },
{"trunc.l.d",		"D,S",		0x46200009, 0xffff003f, WR_1|RD_2|FP_D,		0,		I3_33,		0,	0 },
{"trunc.l.s",		"D,S",		0x46000009, 0xffff003f,	WR_1|RD_2|FP_S|FP_D,	0,		I3_33,		0,	0 },
{"trunc.w.d",		"D,S",		0x4620000d, 0xffff003f, WR_1|RD_2|FP_S|FP_D,	0,		I2,		0,	SF },
{"trunc.w.d",		"D,S,x",	0x4620000d, 0xffff003f, WR_1|RD_2|FP_S|FP_D,	0,		I2,		0,	SF },
{"trunc.w.d",		"D,S,t",	0,    (int) M_TRUNCWD,	INSN_MACRO,		INSN2_M_FP_S|INSN2_M_FP_D, I1,	0,	SF },
{"trunc.w.s",		"D,S",		0x46000024, 0xffff003f,	WR_1|RD_2|FP_S,		0,		EE,		0,	0 },
{"trunc.w.s",		"D,S",		0x4600000d, 0xffff003f,	WR_1|RD_2|FP_S,		0,		I2,		0,	EE },
{"trunc.w.s",		"D,S,x",	0x4600000d, 0xffff003f,	WR_1|RD_2|FP_S,		0,		I2,		0,	EE },
{"trunc.w.s",		"D,S,t",	0,    (int) M_TRUNCWS,	INSN_MACRO,		INSN2_M_FP_S,	I1,		0,	EE },
{"uld",			"t,A(b)",	0,    (int) M_ULD_AB,	INSN_MACRO,		0,		I3,		0,	0 },
{"ulh",			"t,A(b)",	0,    (int) M_ULH_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"ulhu",		"t,A(b)",	0,    (int) M_ULHU_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"ulw",			"t,A(b)",	0,    (int) M_ULW_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"usd",			"t,A(b)",	0,    (int) M_USD_AB,	INSN_MACRO,		0,		I3,		0,	0 },
{"ush",			"t,A(b)",	0,    (int) M_USH_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"usw",			"t,A(b)",	0,    (int) M_USW_AB,	INSN_MACRO,		0,		I1,		0,	0 },
{"v3mulu",		"d,v,t",	0x70000011, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		IOCT,		0,	0 },
{"vmm0",		"d,v,t",	0x70000010, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		IOCT,		0,	0 },
{"vmulu",		"d,v,t",	0x7000000f, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		IOCT,		0,	0 },
{"wach.ob",		"Y",		0x7a00003e, 0xffff07ff,	RD_1|FP_D,		WR_MACC,	SB1,		MX,	0 },
{"wach.ob",		"S",		0x4a00003e, 0xffff07ff,	RD_1|FP_D,		WR_MACC,	N54,		0,	0 },
{"wach.qh",		"Y",		0x7a20003e, 0xffff07ff,	RD_1|FP_D,		WR_MACC,	0,		MX,	0 },
{"wacl.ob",		"Y,Z",		0x7800003e, 0xffe007ff,	RD_1|RD_2|FP_D,		WR_MACC,	SB1,		MX,	0 },
{"wacl.ob",		"S,T",		0x4800003e, 0xffe007ff,	RD_1|RD_2|FP_D,		WR_MACC,	N54,		0,	0 },
{"wacl.qh",		"Y,Z",		0x7820003e, 0xffe007ff,	RD_1|RD_2|FP_D,		WR_MACC,	0,		MX,	0 },
{"wait",		"",		0x42000020, 0xffffffff, NODS,   		0,		I3_32,		0,	0 },
{"wait",		"J",		0x42000020, 0xfe00003f, NODS,   		0,		I32|N55,	0,	0 },
{"waiti",		"",		0x42000020, 0xffffffff,	NODS,			0,		L1,		0,	0 },
{"wrpgpr",		"d,w",		0x41c00000, 0xffe007ff, RD_2,			0,		I33,		0,	0 },
{"wsbh",		"d,w",		0x7c0000a0, 0xffe007ff,	WR_1|RD_2,		0,		I33,		0,	0 },
{"xor",			"d,v,t",	0x00000026, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		I1,		0,	0 },
{"xor",			"t,r,I",	0,    (int) M_XOR_I,	INSN_MACRO,		0,		I1,		0,	0 },
{"xor",			"D,S,T",	0x47800002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"xor",			"D,S,T",	0x4b800002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"xor.ob",		"X,Y,Q",	0x7800000d, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		SB1,		MX,	0 },
{"xor.ob",		"D,S,Q",	0x4800000d, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		N54,		0,	0 },
{"xor.qh",		"X,Y,Q",	0x7820000d, 0xfc20003f,	WR_1|RD_2|RD_3|FP_D,	0,		0,		MX,	0 },
{"xori",		"t,r,i",	0x38000000, 0xfc000000,	WR_1|RD_2,		0,		I1,		0,	0 },
{"yield",		"s",		0x7c000009, 0xfc1fffff, RD_1|NODS,		0,		0,		MT32,	0 },
{"yield",		"d,s",		0x7c000009, 0xfc1f07ff, WR_1|RD_2|NODS,		0,		0,		MT32,	0 },
{"zcb",			"(b)",		0x7000071f, 0xfc1fffff, RD_1|SM,		0,		IOCT2,		0,	0 },
{"zcbt",		"(b)",		0x7000075f, 0xfc1fffff, RD_1|SM,		0,		IOCT2,		0,	0 },

/* User Defined Instruction.  */
{"udi0",		"s,t,d,+1",	0x70000010, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi0",		"s,t,+2",	0x70000010, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi0",		"s,+3",		0x70000010, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi0",		"+4",		0x70000010, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi1",		"s,t,d,+1",	0x70000011, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi1",		"s,t,+2",	0x70000011, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi1",		"s,+3",		0x70000011, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi1",		"+4",		0x70000011, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi2",		"s,t,d,+1",	0x70000012, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi2",		"s,t,+2",	0x70000012, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi2",		"s,+3",		0x70000012, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi2",		"+4",		0x70000012, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi3",		"s,t,d,+1",	0x70000013, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi3",		"s,t,+2",	0x70000013, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi3",		"s,+3",		0x70000013, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi3",		"+4",		0x70000013, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi4",		"s,t,d,+1",	0x70000014, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi4",		"s,t,+2",	0x70000014, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi4",		"s,+3",		0x70000014, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi4",		"+4",		0x70000014, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi5",		"s,t,d,+1",	0x70000015, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi5",		"s,t,+2",	0x70000015, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi5",		"s,+3",		0x70000015, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi5",		"+4",		0x70000015, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi6",		"s,t,d,+1",	0x70000016, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi6",		"s,t,+2",	0x70000016, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi6",		"s,+3",		0x70000016, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi6",		"+4",		0x70000016, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi7",		"s,t,d,+1",	0x70000017, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi7",		"s,t,+2",	0x70000017, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi7",		"s,+3",		0x70000017, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi7",		"+4",		0x70000017, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi8",		"s,t,d,+1",	0x70000018, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi8",		"s,t,+2",	0x70000018, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi8",		"s,+3",		0x70000018, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi8",		"+4",		0x70000018, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi9",		"s,t,d,+1",	0x70000019, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi9",		"s,t,+2",	0x70000019, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi9",		"s,+3",		0x70000019, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi9",		"+4",		0x70000019, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi10",		"s,t,d,+1",	0x7000001a, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi10",		"s,t,+2",	0x7000001a, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi10",		"s,+3",		0x7000001a, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi10",		"+4",		0x7000001a, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi11",		"s,t,d,+1",	0x7000001b, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi11",		"s,t,+2",	0x7000001b, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi11",		"s,+3",		0x7000001b, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi11",		"+4",		0x7000001b, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi12",		"s,t,d,+1",	0x7000001c, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi12",		"s,t,+2",	0x7000001c, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi12",		"s,+3",		0x7000001c, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi12",		"+4",		0x7000001c, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi13",		"s,t,d,+1",	0x7000001d, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi13",		"s,t,+2",	0x7000001d, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi13",		"s,+3",		0x7000001d, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi13",		"+4",		0x7000001d, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi14",		"s,t,d,+1",	0x7000001e, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi14",		"s,t,+2",	0x7000001e, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi14",		"s,+3",		0x7000001e, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi14",		"+4",		0x7000001e, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi15",		"s,t,d,+1",	0x7000001f, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi15",		"s,t,+2",	0x7000001f, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi15",		"s,+3",		0x7000001f, 0xfc00003f,	UDI,			0,		I33,		0,	0 },
{"udi15",		"+4",		0x7000001f, 0xfc00003f,	UDI,			0,		I33,		0,	0 },

/* Coprocessor 2 move/branch operations overlap with VR5400 .ob format
   instructions so they are here for the latters to take precedence.  */
{"bc2f",		"p",		0x49000000, 0xffff0000,	RD_CC|CBD,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"bc2f",		"N,p",		0x49000000, 0xffe30000,	RD_CC|CBD,		0,		I32,		0,	IOCT|IOCTP|IOCT2 },
{"bc2fl",		"p",		0x49020000, 0xffff0000,	RD_CC|CBL,		0,		I2|T3,		0,	IOCT|IOCTP|IOCT2 },
{"bc2fl",		"N,p",		0x49020000, 0xffe30000,	RD_CC|CBL,		0,		I32,		0,	IOCT|IOCTP|IOCT2 },
{"bc2t",		"p",		0x49010000, 0xffff0000,	RD_CC|CBD,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"bc2t",		"N,p",		0x49010000, 0xffe30000,	RD_CC|CBD,		0,		I32,		0,	IOCT|IOCTP|IOCT2 },
{"bc2tl",		"p",		0x49030000, 0xffff0000,	RD_CC|CBL,		0,		I2|T3,		0,	IOCT|IOCTP|IOCT2 },
{"bc2tl",		"N,p",		0x49030000, 0xffe30000,	RD_CC|CBL,		0,		I32,		0,	IOCT|IOCTP|IOCT2 },
{"cfc2",		"t,G",		0x48400000, 0xffe007ff,	WR_1|RD_C2|LCD,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"cfc2",		"t,+9",		0x48400000, 0xffe007ff,	WR_1|RD_C2|LCD,		0,		EE,		0,	0 },
{"cfc2.i",		"t,+9",		0x48400001, 0xffe007ff, WR_1|RD_C2|LCD,		0,		EE,		0,	0 },
{"cfc2.ni",		"t,+9",		0x48400000, 0xffe007ff, WR_1|RD_C2|LCD,		0,		EE,		0,	0 },
{"ctc2",		"t,G",		0x48c00000, 0xffe007ff,	RD_1|WR_CC|COD,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"ctc2",		"t,+9",		0x48c00000, 0xffe007ff,	RD_1|WR_CC|COD,		0,		EE,		0,	0 },
{"ctc2.i",		"t,+9",		0x48c00001, 0xffe007ff, RD_1|WR_CC|COD,		0,		EE,		0,	0 },
{"ctc2.ni",		"t,+9",		0x48c00000, 0xffe007ff, RD_1|WR_CC|COD,		0,		EE,		0,	0 },
{"dmfc2",		"t,i",		0x48200000, 0xffe00000,	WR_1|RD_C2|LCD,		0,		IOCT,		0,	0 },
{"dmfc2",		"t,G",		0x48200000, 0xffe007ff,	WR_1|RD_C2|LCD,		0,		I3,		0,	IOCT|IOCTP|IOCT2|EE },
{"dmfc2",		"t,G,H",	0x48200000, 0xffe007f8,	WR_1|RD_C2|LCD,		0,		I64,		0,	IOCT|IOCTP|IOCT2 },
{"dmtc2",		"t,i",		0x48a00000, 0xffe00000,	RD_1|WR_C2|WR_CC|COD,	0,		IOCT,		0,	0 },
{"dmtc2",		"t,G",		0x48a00000, 0xffe007ff,	RD_1|WR_C2|WR_CC|COD,	0,		I3,		0,	IOCT|IOCTP|IOCT2|EE },
{"dmtc2",		"t,G,H",	0x48a00000, 0xffe007f8,	RD_1|WR_C2|WR_CC|COD,	0,		I64,		0,	IOCT|IOCTP|IOCT2 },
{"mfc2",		"t,G",		0x48000000, 0xffe007ff,	WR_1|RD_C2|LCD,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"mfc2",		"t,G,H",	0x48000000, 0xffe007f8,	WR_1|RD_C2|LCD,		0,		I32,		0,	IOCT|IOCTP|IOCT2 },
{"mfhc2",		"t,G",		0x48600000, 0xffe007ff,	WR_1|RD_C2|LCD,		0,		I33,		0,	IOCT|IOCTP|IOCT2 },
{"mfhc2",		"t,G,H",	0x48600000, 0xffe007f8,	WR_1|RD_C2|LCD,		0,		I33,		0,	IOCT|IOCTP|IOCT2 },
{"mfhc2",		"t,i",		0x48600000, 0xffe00000,	WR_1|RD_C2|LCD,		0,		I33,		0,	IOCT|IOCTP|IOCT2 },
{"mtc2",		"t,G",		0x48800000, 0xffe007ff,	RD_1|WR_C2|WR_CC|COD,	0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"mtc2",		"t,G,H",	0x48800000, 0xffe007f8,	RD_1|WR_C2|WR_CC|COD,	0,		I32,		0,	IOCT|IOCTP|IOCT2 },
{"mthc2",		"t,G",		0x48e00000, 0xffe007ff,	RD_1|WR_C2|WR_CC|COD,	0,		I33,		0,	IOCT|IOCTP|IOCT2 },
{"mthc2",		"t,G,H",	0x48e00000, 0xffe007f8,	RD_1|WR_C2|WR_CC|COD,	0,		I33,		0,	IOCT|IOCTP|IOCT2 },
{"mthc2",		"t,i",		0x48e00000, 0xffe00000,	RD_1|WR_C2|WR_CC|COD,	0,		I33,		0,	IOCT|IOCTP|IOCT2 },
{"qmfc2",		"t,+6",		0x48200000, 0xffe007ff, WR_1|RD_C2,		0,		EE,		0,	0 },
{"qmfc2.i",		"t,+6",		0x48200001, 0xffe007ff,	WR_1|RD_C2,		0,		EE,		0,	0 },
{"qmfc2.ni",		"t,+6",		0x48200000, 0xffe007ff,	WR_1|RD_C2,		0,		EE,		0,	0 },
{"qmtc2",		"t,+6",		0x48a00000, 0xffe007ff,	RD_1|WR_C2,		0,		EE,		0,	0 },
{"qmtc2.i",		"t,+6",		0x48a00001, 0xffe007ff,	RD_1|WR_C2,		0,		EE,		0,	0 },
{"qmtc2.ni",		"t,+6",		0x48a00000, 0xffe007ff,	RD_1|WR_C2,		0,		EE,		0,	0 },
/* Coprocessor 3 move/branch operations overlap with MIPS IV COP1X 
   instructions, so they are here for the latters to take precedence.  */
{"bc3f",		"p",		0x4d000000, 0xffff0000,	RD_CC|CBD,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"bc3fl",		"p",		0x4d020000, 0xffff0000,	RD_CC|CBL,		0,		I2|T3,		0,	IOCT|IOCTP|IOCT2|EE },
{"bc3t",		"p",		0x4d010000, 0xffff0000,	RD_CC|CBD,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"bc3tl",		"p",		0x4d030000, 0xffff0000,	RD_CC|CBL,		0,		I2|T3,		0,	IOCT|IOCTP|IOCT2|EE },
{"cfc3",		"t,G",		0x4c400000, 0xffe007ff,	WR_1|RD_C3|LCD,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"ctc3",		"t,G",		0x4cc00000, 0xffe007ff,	RD_1|WR_CC|COD,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"dmfc3",		"t,G",		0x4c200000, 0xffe007ff,	WR_1|RD_C3|LCD,		0,		I3,		0,	IOCT|IOCTP|IOCT2|EE },
{"dmtc3",		"t,G",		0x4ca00000, 0xffe007ff,	RD_1|WR_C3|WR_CC|COD,	0,		I3,		0,	IOCT|IOCTP|IOCT2|EE },
{"mfc3",		"t,G",		0x4c000000, 0xffe007ff,	WR_1|RD_C3|LCD,		0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"mfc3",		"t,G,H",	0x4c000000, 0xffe007f8,	WR_1|RD_C3|LCD,		0,		I32,		0,	IOCT|IOCTP|IOCT2|EE },
{"mtc3",		"t,G",		0x4c800000, 0xffe007ff,	RD_1|WR_C3|WR_CC|COD,	0,		I1,		0,	IOCT|IOCTP|IOCT2|EE },
{"mtc3",		"t,G,H",	0x4c800000, 0xffe007f8,	RD_1|WR_C3|WR_CC|COD,	0,		I32,		0,	IOCT|IOCTP|IOCT2|EE },

  /* Conflicts with the 4650's "mul" instruction.  Nobody's using the
     4010 any more, so move this insn out of the way.  If the object
     format gave us more info, we could do this right.  */
{"addciu",		"t,r,j",	0x70000000, 0xfc000000,	WR_1|RD_2,		0,		L1,		0,	0 },
/* MIPS DSP ASE */
{"absq_s.ph",		"d,t",		0x7c000252, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"absq_s.pw",		"d,t",		0x7c000456, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"absq_s.qh",		"d,t",		0x7c000256, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"absq_s.w",		"d,t",		0x7c000452, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"addq.ph",		"d,s,t",	0x7c000290, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"addq.pw",		"d,s,t",	0x7c000494, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"addq.qh",		"d,s,t",	0x7c000294, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"addq_s.ph",		"d,s,t",	0x7c000390, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"addq_s.pw",		"d,s,t",	0x7c000594, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"addq_s.qh",		"d,s,t",	0x7c000394, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"addq_s.w",		"d,s,t",	0x7c000590, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"addsc",		"d,s,t",	0x7c000410, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"addu.ob",		"d,s,t",	0x7c000014, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"addu.qb",		"d,s,t",	0x7c000010, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"addu_s.ob",		"d,s,t",	0x7c000114, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"addu_s.qb",		"d,s,t",	0x7c000110, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"addwc",		"d,s,t",	0x7c000450, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"bitrev",		"d,t",		0x7c0006d2, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"bposge32",		"p",		0x041c0000, 0xffff0000, CBD,			0,		0,		D32,	0 },
{"bposge64",		"p",		0x041d0000, 0xffff0000, CBD,			0,		0,		D64,	0 },
{"cmp.eq.ph",		"s,t",		0x7c000211, 0xfc00ffff, RD_1|RD_2,		0,		0,		D32,	0 },
{"cmp.eq.pw",		"s,t",		0x7c000415, 0xfc00ffff, RD_1|RD_2,		0,		0,		D64,	0 },
{"cmp.eq.qh",		"s,t",		0x7c000215, 0xfc00ffff, RD_1|RD_2,		0,		0,		D64,	0 },
{"cmpgu.eq.ob",		"d,s,t",	0x7c000115, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"cmpgu.eq.qb",		"d,s,t",	0x7c000111, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"cmpgu.le.ob",		"d,s,t",	0x7c000195, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"cmpgu.le.qb",		"d,s,t",	0x7c000191, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"cmpgu.lt.ob",		"d,s,t",	0x7c000155, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"cmpgu.lt.qb",		"d,s,t",	0x7c000151, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"cmp.le.ph",		"s,t",		0x7c000291, 0xfc00ffff, RD_1|RD_2,		0,		0,		D32,	0 },
{"cmp.le.pw",		"s,t",		0x7c000495, 0xfc00ffff, RD_1|RD_2,		0,		0,		D64,	0 },
{"cmp.le.qh",		"s,t",		0x7c000295, 0xfc00ffff, RD_1|RD_2,		0,		0,		D64,	0 },
{"cmp.lt.ph",		"s,t",		0x7c000251, 0xfc00ffff, RD_1|RD_2,		0,		0,		D32,	0 },
{"cmp.lt.pw",		"s,t",		0x7c000455, 0xfc00ffff, RD_1|RD_2,		0,		0,		D64,	0 },
{"cmp.lt.qh",		"s,t",		0x7c000255, 0xfc00ffff, RD_1|RD_2,		0,		0,		D64,	0 },
{"cmpu.eq.ob",		"s,t",		0x7c000015, 0xfc00ffff, RD_1|RD_2,		0,		0,		D64,	0 },
{"cmpu.eq.qb",		"s,t",		0x7c000011, 0xfc00ffff, RD_1|RD_2,		0,		0,		D32,	0 },
{"cmpu.le.ob",		"s,t",		0x7c000095, 0xfc00ffff, RD_1|RD_2,		0,		0,		D64,	0 },
{"cmpu.le.qb",		"s,t",		0x7c000091, 0xfc00ffff, RD_1|RD_2,		0,		0,		D32,	0 },
{"cmpu.lt.ob",		"s,t",		0x7c000055, 0xfc00ffff, RD_1|RD_2,		0,		0,		D64,	0 },
{"cmpu.lt.qb",		"s,t",		0x7c000051, 0xfc00ffff, RD_1|RD_2,		0,		0,		D32,	0 },
{"dextpdp",		"t,7,6",	0x7c0002bc, 0xfc00e7ff, WR_1|RD_a|DSP_VOLA,	0,		0,		D64,	0 },
{"dextpdpv",		"t,7,s",	0x7c0002fc, 0xfc00e7ff, WR_1|RD_3|RD_a|DSP_VOLA, 0,		0,		D64,	0 },
{"dextp",		"t,7,6",	0x7c0000bc, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D64,	0 },
{"dextpv",		"t,7,s",	0x7c0000fc, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D64,	0 },
{"dextr.l",		"t,7,6",	0x7c00043c, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D64,	0 },
{"dextr_r.l",		"t,7,6",	0x7c00053c, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D64,	0 },
{"dextr_rs.l",		"t,7,6",	0x7c0005bc, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D64,	0 },
{"dextr_rs.w",		"t,7,6",	0x7c0001bc, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D64,	0 },
{"dextr_r.w",		"t,7,6",	0x7c00013c, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D64,	0 },
{"dextr_s.h",		"t,7,6",	0x7c0003bc, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D64,	0 },
{"dextrv.l",		"t,7,s",	0x7c00047c, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D64,	0 },
{"dextrv_r.l",		"t,7,s",	0x7c00057c, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D64,	0 },
{"dextrv_rs.l",		"t,7,s",	0x7c0005fc, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D64,	0 },
{"dextrv_rs.w",		"t,7,s",	0x7c0001fc, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D64,	0 },
{"dextrv_r.w",		"t,7,s",	0x7c00017c, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D64,	0 },
{"dextrv_s.h",		"t,7,s",	0x7c0003fc, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D64,	0 },
{"dextrv.w",		"t,7,s",	0x7c00007c, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D64,	0 },
{"dextr.w",		"t,7,6",	0x7c00003c, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D64,	0 },
{"dinsv",		"t,s",		0x7c00000d, 0xfc00ffff, WR_1|RD_2,		0,		0,		D64,	0 },
{"dmadd",		"7,s,t",	0x7c000674, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"dmaddu",		"7,s,t",	0x7c000774, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"dmsub",		"7,s,t",	0x7c0006f4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"dmsubu",		"7,s,t",	0x7c0007f4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"dmthlip",		"s,7",		0x7c0007fc, 0xfc1fe7ff, RD_1|MOD_a|DSP_VOLA,	0,		0,		D64,	0 },
{"dpaq_sa.l.pw",	"7,s,t",	0x7c000334, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"dpaq_sa.l.w",		"7,s,t",	0x7c000330, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"dpaq_s.w.ph",		"7,s,t",	0x7c000130, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"dpaq_s.w.qh",		"7,s,t",	0x7c000134, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"dpau.h.obl",		"7,s,t",	0x7c0000f4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"dpau.h.obr",		"7,s,t",	0x7c0001f4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"dpau.h.qbl",		"7,s,t",	0x7c0000f0, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"dpau.h.qbr",		"7,s,t",	0x7c0001f0, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"dpsq_sa.l.pw",	"7,s,t",	0x7c000374, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"dpsq_sa.l.w",		"7,s,t",	0x7c000370, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"dpsq_s.w.ph",		"7,s,t",	0x7c000170, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"dpsq_s.w.qh",		"7,s,t",	0x7c000174, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"dpsu.h.obl",		"7,s,t",	0x7c0002f4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"dpsu.h.obr",		"7,s,t",	0x7c0003f4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"dpsu.h.qbl",		"7,s,t",	0x7c0002f0, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"dpsu.h.qbr",		"7,s,t",	0x7c0003f0, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"dshilo",		"7,:",		0x7c0006bc, 0xfc07e7ff, MOD_a,			0,		0,		D64,	0 },
{"dshilov",		"7,s",		0x7c0006fc, 0xfc1fe7ff, RD_2|MOD_a,		0,		0,		D64,	0 },
{"extpdp",		"t,7,6",	0x7c0002b8, 0xfc00e7ff, WR_1|RD_a|DSP_VOLA,	0,		0,		D32,	0 },
{"extpdpv",		"t,7,s",	0x7c0002f8, 0xfc00e7ff, WR_1|RD_3|RD_a|DSP_VOLA, 0,		0,		D32,	0 },
{"extp",		"t,7,6",	0x7c0000b8, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D32,	0 },
{"extpv",		"t,7,s",	0x7c0000f8, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D32,	0 },
{"extr_rs.w",		"t,7,6",	0x7c0001b8, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D32,	0 },
{"extr_r.w",		"t,7,6",	0x7c000138, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D32,	0 },
{"extr_s.h",		"t,7,6",	0x7c0003b8, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D32,	0 },
{"extrv_rs.w",		"t,7,s",	0x7c0001f8, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D32,	0 },
{"extrv_r.w",		"t,7,s",	0x7c000178, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D32,	0 },
{"extrv_s.h",		"t,7,s",	0x7c0003f8, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D32,	0 },
{"extrv.w",		"t,7,s",	0x7c000078, 0xfc00e7ff, WR_1|RD_3|RD_a,		0,		0,		D32,	0 },
{"extr.w",		"t,7,6",	0x7c000038, 0xfc00e7ff, WR_1|RD_a,		0,		0,		D32,	0 },
{"insv",		"t,s",		0x7c00000c, 0xfc00ffff, WR_1|RD_2,		0,		0,		D32,	0 },
/* lbux, ldx, lhx and lwx are the basic instruction section.  */
{"maq_sa.w.phl",	"7,s,t",	0x7c000430, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"maq_sa.w.phr",	"7,s,t",	0x7c0004b0, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"maq_sa.w.qhll",	"7,s,t",	0x7c000434, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"maq_sa.w.qhlr",	"7,s,t",	0x7c000474, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"maq_sa.w.qhrl",	"7,s,t",	0x7c0004b4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"maq_sa.w.qhrr",	"7,s,t",	0x7c0004f4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"maq_s.l.pwl",		"7,s,t",	0x7c000734, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"maq_s.l.pwr",		"7,s,t",	0x7c0007b4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"maq_s.w.phl",		"7,s,t",	0x7c000530, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"maq_s.w.phr",		"7,s,t",	0x7c0005b0, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"maq_s.w.qhll",	"7,s,t",	0x7c000534, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"maq_s.w.qhlr",	"7,s,t",	0x7c000574, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"maq_s.w.qhrl",	"7,s,t",	0x7c0005b4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"maq_s.w.qhrr",	"7,s,t",	0x7c0005f4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"modsub",		"d,s,t",	0x7c000490, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"mthlip",		"s,7",		0x7c0007f8, 0xfc1fe7ff, RD_1|MOD_a|DSP_VOLA,	0,		0,		D32,	0 },
{"muleq_s.pw.qhl",	"d,s,t",	0x7c000714, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,		0,		D64,	0 },
{"muleq_s.pw.qhr",	"d,s,t",	0x7c000754, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,		0,		D64,	0 },
{"muleq_s.w.phl",	"d,s,t",	0x7c000710, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,		0,		D32,	0 },
{"muleq_s.w.phr",	"d,s,t",	0x7c000750, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,		0,		D32,	0 },
{"muleu_s.ph.qbl",	"d,s,t",	0x7c000190, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,		0,		D32,	0 },
{"muleu_s.ph.qbr",	"d,s,t",	0x7c0001d0, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,		0,		D32,	0 },
{"muleu_s.qh.obl",	"d,s,t",	0x7c000194, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,		0,		D64,	0 },
{"muleu_s.qh.obr",	"d,s,t",	0x7c0001d4, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,		0,		D64,	0 },
{"mulq_rs.ph",		"d,s,t",	0x7c0007d0, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	0,		0,		D32,	0 },
{"mulq_rs.qh",		"d,s,t",	0x7c0007d4, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO,	0,		0,		D64,	0 },
{"mulsaq_s.l.pw",	"7,s,t",	0x7c0003b4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"mulsaq_s.w.ph",	"7,s,t",	0x7c0001b0, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D32,	0 },
{"mulsaq_s.w.qh",	"7,s,t",	0x7c0001b4, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,		0,		D64,	0 },
{"packrl.ph",		"d,s,t",	0x7c000391, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"packrl.pw",		"d,s,t",	0x7c000395, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"pick.ob",		"d,s,t",	0x7c0000d5, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"pick.ph",		"d,s,t",	0x7c0002d1, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"pick.pw",		"d,s,t",	0x7c0004d5, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"pick.qb",		"d,s,t",	0x7c0000d1, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"pick.qh",		"d,s,t",	0x7c0002d5, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"preceq.pw.qhla",	"d,t",		0x7c000396, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"preceq.pw.qhl",	"d,t",		0x7c000316, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"preceq.pw.qhra",	"d,t",		0x7c0003d6, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"preceq.pw.qhr",	"d,t",		0x7c000356, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"preceq.s.l.pwl",	"d,t",		0x7c000516, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"preceq.s.l.pwr",	"d,t",		0x7c000556, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"precequ.ph.qbla",	"d,t",		0x7c000192, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"precequ.ph.qbl",	"d,t",		0x7c000112, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"precequ.ph.qbra",	"d,t",		0x7c0001d2, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"precequ.ph.qbr",	"d,t",		0x7c000152, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"precequ.pw.qhla",	"d,t",		0x7c000196, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"precequ.pw.qhl",	"d,t",		0x7c000116, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"precequ.pw.qhra",	"d,t",		0x7c0001d6, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"precequ.pw.qhr",	"d,t",		0x7c000156, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"preceq.w.phl",	"d,t",		0x7c000312, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"preceq.w.phr",	"d,t",		0x7c000352, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"preceu.ph.qbla",	"d,t",		0x7c000792, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"preceu.ph.qbl",	"d,t",		0x7c000712, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"preceu.ph.qbra",	"d,t",		0x7c0007d2, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"preceu.ph.qbr",	"d,t",		0x7c000752, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"preceu.qh.obla",	"d,t",		0x7c000796, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"preceu.qh.obl",	"d,t",		0x7c000716, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"preceu.qh.obra",	"d,t",		0x7c0007d6, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"preceu.qh.obr",	"d,t",		0x7c000756, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"precrq.ob.qh",	"d,s,t",	0x7c000315, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"precrq.ph.w",		"d,s,t",	0x7c000511, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"precrq.pw.l",		"d,s,t",	0x7c000715, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"precrq.qb.ph",	"d,s,t",	0x7c000311, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"precrq.qh.pw",	"d,s,t",	0x7c000515, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"precrq_rs.ph.w",	"d,s,t",	0x7c000551, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"precrq_rs.qh.pw",	"d,s,t",	0x7c000555, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"precrqu_s.ob.qh",	"d,s,t",	0x7c0003d5, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"precrqu_s.qb.ph",	"d,s,t",	0x7c0003d1, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"raddu.l.ob",		"d,s",		0x7c000514, 0xfc1f07ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"raddu.w.qb",		"d,s",		0x7c000510, 0xfc1f07ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"rddsp",		"d",		0x7fff04b8, 0xffff07ff, WR_1,			0,		0,		D32,	0 },
{"rddsp",		"d,'",		0x7c0004b8, 0xffc007ff, WR_1,			0,		0,		D32,	0 },
{"repl.ob",		"d,5",		0x7c000096, 0xff0007ff, WR_1,			0,		0,		D64,	0 },
{"repl.ph",		"d,@",		0x7c000292, 0xfc0007ff, WR_1,			0,		0,		D32,	0 },
{"repl.pw",		"d,@",		0x7c000496, 0xfc0007ff, WR_1,			0,		0,		D64,	0 },
{"repl.qb",		"d,5",		0x7c000092, 0xff0007ff, WR_1,			0,		0,		D32,	0 },
{"repl.qh",		"d,@",		0x7c000296, 0xfc0007ff, WR_1,			0,		0,		D64,	0 },
{"replv.ob",		"d,t",		0x7c0000d6, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"replv.ph",		"d,t",		0x7c0002d2, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"replv.pw",		"d,t",		0x7c0004d6, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"replv.qb",		"d,t",		0x7c0000d2, 0xffe007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"replv.qh",		"d,t",		0x7c0002d6, 0xffe007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"shilo",		"7,0",		0x7c0006b8, 0xfc0fe7ff, MOD_a,			0,		0,		D32,	0 },
{"shilov",		"7,s",		0x7c0006f8, 0xfc1fe7ff, RD_2|MOD_a,		0,		0,		D32,	0 },
{"shll.ob",		"d,t,3",	0x7c000017, 0xff0007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"shll.ph",		"d,t,4",	0x7c000213, 0xfe0007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"shll.pw",		"d,t,6",	0x7c000417, 0xfc0007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"shll.qb",		"d,t,3",	0x7c000013, 0xff0007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"shll.qh",		"d,t,4",	0x7c000217, 0xfe0007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"shll_s.ph",		"d,t,4",	0x7c000313, 0xfe0007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"shll_s.pw",		"d,t,6",	0x7c000517, 0xfc0007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"shll_s.qh",		"d,t,4",	0x7c000317, 0xfe0007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"shll_s.w",		"d,t,6",	0x7c000513, 0xfc0007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"shllv.ob",		"d,t,s",	0x7c000097, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"shllv.ph",		"d,t,s",	0x7c000293, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"shllv.pw",		"d,t,s",	0x7c000497, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"shllv.qb",		"d,t,s",	0x7c000093, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"shllv.qh",		"d,t,s",	0x7c000297, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"shllv_s.ph",		"d,t,s",	0x7c000393, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"shllv_s.pw",		"d,t,s",	0x7c000597, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"shllv_s.qh",		"d,t,s",	0x7c000397, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"shllv_s.w",		"d,t,s",	0x7c000593, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"shra.ph",		"d,t,4",	0x7c000253, 0xfe0007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"shra.pw",		"d,t,6",	0x7c000457, 0xfc0007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"shra.qh",		"d,t,4",	0x7c000257, 0xfe0007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"shra_r.ph",		"d,t,4",	0x7c000353, 0xfe0007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"shra_r.pw",		"d,t,6",	0x7c000557, 0xfc0007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"shra_r.qh",		"d,t,4",	0x7c000357, 0xfe0007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"shra_r.w",		"d,t,6",	0x7c000553, 0xfc0007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"shrav.ph",		"d,t,s",	0x7c0002d3, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"shrav.pw",		"d,t,s",	0x7c0004d7, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"shrav.qh",		"d,t,s",	0x7c0002d7, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"shrav_r.ph",		"d,t,s",	0x7c0003d3, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"shrav_r.pw",		"d,t,s",	0x7c0005d7, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"shrav_r.qh",		"d,t,s",	0x7c0003d7, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"shrav_r.w",		"d,t,s",	0x7c0005d3, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"shrl.ob",		"d,t,3",	0x7c000057, 0xff0007ff, WR_1|RD_2,		0,		0,		D64,	0 },
{"shrl.qb",		"d,t,3",	0x7c000053, 0xff0007ff, WR_1|RD_2,		0,		0,		D32,	0 },
{"shrlv.ob",		"d,t,s",	0x7c0000d7, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"shrlv.qb",		"d,t,s",	0x7c0000d3, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"subq.ph",		"d,s,t",	0x7c0002d0, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"subq.pw",		"d,s,t",	0x7c0004d4, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"subq.qh",		"d,s,t",	0x7c0002d4, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"subq_s.ph",		"d,s,t",	0x7c0003d0, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"subq_s.pw",		"d,s,t",	0x7c0005d4, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"subq_s.qh",		"d,s,t",	0x7c0003d4, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"subq_s.w",		"d,s,t",	0x7c0005d0, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"subu.ob",		"d,s,t",	0x7c000054, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"subu.qb",		"d,s,t",	0x7c000050, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"subu_s.ob",		"d,s,t",	0x7c000154, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D64,	0 },
{"subu_s.qb",		"d,s,t",	0x7c000150, 0xfc0007ff, WR_1|RD_2|RD_3,		0,		0,		D32,	0 },
{"wrdsp",		"s",		0x7c1ffcf8, 0xfc1fffff, RD_1|DSP_VOLA,		0,		0,		D32,	0 },
{"wrdsp",		"s,8",		0x7c0004f8, 0xfc1e07ff, RD_1|DSP_VOLA,		0,		0,		D32,	0 },
/* MIPS DSP ASE Rev2 */
{"absq_s.qb",		"d,t",		0x7c000052, 0xffe007ff, WR_1|RD_2,              0,              0,		D33,	0 },
{"addu.ph",		"d,s,t",	0x7c000210, 0xfc0007ff, WR_1|RD_2|RD_3,         0,              0,		D33,	0 },
{"addu_s.ph",		"d,s,t",	0x7c000310, 0xfc0007ff, WR_1|RD_2|RD_3,         0,              0,		D33,	0 },
{"adduh.qb",		"d,s,t",	0x7c000018, 0xfc0007ff, WR_1|RD_2|RD_3,         0,              0,		D33,	0 },
{"adduh_r.qb",		"d,s,t",	0x7c000098, 0xfc0007ff, WR_1|RD_2|RD_3,         0,              0,		D33,	0 },
{"append",		"t,s,h",	0x7c000031, 0xfc0007ff, MOD_1|RD_2,         0,              0,		D33,	0 },
{"balign",		"t,s,I",	0,    (int) M_BALIGN,	INSN_MACRO,             0,              0,		D33,	0 },
{"balign",		"t,s,2",	0x7c000431, 0xfc00e7ff, MOD_1|RD_2,         0,              0,		D33,	0 },
{"cmpgdu.eq.qb",	"d,s,t",	0x7c000611, 0xfc0007ff, WR_1|RD_2|RD_3,		0,              0,		D33,	0 },
{"cmpgdu.lt.qb",	"d,s,t",	0x7c000651, 0xfc0007ff, WR_1|RD_2|RD_3,		0,              0,		D33,	0 },
{"cmpgdu.le.qb",	"d,s,t",	0x7c000691, 0xfc0007ff, WR_1|RD_2|RD_3,		0,              0,		D33,	0 },
{"dpa.w.ph",		"7,s,t",	0x7c000030, 0xfc00e7ff, RD_2|RD_3|MOD_a,        0,              0,		D33,	0 },
{"dps.w.ph",		"7,s,t",	0x7c000070, 0xfc00e7ff, RD_2|RD_3|MOD_a,        0,              0,		D33,	0 },
{"mul.ph",		"d,s,t",	0x7c000318, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,              0,		D33,	0 },
{"mul_s.ph",		"d,s,t",	0x7c000398, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,              0,		D33,	0 },
{"mulq_rs.w",		"d,s,t",	0x7c0005d8, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,              0,		D33,	0 },
{"mulq_s.ph",		"d,s,t",	0x7c000790, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,              0,		D33,	0 },
{"mulq_s.w",		"d,s,t",	0x7c000598, 0xfc0007ff, WR_1|RD_2|RD_3|WR_HILO, 0,              0,		D33,	0 },
{"mulsa.w.ph",		"7,s,t",	0x7c0000b0, 0xfc00e7ff, RD_2|RD_3|MOD_a,        0,              0,		D33,	0 },
{"precr.qb.ph",		"d,s,t",	0x7c000351, 0xfc0007ff, WR_1|RD_2|RD_3,		0,              0,		D33,	0 },
{"precr_sra.ph.w",	"t,s,h",	0x7c000791, 0xfc0007ff, MOD_1|RD_2,		0,              0,		D33,	0 },
{"precr_sra_r.ph.w",	"t,s,h",	0x7c0007d1, 0xfc0007ff, MOD_1|RD_2,		0,              0,		D33,	0 },
{"prepend",		"t,s,h",	0x7c000071, 0xfc0007ff, MOD_1|RD_2,         0,              0,		D33,	0 },
{"shra.qb",		"d,t,3",	0x7c000113, 0xff0007ff, WR_1|RD_2,              0,              0,		D33,	0 },
{"shra_r.qb",		"d,t,3",	0x7c000153, 0xff0007ff, WR_1|RD_2,              0,              0,		D33,	0 },
{"shrav.qb",		"d,t,s",	0x7c000193, 0xfc0007ff, WR_1|RD_2|RD_3,         0,              0,		D33,	0 },
{"shrav_r.qb",		"d,t,s",	0x7c0001d3, 0xfc0007ff, WR_1|RD_2|RD_3,         0,              0,		D33,	0 },
{"shrl.ph",		"d,t,4",	0x7c000653, 0xfe0007ff, WR_1|RD_2,              0,              0,		D33,	0 },
{"shrlv.ph",		"d,t,s",	0x7c0006d3, 0xfc0007ff, WR_1|RD_2|RD_3,         0,              0,		D33,	0 },
{"subu.ph",		"d,s,t",	0x7c000250, 0xfc0007ff, WR_1|RD_2|RD_3,         0,              0,		D33,	0 },
{"subu_s.ph",		"d,s,t",	0x7c000350, 0xfc0007ff, WR_1|RD_2|RD_3,         0,              0,		D33,	0 },
{"subuh.qb",		"d,s,t",	0x7c000058, 0xfc0007ff, WR_1|RD_2|RD_3,         0,              0,		D33,	0 },
{"subuh_r.qb",		"d,s,t",	0x7c0000d8, 0xfc0007ff, WR_1|RD_2|RD_3,         0,              0,		D33,	0 },
{"addqh.ph",		"d,s,t",	0x7c000218, 0xfc0007ff, WR_1|RD_2|RD_3,		0,              0,		D33,	0 },
{"addqh_r.ph",		"d,s,t",	0x7c000298, 0xfc0007ff, WR_1|RD_2|RD_3,		0,              0,		D33,	0 },
{"addqh.w",		"d,s,t",	0x7c000418, 0xfc0007ff, WR_1|RD_2|RD_3,		0,              0,		D33,	0 },
{"addqh_r.w",		"d,s,t",	0x7c000498, 0xfc0007ff, WR_1|RD_2|RD_3,		0,              0,		D33,	0 },
{"subqh.ph",		"d,s,t",	0x7c000258, 0xfc0007ff, WR_1|RD_2|RD_3,		0,              0,		D33,	0 },
{"subqh_r.ph",		"d,s,t",	0x7c0002d8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,              0,		D33,	0 },
{"subqh.w",		"d,s,t",	0x7c000458, 0xfc0007ff, WR_1|RD_2|RD_3,		0,              0,		D33,	0 },
{"subqh_r.w",		"d,s,t",	0x7c0004d8, 0xfc0007ff, WR_1|RD_2|RD_3,		0,              0,		D33,	0 },
{"dpax.w.ph",		"7,s,t",	0x7c000230, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,              0,		D33,	0 },
{"dpsx.w.ph",		"7,s,t",	0x7c000270, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,              0,		D33,	0 },
{"dpaqx_s.w.ph",	"7,s,t",	0x7c000630, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,              0,		D33,	0 },
{"dpaqx_sa.w.ph",	"7,s,t",	0x7c0006b0, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,              0,		D33,	0 },
{"dpsqx_s.w.ph",	"7,s,t",	0x7c000670, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,              0,		D33,	0 },
{"dpsqx_sa.w.ph",	"7,s,t",	0x7c0006f0, 0xfc00e7ff, RD_2|RD_3|MOD_a,	0,              0,		D33,	0 },
/* Move bc0* after mftr and mttr to avoid opcode collision.  */
{"bc0f",		"p",		0x41000000, 0xffff0000,	RD_CC|CBD,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"bc0fl",		"p",		0x41020000, 0xffff0000,	RD_CC|CBL,		0,		I2|T3,		0,	IOCT|IOCTP|IOCT2 },
{"bc0t",		"p",		0x41010000, 0xffff0000,	RD_CC|CBD,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"bc0tl",		"p",		0x41030000, 0xffff0000,	RD_CC|CBL,		0,		I2|T3,		0,	IOCT|IOCTP|IOCT2 },
/* ST Microelectronics Loongson-2E and -2F.  */
{"mult.g",		"d,s,t",	0x7c000018, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2E,		0,	0 },
{"mult.g",		"d,s,t",	0x70000010, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2F,		0,	0 },
{"gsmult",		"d,s,t",	0x70000010, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"multu.g",		"d,s,t",	0x7c000019, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2E,		0,	0 },
{"multu.g",		"d,s,t",	0x70000012, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2F,		0,	0 },
{"gsmultu",		"d,s,t",	0x70000012, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"dmult.g",		"d,s,t",	0x7c00001c, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2E,		0,	0 },
{"dmult.g",		"d,s,t",	0x70000011, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2F,		0,	0 },
{"gsdmult",		"d,s,t",	0x70000011, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"dmultu.g",		"d,s,t",	0x7c00001d, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2E,		0,	0 },
{"dmultu.g",		"d,s,t",	0x70000013, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2F,		0,	0 },
{"gsdmultu",		"d,s,t",	0x70000013, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"div.g",		"d,s,t",	0x7c00001a, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2E,		0,	0 },
{"div.g",		"d,s,t",	0x70000014, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2F,		0,	0 },
{"gsdiv",		"d,s,t",	0x70000014, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"divu.g",		"d,s,t",	0x7c00001b, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2E,		0,	0 },
{"divu.g",		"d,s,t",	0x70000016, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2F,		0,	0 },
{"gsdivu",		"d,s,t",	0x70000016, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"ddiv.g",		"d,s,t",	0x7c00001e, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2E,		0,	0 },
{"ddiv.g",		"d,s,t",	0x70000015, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2F,		0,	0 },
{"gsddiv",		"d,s,t",	0x70000015, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"ddivu.g",		"d,s,t",	0x7c00001f, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2E,		0,	0 },
{"ddivu.g",		"d,s,t",	0x70000017, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2F,		0,	0 },
{"gsddivu",		"d,s,t",	0x70000017, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"mod.g",		"d,s,t",	0x7c000022, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2E,		0,	0 },
{"mod.g",		"d,s,t",	0x7000001c, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2F,		0,	0 },
{"gsmod",		"d,s,t",	0x7000001c, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"modu.g",		"d,s,t",	0x7c000023, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2E,		0,	0 },
{"modu.g",		"d,s,t",	0x7000001e, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2F,		0,	0 },
{"gsmodu",		"d,s,t",	0x7000001e, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"dmod.g",		"d,s,t",	0x7c000026, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2E,		0,	0 },
{"dmod.g",		"d,s,t",	0x7000001d, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2F,		0,	0 },
{"gsdmod",		"d,s,t",	0x7000001d, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"dmodu.g",		"d,s,t",	0x7c000027, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2E,		0,	0 },
{"dmodu.g",		"d,s,t",	0x7000001f, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL2F,		0,	0 },
{"gsdmodu",		"d,s,t",	0x7000001f, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		IL3A,		0,	0 },
{"packsshb",		"D,S,T",	0x47400002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"packsshb",		"D,S,T",	0x4b400002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"packsswh",		"D,S,T",	0x47200002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"packsswh",		"D,S,T",	0x4b200002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"packushb",		"D,S,T",	0x47600002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"packushb",		"D,S,T",	0x4b600002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"paddb",		"D,S,T",	0x47c00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"paddb",		"D,S,T",	0x4bc00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"paddb",		"d,s,t",	0x70000208, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"paddh",		"D,S,T",	0x47400000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"paddh",		"d,s,t",	0x70000108, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"paddh",		"D,S,T",	0x4b400000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"paddw",		"D,S,T",	0x47600000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"paddw",		"D,S,T",	0x4b600000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"paddw",		"d,s,t",	0x70000008, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"paddd",		"D,S,T",	0x47e00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"paddd",		"D,S,T",	0x4be00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"paddsb",		"D,S,T",	0x47800000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"paddsb",		"D,S,T",	0x4b800000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"paddsb",		"d,s,t",	0x70000608, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"paddsh",		"D,S,T",	0x47000000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"paddsh",		"D,S,T",	0x4b000000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"paddsh",		"d,s,t",	0x70000508, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"paddusb",		"D,S,T",	0x47a00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"paddusb",		"D,S,T",	0x4ba00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"paddush",		"D,S,T",	0x47200000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"paddush",		"D,S,T",	0x4b200000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pandn",		"D,S,T",	0x47e00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pandn",		"D,S,T",	0x4be00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pavgb",		"D,S,T",	0x46600000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pavgb",		"D,S,T",	0x4b200008, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pavgh",		"D,S,T",	0x46400000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pavgh",		"D,S,T",	0x4b000008, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pcmpeqb",		"D,S,T",	0x46c00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pcmpeqb",		"D,S,T",	0x4b800009, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pcmpeqh",		"D,S,T",	0x46800001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pcmpeqh",		"D,S,T",	0x4b400009, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pcmpeqw",		"D,S,T",	0x46400001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pcmpeqw",		"D,S,T",	0x4b000009, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pcmpgtb",		"D,S,T",	0x46e00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pcmpgtb",		"D,S,T",	0x4ba00009, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pcmpgth",		"D,S,T",	0x46a00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pcmpgth",		"D,S,T",	0x4b600009, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pcmpgtw",		"D,S,T",	0x46600001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pcmpgtw",		"D,S,T",	0x4b200009, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pextrh",		"D,S,T",	0x45c00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pextrh",		"D,S,T",	0x4b40000e, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pinsrh_0",		"D,S,T",	0x47800003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pinsrh_0",		"D,S,T",	0x4b800003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pinsrh_1",		"D,S,T",	0x47a00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pinsrh_1",		"D,S,T",	0x4ba00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pinsrh_2",		"D,S,T",	0x47c00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pinsrh_2",		"D,S,T",	0x4bc00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pinsrh_3",		"D,S,T",	0x47e00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pinsrh_3",		"D,S,T",	0x4be00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pmaddhw",		"D,S,T",	0x45e00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pmaddhw",		"D,S,T",	0x4b60000e, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pmaxsh",		"D,S,T",	0x46800000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pmaxsh",		"D,S,T",	0x4b400008, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pmaxub",		"D,S,T",	0x46c00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pmaxub",		"D,S,T",	0x4b800008, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pminsh",		"D,S,T",	0x46a00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pminsh",		"D,S,T",	0x4b600008, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pminub",		"D,S,T",	0x46e00000, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pminub",		"D,S,T",	0x4ba00008, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pmovmskb",		"D,S",		0x46a00005, 0xffff003f,	WR_1|RD_2|FP_D,		0,		IL2E,		0,	0 },
{"pmovmskb",		"D,S",		0x4ba0000f, 0xffff003f,	WR_1|RD_2|FP_D,		0,		IL2F|IL3A,	0,	0 },
{"pmulhuh",		"D,S,T",	0x46e00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pmulhuh",		"D,S,T",	0x4ba0000a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pmulhh",		"D,S,T",	0x46a00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pmulhh",		"D,S,T",	0x4b60000a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pmullh",		"D,S,T",	0x46800002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pmullh",		"D,S,T",	0x4b40000a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pmuluw",		"D,S,T",	0x46c00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pmuluw",		"D,S,T",	0x4b80000a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"pasubub",		"D,S,T",	0x45a00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pasubub",		"D,S,T",	0x4b20000d, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"biadd",		"D,S",		0x46800005, 0xffff003f,	WR_1|RD_2|FP_D,		0,		IL2E,		0,	0 },
{"biadd",		"D,S",		0x4b80000f, 0xffff003f,	WR_1|RD_2|FP_D,		0,		IL2F|IL3A,	0,	0 },
{"pshufh",		"D,S,T",	0x47000002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"pshufh",		"D,S,T",	0x4b000002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psllh",		"D,S,T",	0x46600002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psllh",		"D,S,T",	0x4b20000a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psllh",		"d,t,<",	0x70000034, 0xffe0003f,	WR_1|RD_2,		0,		MMI,		0,	0 },
{"psllw",		"D,S,T",	0x46400002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psllw",		"D,S,T",	0x4b00000a, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psllw",		"d,t,<",	0x7000003c, 0xffe0003f,	WR_1|RD_2,		0,		MMI,		0,	0 },
{"psrah",		"D,S,T",	0x46a00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psrah",		"D,S,T",	0x4b60000b, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psrah",		"d,t,<",	0x70000037, 0xffe0003f,	WR_1|RD_2,		0,		MMI,		0,	0 },
{"psraw",		"D,S,T",	0x46800003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psraw",		"D,S,T",	0x4b40000b, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psraw",		"d,t,<",	0x7000003f, 0xffe0003f,	WR_1|RD_2,		0,		MMI,		0,	0 },
{"psrlh",		"D,S,T",	0x46600003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psrlh",		"D,S,T",	0x4b20000b, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psrlh",		"d,t,<",	0x70000036, 0xffe0003f,	WR_1|RD_2,		0,		MMI,		0,	0 },
{"psrlw",		"D,S,T",	0x46400003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psrlw",		"D,S,T",	0x4b00000b, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psrlw",		"d,t,<",	0x7000003e, 0xffe0003f,	WR_1|RD_2,		0,		MMI,		0,	0 },
{"psubb",		"D,S,T",	0x47c00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psubb",		"D,S,T",	0x4bc00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psubb",		"d,s,t",	0x70000248, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"psubh",		"D,S,T",	0x47400001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psubh",		"D,S,T",	0x4b400001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psubh",		"d,s,t",	0x70000148, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"psubw",		"D,S,T",	0x47600001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psubw",		"D,S,T",	0x4b600001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psubw",		"d,s,t",	0x70000048, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"psubd",		"D,S,T",	0x47e00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psubd",		"D,S,T",	0x4be00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psubsb",		"D,S,T",	0x47800001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psubsb",		"D,S,T",	0x4b800001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psubsb",		"d,s,t",	0x70000648, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"psubsh",		"D,S,T",	0x47000001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psubsh",		"D,S,T",	0x4b000001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psubsh",		"d,s,t",	0x70000548, 0xfc0007ff,	WR_1|RD_2|RD_3,		0,		MMI,		0,	0 },
{"psubusb",		"D,S,T",	0x47a00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psubusb",		"D,S,T",	0x4ba00001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"psubush",		"D,S,T",	0x47200001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"psubush",		"D,S,T",	0x4b200001, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"punpckhbh",		"D,S,T",	0x47600003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"punpckhbh",		"D,S,T",	0x4b600003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"punpckhhw",		"D,S,T",	0x47200003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"punpckhhw",		"D,S,T",	0x4b200003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"punpckhwd",		"D,S,T",	0x46e00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"punpckhwd",		"D,S,T",	0x4ba0000b, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"punpcklbh",		"D,S,T",	0x47400003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"punpcklbh",		"D,S,T",	0x4b400003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"punpcklhw",		"D,S,T",	0x47000003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"punpcklhw",		"D,S,T",	0x4b000003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"punpcklwd",		"D,S,T",	0x46c00003, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2E,		0,	0 },
{"punpcklwd",		"D,S,T",	0x4b80000b, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	0,		IL2F|IL3A,	0,	0 },
{"sequ",		"S,T",		0x46800032, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2E,		0,	0 },
{"sequ",		"S,T",		0x4b80000c, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	0,		IL2F|IL3A,	0,	0 },

/* Alias of some loongson mmi insn that do integer operands in float regeiter.  */
{"andn",		"D,S,T",	0x4be00002, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* pandn */
{"saddw",		"D,S,T",	0x4b40000c, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* add */
{"saddd",		"D,S,T",	0x4b60000c, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* dadd */
{"sadduw",		"D,S,T",	0x4b00000c, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* addu */
{"ssubw",		"D,S,T",	0x4b40000d, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* sub */
{"ssubd",		"D,S,T",	0x4b60000d, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* dsub */
{"ssubuw",		"D,S,T",	0x4b00000d, 0xffe0003f,	WR_1|RD_2|RD_3|FP_S,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* subu */
{"sseqd",		"S,T",		0x4ba0000c, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* seq */
{"ssequd",		"S,T",		0x4b80000c, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* sequ */
{"ssltd",		"S,T",		0x4ba0000d, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* slt */
{"ssltud",		"S,T",		0x4b80000d, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* sltu */
{"ssled",		"S,T",		0x4ba0000e, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* sle */
{"ssleud",		"S,T",		0x4b80000e, 0xffe007ff,	RD_1|RD_2|WR_CC|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* sleu */
{"ssllw",		"D,S,T",	0x4b00000e, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* sll */
{"sslld",		"D,S,T",	0x4b20000e, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* dsll */
{"ssraw",		"D,S,T",	0x4b40000f, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* sra */
{"ssrad",		"D,S,T",	0x4b60000f, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* dsra */
{"ssrlw",		"D,S,T",	0x4b00000f, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* srl */
{"ssrld",		"D,S,T",	0x4b20000f, 0xffe0003f,	WR_1|RD_2|RD_3|FP_D,	INSN2_ALIAS,	IL2F|IL3A,	0,	0 },  /* dsrl */

/* MIPS Enhanced VA Scheme */
{"lbue",		"t,+j(b)",	0x7c000028, 0xfc00007f, WR_1|RD_3|LDD,		0,		0,		EVA,	0 },
{"lbue",		"t,A(b)",	0,    (int) M_LBUE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"lhue",		"t,+j(b)",	0x7c000029, 0xfc00007f, WR_1|RD_3|LDD,		0,		0,		EVA,	0 },
{"lhue",		"t,A(b)",	0,    (int) M_LHUE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"lbe",			"t,+j(b)",	0x7c00002c, 0xfc00007f, WR_1|RD_3|LDD,		0,		0,		EVA,	0 },
{"lbe",			"t,A(b)",	0,    (int) M_LBE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"lhe",			"t,+j(b)",	0x7c00002d, 0xfc00007f, WR_1|RD_3|LDD,		0,		0,		EVA,	0 },
{"lhe",			"t,A(b)",	0,    (int) M_LHE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"lle",			"t,+j(b)",	0x7c00002e, 0xfc00007f, WR_1|RD_3|LDD,		0,		0,		EVA,	0 },
{"lle",			"t,A(b)",	0,    (int) M_LLE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"lwe",			"t,+j(b)",	0x7c00002f, 0xfc00007f, WR_1|RD_3|LDD,		0,		0,		EVA,	0 },
{"lwe",			"t,A(b)",	0,    (int) M_LWE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"lwle",		"t,+j(b)",	0x7c000019, 0xfc00007f, WR_1|RD_3|LDD,		0,		0,		EVA,	0 },
{"lwle",		"t,A(b)",	0,    (int) M_LWLE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"lwre",		"t,+j(b)",	0x7c00001a, 0xfc00007f, WR_1|RD_3|LDD,		0,		0,		EVA,	0 },
{"lwre",		"t,A(b)",	0,    (int) M_LWRE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"sbe",			"t,+j(b)",	0x7c00001c, 0xfc00007f, RD_1|RD_3|SM,		0,		0,		EVA,	0 },
{"sbe",			"t,A(b)",	0,    (int) M_SBE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"sce",			"t,+j(b)",	0x7c00001e, 0xfc00007f, MOD_1|RD_3|SM,		0,		0,		EVA,	0 },
{"sce",			"t,A(b)",	0,    (int) M_SCE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"she",			"t,+j(b)",	0x7c00001d, 0xfc00007f, RD_1|RD_3|SM,		0,		0,		EVA,	0 },
{"she",			"t,A(b)",	0,    (int) M_SHE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"swe",			"t,+j(b)",	0x7c00001f, 0xfc00007f, RD_1|RD_3|SM,		0,		0,		EVA,	0 },
{"swe",			"t,A(b)",	0,    (int) M_SWE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"swle",		"t,+j(b)",	0x7c000021, 0xfc00007f, RD_1|RD_3|SM,		0,		0,		EVA,	0 },
{"swle",		"t,A(b)",	0,    (int) M_SWLE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"swre",		"t,+j(b)",	0x7c000022, 0xfc00007f, RD_1|RD_3|SM,		0,		0,		EVA,	0 },
{"swre",		"t,A(b)",	0,    (int) M_SWRE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
{"cachee",		"k,+j(b)",	0x7c00001b, 0xfc00007f, RD_3,			0,		0,		EVA,	0 },
{"cachee",		"k,A(b)",	0,    (int) M_CACHEE_AB,INSN_MACRO,		0,		0,		EVA,	0 },
{"prefe",		"k,+j(b)",	0x7c000023, 0xfc00007f, RD_3,			0,		0,		EVA,	0 },
{"prefe",		"k,A(b)",	0,    (int) M_PREFE_AB,	INSN_MACRO,		0,		0,		EVA,	0 },
/* No hazard protection on coprocessor instructions--they shouldn't
   change the state of the processor and if they do it's up to the
   user to put in nops as necessary.  These are at the end so that the
   disassembler recognizes more specific versions first.  */
{"c0",			"C",		0x42000000, 0xfe000000,	CP,			0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"c1",			"C",		0x46000000, 0xfe000000,	FP_S,			0,		I1,		0,	0 },
{"c2",			"C",		0x4a000000, 0xfe000000,	CP,			0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"c3",			"C",		0x4e000000, 0xfe000000,	CP,			0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"cop0",		"C",		0,    (int) M_COP0,	INSN_MACRO,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"cop1",		"C",		0,    (int) M_COP1,	INSN_MACRO,		INSN2_M_FP_S,	I1,		0,	0 },
{"cop2",		"C",		0,    (int) M_COP2,	INSN_MACRO,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
{"cop3",		"C",		0,    (int) M_COP3,	INSN_MACRO,		0,		I1,		0,	IOCT|IOCTP|IOCT2 },
/* RFE conflicts with the new Virt spec instruction tlbgp. */
{"rfe",			"",		0x42000010, 0xffffffff,	0,			0,		I1|T3,		0,	0 },
};

#define MIPS_NUM_OPCODES \
	((sizeof mips_builtin_opcodes) / (sizeof (mips_builtin_opcodes[0])))
const int bfd_mips_num_builtin_opcodes = MIPS_NUM_OPCODES;

/* const removed from the following to allow for dynamic extensions to the
 * built-in instruction set. */
struct mips_opcode *mips_opcodes =
  (struct mips_opcode *) mips_builtin_opcodes;
int bfd_mips_num_opcodes = MIPS_NUM_OPCODES;
#undef MIPS_NUM_OPCODES
