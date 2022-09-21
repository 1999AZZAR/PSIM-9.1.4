/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: termios.h
: Note: CH termios.h header file wraper
************************************************************/
#ifndef _TERMIOS_H_
#define	_TERMIOS_H_

#include <sys/types.h>

typedef unsigned long tcflag_t;
typedef unsigned char cc_t;
typedef unsigned long speed_t;

#include <ch/termios.h>

extern speed_t cfgetospeed (const struct termios *);
extern int cfsetospeed (struct termios *, speed_t);
extern speed_t cfgetispeed (const struct termios *);
extern int cfsetispeed (struct termios *, speed_t);
extern int tcgetattr (int, struct termios *);
extern int tcsetattr (int, int, const struct termios *);
extern int tcsendbreak (int, int);
extern int tcdrain (int);
extern int tcflush (int, int);
extern int tcflow (int, int);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChTermios_handle = dlopen("libtermios.dl", RTLD_LAZY);
if(_ChTermios_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChTermios_handle in termios.h\n");
   exit(-1);
}
void _dlclose_termios(void) {
   dlclose(_ChTermios_handle);
}
atexit(_dlclose_termios);
#endif
 
#endif /* _TERMIOS_H_ */
