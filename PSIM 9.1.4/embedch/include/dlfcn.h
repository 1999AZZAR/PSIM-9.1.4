/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: dlfcn.h
************************************************************/
#ifndef _DLFCN_H_
#define	_DLFCN_H_

/* Valid values for mode argument to dlopen. */
#if defined(_HPUX_)
#define	RTLD_LAZY	0x1        /* same as BIND_DEFERRED  in <dl.h> */
#define	RTLD_NOW        0x0        /* same as BIND_IMMEDIATE in <dl.h> */
#elif defined(_AIX_)
#define RTLD_NOW                0x00000002 /* Load object and dependents now. */
#define RTLD_LAZY               0x00000004 /* Load object and dependents when
                                              symbol is referenced (not
                                              implemented) */
#define RTLD_GLOBAL             0x00010000 /* Make symbols in this module
                                              visible to other dlopens. */
#define RTLD_LOCAL              0x00080000 /* Make symbols in this module
                                              private. */
#else
#define	RTLD_LAZY	1	   /* lazy function call binding */
#if defined(_SUN_)
#define	RTLD_NOW	1	   /* immediate function call binding */
#else
#define	RTLD_NOW	2	   /* immediate function call binding */
#endif
#define	RTLD_GLOBAL	0x100	   /* allow symbols to be global */
/* Valid values for handle argument to dlsym(3x). */
#define	RTLD_NEXT	(void *)-1 /* look in `next' shared object */
#endif

extern void * dlopen(const char *, int);
extern void * dlsym(void *, const char *);
extern int    dlclose(void *);
extern char * dlerror(void);
/* generic function
extern int     dlrunfun(void *, void *, type (*)(), ...);
*/

#endif	/* _DLFCN_H_ */
