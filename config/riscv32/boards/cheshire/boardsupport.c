/* Copyright (C) 2017 Embecosm Limited and University of Bristol

   Contributor Graham Markall <graham.markall@embecosm.com>

   This file is part of Embench and was formerly part of the Bristol/Embecosm
   Embedded Benchmark Suite.

   SPDX-License-Identifier: GPL-3.0-or-later */

   //#include <stdint.h>
   #include <support.h>
   //#include "regs/cheshire.h"
   //#include "dif/clint.h"
   //#include "dif/uart.h"
   //#include "params.h"
   //#include "util.h"
   //#include "printf.h"

   //int cycle_bmark, instr_bmark, Bmiss_bmark, ICmiss_bmark, DCmiss_bmark, IFempty_bmark, PipBub_bmark, cycle_count, instr_count, Bmiss_count, ICmiss_count, DCmiss_count, IFempty_count, PipBub_count;

   void
   initialise_board ()
   {
    //uint32_t rtc_freq = *reg32(&__base_regs, CHESHIRE_RTC_FREQ_REG_OFFSET);
    //uint64_t reset_freq = clint_get_core_freq(rtc_freq, 2500);
    //uart_init(&__base_uart, reset_freq, __BOOT_BAUDRATE);
    
    //__asm__ volatile("csrc mcountinhibit, %0" :: "r"(1 << 4));
    
   }

   void __attribute__ ((noinline)) __attribute__ ((externally_visible))
   start_trigger ()
   { 
    
    __asm__ volatile("csrw mhpmevent3, %0" :: "r"(0b00001)); //L1 I-Cache misses
    __asm__ volatile("csrw mhpmevent4, %0" :: "r"(0b00010)); //L1 D-Cache misses
    __asm__ volatile("csrw mhpmevent5, %0" :: "r"(0b01010)); //Branch mispredicts 
    __asm__ volatile("csrw mhpmevent6, %0" :: "r"(0b11001)); //no issue
    __asm__ volatile("csrw mhpmevent7, %0" :: "r"(0b10111)); //Dual issue 
    __asm__ volatile("csrw mhpmevent8, %0" :: "r"(0b11000)); //Single issue
    register unsigned int val __asm__("a0");
    __asm__ volatile("csrw mhpmevent9, %0" :: "r"(val)); 
    /*
     __asm__ volatile("csrr %0, mcycle" : "=r"(cycle_count));
     __asm__ volatile("csrr %0, minstret" : "=r"(instr_count));
     __asm__ volatile("csrr %0, mhpmcounter3" : "=r"(ICmiss_count));
     __asm__ volatile("csrr %0, mhpmcounter4" : "=r"(DCmiss_count));
     __asm__ volatile("csrr %0, mhpmcounter5" : "=r"(Bmiss_count));
     __asm__ volatile("csrr %0, mhpmcounter6" : "=r"(IFempty_count));
     __asm__ volatile("csrr %0, mhpmcounter7" : "=r"(PipBub_count));
     cycle_bmark = -cycle_count;
     instr_bmark = -instr_count;
     ICmiss_bmark = -ICmiss_count;
     DCmiss_bmark = -DCmiss_count;
     Bmiss_bmark = -Bmiss_count;
     IFempty_bmark = -IFempty_count;
     PipBub_bmark = -PipBub_count;
     //printf("ICmiss = %d  DCmiss = %d  Bmiss = %d  IFempty = %d  PipBub = %d\n\r", ICmiss_count, DCmiss_count, Bmiss_count, IFempty_count, PipBub_count);
     */
   }

   void __attribute__ ((noinline)) __attribute__ ((externally_visible))
   stop_trigger ()
   {
    register unsigned int val __asm__("a0");
    __asm__ volatile("csrw mhpmevent9, %0" :: "r"(val)); 
    __asm__ volatile("csrw mhpmevent3, %0" :: "r"(0b00000)); //L1 I-Cache misses
    __asm__ volatile("csrw mhpmevent4, %0" :: "r"(0b00000)); //L1 D-Cache misses
    __asm__ volatile("csrw mhpmevent5, %0" :: "r"(0b00000)); //Branch mispredicts 
    __asm__ volatile("csrw mhpmevent6, %0" :: "r"(0b00000)); //Instruction fetch Empty
    __asm__ volatile("csrw mhpmevent7, %0" :: "r"(0b00000)); //Pipeline bubbles 01001
    __asm__ volatile("csrw mhpmevent8, %0" :: "r"(0b00000)); //Branch instructions

    /*
     __asm__ volatile("csrr %0, mcycle" : "=r"(cycle_count));
     __asm__ volatile("csrr %0, minstret" : "=r"(instr_count));
     __asm__ volatile("csrr %0, mhpmcounter3" : "=r"(ICmiss_count));
     __asm__ volatile("csrr %0, mhpmcounter4" : "=r"(DCmiss_count));
     __asm__ volatile("csrr %0, mhpmcounter5" : "=r"(Bmiss_count));
     __asm__ volatile("csrr %0, mhpmcounter6" : "=r"(IFempty_count));
     __asm__ volatile("csrr %0, mhpmcounter7" : "=r"(PipBub_count));
     cycle_bmark += cycle_count;
     instr_bmark += instr_count;
     ICmiss_bmark += ICmiss_count;
     DCmiss_bmark += DCmiss_count;
     Bmiss_bmark += Bmiss_count;
     IFempty_bmark += IFempty_count;
     PipBub_bmark += PipBub_count;
     printf("cyc_b = %d  ins_b = %d\n\r", cycle_bmark, instr_bmark);
     printf("ICmiss = %d  DCmiss = %d  Bmiss = %d  IFempty = %d  PipBub = %d\n\r", ICmiss_bmark, DCmiss_bmark, Bmiss_bmark, IFempty_bmark, PipBub_bmark);
     */
   }
