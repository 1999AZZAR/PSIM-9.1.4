/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: stropts.h
: Note: CH stropts.h header file wraper
************************************************************/
#ifndef _STROPTS_H_
#define	_STROPTS_H_

#include <sys/types.h>

#include <ch/stropts.h>

extern int isastream(int);
extern int getmsg(int, struct strbuf *, struct strbuf *, int *);
extern int putmsg(int, const struct strbuf *, const struct strbuf *, int);
extern int getpmsg(int, struct strbuf *, struct strbuf *, int *, int *);
extern int putpmsg(int, const struct strbuf *, const struct strbuf *, int, int);
/*
 * These three routines are not duplicated in unistd.h; duplication necessitated
 * by XPG4.2 compliance/namespace issues.
 */
/* extern int ioctl(int, int, ...); built in*/
extern int fattach(int, const char *);
extern int fdetach(const char *);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChStropts_handle = dlopen("libstropts.dl", RTLD_LAZY);
if(_ChStropts_handle == NULL) { 
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChStropts_handle in stropts.h\n");
   exit(-1);
} 
void _dlclose_stropts(void) {
   dlclose(_ChStropts_handle);
}
atexit(_dlclose_stropts);
#endif  
 
#endif /* _STROPTS_H_ */
