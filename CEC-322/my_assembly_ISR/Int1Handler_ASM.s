#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"

  name isr_asm
  section .text:CODE
  extern srv
  public isr_asm_start
 
 isr_asm_start:
  ;TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT); C Instruction
  MOVS      R1, #1
  MOV32     R0, #0x40031000        ; [0x804] 0x40031000
  STR       R1, [R0, #0x24]
  ;srv++; C Instruction
  MOV32     R0, srv       ; [0x800] showADC
  LDR       R1, [R0]
  ADDS      R1, R1, #1
  STR       R1, [R0]

  BX LR
  end
  