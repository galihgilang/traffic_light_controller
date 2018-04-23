#include <reg52.h>
#include <stdio.h>

/*------------------------------------------------
MAIN C function
------------------------------------------------*/
void main (void)
{
/*--------------------------------------
Set serial port for 9600 baud at
11.0592 MHz.  Note that we use Timer 1
for the baud rate generator.
--------------------------------------*/
SCON  = 0x50;
TMOD |= 0x20;
TH1   = 0xFA;
TR1   = 1;
TI    = 1;
PCON |= 0x80;

printf ("\r\nCounter 0 Example Program\r\n");
printf ("\r\nStart toggling P3.4 (T0 input)\r\n\r\n");

/*--------------------------------------
Set Timer0 for 16-bit counter mode.
Set the Timer0 Run control bit.
--------------------------------------*/
TMOD = (TMOD & 0xF0) | 0x05;
TR0 = 1;

/*--------------------------------------
Output the value of the counter.  As you
toggle P3.4, the timer/counter 0 value
will increase.
--------------------------------------*/
while (1)
  {
  printf ("\rCounter 0 = %2.2bX%2.2bXh", TH0, TL0);
  }
}

