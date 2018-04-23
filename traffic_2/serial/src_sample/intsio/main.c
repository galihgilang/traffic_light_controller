/*------------------------------------------------------------------------------
MAIN.C:  Interrupt Driver SIO Using printf.

Copyright 1995-2002 KEIL Software, Inc.
------------------------------------------------------------------------------*/

#include <stdio.h>
#include "sio.h"

/*------------------------------------------------------------------------------
_getkey waits until a character is received from the serial port.  This may not
be the exact desired operation (for example if the buffer is empty, this
function hangs waiting for a character to be received).
------------------------------------------------------------------------------*/
char _getkey (void)
{
int k;

do
  {
  k = com_getchar ();
  }
while (k == -1);

return ((unsigned char) k);
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
char putchar (char c)
{
volatile unsigned int i;

while (com_putchar (c) != 0)
  {
  for (i=0; i<1000; i++)
    {
    /*** DO NOTHING ***/
    }
  }

return (c);
}

/*------------------------------------------------------------------------------
Note that the two function above, _getkey and putchar, replace the library
functions of the same name.  These functions use the interrupt-driven serial
I/O routines in SIO.C.
------------------------------------------------------------------------------*/
code char message [] =
  "This is a test to see if the interrupt driven serial I/O routines really work.";

void main (void)
{
com_initialize ();              /* initialize interrupt driven serial I/O */
com_baudrate (38400);           /* setup for 38400 baud */

printf ("Interrupt-driver Serial I/O Example\r\n\r\n");

while (1)
  {
  unsigned char c;

  printf ("Press a key.\r\n");
  c = getchar ();
  printf ("\r\n");
  printf ("You pressed '%c'.\r\n\r\n", c);
  }
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

