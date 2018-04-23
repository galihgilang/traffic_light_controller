#include <reg52.h>
#include <stdio.h>

/*------------------------------------------------
Timer 0 Interrupt Service Routine.

Set a breakpoint on 'overflow_count++' and run the
program in the debugger.  You will see this line
executes every 65536 clock cycles.
------------------------------------------------*/
static unsigned long overflow_count = 0;

void timer0_ISR (void) interrupt 1
{
overflow_count++;   /* Increment the overflow count */
}

/*------------------------------------------------
MAIN C function
------------------------------------------------*/
void main (void)
{
/*--------------------------------------
Set Timer0 for 16-bit timer mode.  The
timer counts to 65535, overflows, and
generates an interrupt.

Set the Timer0 Run control bit.
--------------------------------------*/
TMOD = (TMOD & 0xF0) | 0x01;  /* Set T/C0 Mode */
ET0 = 1;                      /* Enable Timer 0 Interrupts */
TR0 = 1;                      /* Start Timer 0 Running */
EA = 1;                       /* Global Interrupt Enable */

/*--------------------------------------
Do Nothing.  Actually, the timer 0
interrupt will occur every 65536 clocks.
--------------------------------------*/
while (1)
  {
  }
}

