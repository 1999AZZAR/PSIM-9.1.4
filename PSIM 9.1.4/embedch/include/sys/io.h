/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: io.h
* Note: Ch io.h header file wraper
*       sys/io.h has only been tested in Linux
************************************************************/
#ifndef	_SYS_IO_H_
#define	_SYS_IO_H_


/* If TURN_ON is TRUE, request for permission to do direct i/o on the
   port numbers in the range [FROM,FROM+NUM-1].  Otherwise, turn I/O
   permission off for that range.  This call requires root privileges.

   Portability note: not all Linux platforms support this call.  Most
   platforms based on the PC I/O architecture probably will, however.
   E.g., Linux/Alpha for Alpha PCs supports this.  */
extern int ioperm (unsigned long int from, unsigned long int num,
                   int turn_on);

/* Set the I/O privilege level to LEVEL.  If LEVEL>3, permission to
   access any I/O port is granted.  This call requires root
   privileges. */
extern int iopl (int level);

/* static inline functions in C are implemented as external functions in Ch below */
extern unsigned char inb (unsigned short int port);
extern unsigned char inb_p (unsigned short int port);
extern unsigned short int inw (unsigned short int port);
extern unsigned short int inw_p (unsigned short int port);
extern unsigned int inl (unsigned short int port);
extern unsigned int inl_p (unsigned short int port);
extern void outb (unsigned char value, unsigned short int port);
extern void outb_p (unsigned char value, unsigned short int port);
extern void outw (unsigned short int value, unsigned short int port);
extern void outw_p (unsigned short int value, unsigned short int port);
extern void outl (unsigned int value, unsigned short int port);
extern void outl_p (unsigned int value, unsigned short int port);
extern void insb (unsigned short int port, void *addr, unsigned long int count);
extern void insw (unsigned short int port, void *addr, unsigned long int count);
extern void insl (unsigned short int port, void *addr, unsigned long int count);
extern void outsb (unsigned short int port, const void *addr, unsigned long int count);
extern void outsw (unsigned short int port, const void *addr, unsigned long int count);
extern void outsl (unsigned short int port, const void *addr, unsigned long int count);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysIo_handle = dlopen("libio.dl", RTLD_LAZY);
if(_ChSysIo_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysIo_handle in sys/io.h\n");
   exit(-1);
}
void _dlclose_sysio(void) {
   dlclose(_ChSysIo_handle);
}
atexit(_dlclose_sysio);
#endif

#endif /* _SYS_IO_H_ */
