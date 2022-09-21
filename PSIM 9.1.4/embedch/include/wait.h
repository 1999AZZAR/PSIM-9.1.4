/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: wait.h
: Note: CH wait.h header file wraper
************************************************************/
#ifndef _SYS_WAIT_H_
#define _SYS_WAIT_H_

#include <sys/types.h>
#include <ch/sys/wait.h>

extern pid_t wait(int *);
extern pid_t waitpid(pid_t, int *, int);
#if _isvar("idtype_t") && _isvar("siginfo_t")
extern int waitid(idtype_t, id_t, siginfo_t *, int);
#endif

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysWait_handle = dlopen("libwait.dl", RTLD_LAZY);
if(_ChSysWait_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysWait_handle in wait.h\n");
   exit(-1);
}
void _dlclose_syswait(void) {
   dlclose(_ChSysWait_handle);
}
atexit(_dlclose_syswait);
#endif

#endif /* _SYS_WAIT_H_ */
