/* Copyright 2003 Marcin Siennicki <m.siennicki@cloos.pl>
 * see COPYING file for details */

#ifndef __CSSL_H__
#define __CSSL_H__

#include <stdint.h>
#include <signal.h>
#include <termios.h>

#include "csslType.h"


/* get the error message */
const char *cssl_geterrormsg();

/* get the error code */
int cssl_geterror();

/* start the cssl */
void cssl_start();

/* finish all jobs, clear memory, etc. */
void cssl_stop();

/* alloc new cssl_t struct and open the port */
cssl_t *cssl_openSock(const char* address, int portno,
		  cssl_callback_t callback,
		  int id,
		  int baud,
		  int bits,
		  int parity,
		  int stop);
cssl_t *cssl_open(const char *fname, /* pathname of port file,
				      * for example "/dev/ttyS0" */
		  cssl_callback_t callback, /* callback function
					     * If you dont want
					     * event driven reading - set
					     * it to NULL */
		  int id,     /* your own id for the port, it can help
			       * to identify the port in callback f.*/
		  int baud,   /* baudrate, integer, for example 19200 */
		  int bits,   /* data bits: 7 or 8 */
		  int parity, /* parity: 0 - none, 1-odd, 2-even */
		  int stop);  /* stop bits: 1 or 2 */

/* closes the port, and frees its cssl_t struct */
void cssl_close(cssl_t *serial);

/* setups the port, look at cssl_open */
void cssl_setup(cssl_t *serial,
		   int baud,
		   int bits,
		   int parity,
		   int stop);

void cssl_setflowcontrol(cssl_t *serial,
			 int rtscts,   /* Boolean: 
					* 0 - no rts/cts control,
					* 1 - rts/cts control 
					*/
			 int xonxoff); /* Boolean: 
					* 0 - no xon/xoff, 
					* 1 - xon/xoff 
					*/

/* sends a char via serial port */
void cssl_putchar(cssl_t *serial,
		     char c);

/* sends a null terminated string */
void cssl_putstring(cssl_t *serial,
		       char *str);

/* sends a data of known size */
void cssl_putdata(cssl_t *serial,
		  uint8_t *data, /* data */
		  int datalen);  /* length of data */

/* waits until all data has been transmited */

void cssl_drain(cssl_t *serial);

/*====================================== 
 * Blocking mode 
 */

/* Sets port timeout (deciseconds) in blocking mode */
void cssl_settimeout(cssl_t *serial, int timeout);

/* reads a char in blocking mode */
int cssl_getchar(cssl_t *serial);

/* reads a data to a buffer in blocking mode*/
int cssl_getdata(cssl_t *serial,
		 uint8_t *buffer,  /* buffer for data */
		 int size);        /* buffer size */


#endif /* __CSSL_H__ */
