/*
 * csslType.h
 *
 *  Created on: 13 janv. 2012
 *      Author: bplanche
 */

#ifndef CSSLTYPE_H_
#define CSSLTYPE_H_

typedef void (*cssl_callback_t)(int id,  /* id passed to callback */
				uint8_t *buffer, /* data received */
				int len); /* length of data in bytes */

typedef struct __cssl_t {

    uint8_t buffer[255];      /* input buffer */

    int fd;                   /* tty file descriptor */

    struct termios tio;       /* termios structure for the port */
    struct termios oldtio;    /* old termios structure */

    cssl_callback_t callback; /* callback function */

    int id;                   /* id which would be passed to callback */

    struct __cssl_t *next;

} cssl_t;

typedef enum {
    CSSL_OK,                 /* everything is all right */
    CSSL_ERROR_NOSIGNAL,     /* there's no free signal */
    CSSL_ERROR_NOTSTARTED,   /* you should first start cssl */
    CSSL_ERROR_NULLPOINTER,  /* you gave a null pointer to the function */
    CSSL_ERROR_OOPS,         /* internal error, something's erong */
    CSSL_ERROR_MEMORY,       /* there's no memory for cssl_t structure */
    CSSL_ERROR_OPEN          /* file doesnt exist or you aren't good user */
} cssl_error_t;

#endif /* CSSLTYPE_H_ */
