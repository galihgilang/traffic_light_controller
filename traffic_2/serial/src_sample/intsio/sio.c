/*------------------------------------------------------------------------------
SIO.C:  Serial Communication Routines.

Copyright 1995-2002 KEIL Software, Inc.
------------------------------------------------------------------------------*/

#include <reg51.h>
#include <string.h>
#include "sio.h"

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
#define TBUF_SIZE	256		/* DO NOT CHANGE */
#define RBUF_SIZE	256		/* DO NOT CHANGE */

static xdata unsigned char tbuf [TBUF_SIZE];
static xdata unsigned char rbuf [RBUF_SIZE];

static xdata unsigned char t_in = 0;
static xdata unsigned char t_out = 0;
static xdata unsigned char t_disabled = 0;

static xdata unsigned char r_in = 0;
static xdata unsigned char r_out = 0;

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
static void com_isr (void) interrupt 4 using 2
{
/*------------------------------------------------
Received data interrupt.
------------------------------------------------*/
if (RI != 0)
  {
  RI = 0;

  if ((r_in + 1) != r_out)
    rbuf [r_in++] = SBUF;
  }

/*------------------------------------------------
Transmitted data interrupt.
------------------------------------------------*/
if (TI != 0)
  {
  TI = 0;

  if (t_in != t_out)
    SBUF = tbuf [t_out++];
  else
    t_disabled = 1;
  }

}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
void com_initialize (void)
{
/*------------------------------------------------
Setup TIMER1 to generate the proper baud rate.
------------------------------------------------*/
com_baudrate (1200);

/*------------------------------------------------
Clear com buffer indexes.
------------------------------------------------*/
EA = 0;                         /* Disable Interrupts */

t_in = 0;
t_out = 0;
t_disabled = 1;

r_in = 0;
r_out = 0;

/*------------------------------------------------
Setup serial port registers.
------------------------------------------------*/
SM0 = 0; SM1 = 1;		/* serial port MODE 1 */
SM2 = 0;
REN = 1;			/* enable serial receiver */

TI = 0;				/* clear transmit interrupt */
RI = 0;				/* clear receiver interrupt */

ES = 1;				/* enable serial interrupts */
PS = 0;				/* set serial interrupts to low priority */

EA = 1;                         /* Enable Interrupts */
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
void com_baudrate (
  unsigned baudrate)
{
EA = 0;                             /* Disable Interrupts */

/*------------------------------------------------
Clear transmit interrupt and buffer.
------------------------------------------------*/
TI = 0;				    /* clear transmit interrupt */
t_in = 0;			    /* empty transmit buffer */
t_out = 0;
t_disabled = 1;			    /* disable transmitter */

/*------------------------------------------------
Set timer 1 up as a baud rate generator.
------------------------------------------------*/
TR1 = 0;			    /* stop timer 1 */
ET1 = 0;			    /* disable timer 1 interrupt */

PCON |= 0x80;			    /* 0x80=SMOD: set serial baudrate doubler */

TMOD &= ~0xF0;			    /* clear timer 1 mode bits */
TMOD |= 0x20;			    /* put timer 1 into MODE 2 */

TH1 = (unsigned char) (256 - (XTAL / (16L * 12L * baudrate)));

TR1 = 1;			    /* start timer 1 */

EA = 1;                             /* Enable Interrupts */
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
char com_putchar (
  unsigned char c)
{
/*------------------------------------------------
If the buffer is full, return an error value.
------------------------------------------------*/
if ((TBUF_SIZE - com_tbuflen ()) <= 2)
  return (-1);

/*------------------------------------------------
Add the data to the transmit buffer.  If the
transmit interrupt is disabled, then enable it.
------------------------------------------------*/
EA = 0;                         /* Disable Interrupts */

tbuf [t_in++] = c;

if (t_disabled)			/* if transmitter is disabled */
  {
  t_disabled = 0;
  TI = 1;			/* enable it */
  }

EA = 1;                         /* Enable Interrupts */

return (0);
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
int com_getchar (void)
{
int c;

if (com_rbuflen () == 0)
  return (-1);

EA = 0;                         /* Disable Interrupts */
c = rbuf [r_out++];
EA = 1;                         /* Enable Interrupts */

return (c);
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
unsigned char com_rbuflen (void)
{
return (r_in - r_out);
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
unsigned char com_tbuflen (void)
{
return (t_in - t_out);
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

