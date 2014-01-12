
/*---------------------------------------------------------------*/
/*--- begin                              libvex_guest_arm64.h ---*/
/*---------------------------------------------------------------*/

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2013-2013 OpenWorks
      info@open-works.net

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.

   The GNU General Public License is contained in the file COPYING.
*/

#ifndef __LIBVEX_PUB_GUEST_ARM64_H
#define __LIBVEX_PUB_GUEST_ARM64_H

#include "libvex_basictypes.h"


/*---------------------------------------------------------------*/
/*--- Vex's representation of the ARM64 CPU state.            ---*/
/*---------------------------------------------------------------*/

typedef
   struct {
      /* Event check fail addr and counter. */
      /* 0 */  ULong host_EvC_FAILADDR;
      /* 8 */  UInt  host_EvC_COUNTER;
      /* 12 */ UInt  pad0;
      /* 16 */
      ULong guest_X0;
      ULong guest_X1;
      ULong guest_X2;
      ULong guest_X3;
      ULong guest_X4;
      ULong guest_X5;
      ULong guest_X6;
      ULong guest_X7;
      ULong guest_X8;
      ULong guest_X9;
      ULong guest_X10;
      ULong guest_X11;
      ULong guest_X12;
      ULong guest_X13;
      ULong guest_X14;
      ULong guest_X15;
      ULong guest_X16;
      ULong guest_X17;
      ULong guest_X18;
      ULong guest_X19;
      ULong guest_X20;
      ULong guest_X21;
      ULong guest_X22;
      ULong guest_X23;
      ULong guest_X24;
      ULong guest_X25;
      ULong guest_X26;
      ULong guest_X27;
      ULong guest_X28;
      ULong guest_X29;
      ULong guest_X30;     /* link register */
      ULong guest_SP;
      ULong guest_PC;

      /* 4-word thunk used to calculate N(sign) Z(zero) C(carry,
         unsigned overflow) and V(signed overflow) flags. */
      ULong guest_CC_OP;
      ULong guest_CC_DEP1;
      ULong guest_CC_DEP2;
      ULong guest_CC_NDEP;

      /* User-space thread register? */
      ULong guest_TPIDR_EL0;

      /* FP/SIMD state */
      U128 guest_Q0;
      U128 guest_Q1;
      U128 guest_Q2;
      U128 guest_Q3;
      U128 guest_Q4;
      U128 guest_Q5;
      U128 guest_Q6;
      U128 guest_Q7;
      U128 guest_Q8;
      U128 guest_Q9;
      U128 guest_Q10;
      U128 guest_Q11;
      U128 guest_Q12;
      U128 guest_Q13;
      U128 guest_Q14;
      U128 guest_Q15;
      U128 guest_Q16;
      U128 guest_Q17;
      U128 guest_Q18;
      U128 guest_Q19;
      U128 guest_Q20;
      U128 guest_Q21;
      U128 guest_Q22;
      U128 guest_Q23;
      U128 guest_Q24;
      U128 guest_Q25;
      U128 guest_Q26;
      U128 guest_Q27;
      U128 guest_Q28;
      U128 guest_Q29;
      U128 guest_Q30;
      U128 guest_Q31;

      /* Various pseudo-regs mandated by Vex or Valgrind. */
      /* Emulation notes */
      UInt guest_EMNOTE;

      /* For clflush: record start and length of area to invalidate */
      ULong guest_TISTART;
      ULong guest_TILEN;

      /* Used to record the unredirected guest address at the start of
         a translation whose start has been redirected.  By reading
         this pseudo-register shortly afterwards, the translation can
         find out what the corresponding no-redirection address was.
         Note, this is only set for wrap-style redirects, not for
         replace-style ones. */
      ULong guest_NRADDR;

      /* Needed for Darwin (but mandated for all guest architectures):
         program counter at the last syscall insn (int 0x80/81/82,
         sysenter, syscall, svc).  Used when backing up to restart a
         syscall that has been interrupted by a signal. */
      ULong guest_IP_AT_SYSCALL;

      /* The complete FPCR.  Default value seems to be zero.  We
         ignore all bits except 23 and 22, which are the rounding
         mode.  The guest is unconstrained in what values it can write
         to and read from this register, but the emulation only takes
         note of bits 23 and 22. */
      UInt  guest_FPCR;

      /* The complete FPSR.  As with FPCR, the guest may write and
         read any values here, and the emulation ignores it, with the
         exception of bit 27 (QC, the sticky saturation bit) which
         does get set when required. */
      UInt  guest_FPSR;

      /* Padding to make it have an 32-aligned size */
      UInt  pad_end_0;
      ULong pad_end_1;
   }
   VexGuestARM64State;


/*---------------------------------------------------------------*/
/*--- Utility functions for ARM64 guest stuff.                ---*/
/*---------------------------------------------------------------*/

/* ALL THE FOLLOWING ARE VISIBLE TO LIBRARY CLIENT */

/* Initialise all guest ARM64 state. */

extern
void LibVEX_GuestARM64_initialise ( /*OUT*/VexGuestARM64State* vex_state );

/* Calculate the ARM64 flag state from the saved data, in the format
   32x0:n:z:c:v:28x0. */
extern
ULong LibVEX_GuestARM64_get_nzcv ( /*IN*/
                                   const VexGuestARM64State* vex_state );

#endif /* ndef __LIBVEX_PUB_GUEST_ARM64_H */


/*---------------------------------------------------------------*/
/*---                                    libvex_guest_arm64.h ---*/
/*---------------------------------------------------------------*/
