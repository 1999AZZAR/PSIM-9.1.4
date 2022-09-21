/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: procset.h
: Note: CH procset.h header file wraper
************************************************************/
#ifndef _SYS_PROCSET_H_
#define _SYS_PROCSET_H_

#include <sys/types.h>

#include <ch/sys/procset.h>

extern int sigsend(idtype_t, id_t, int);
extern int sigsendset(procset_t *, int);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysProcset_handle = dlopen("libprocset.dl", RTLD_LAZY);
if(_ChSysProcset_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysProcset_handle in sys/procset.h\n");
   exit(-1);
} 
void _dlclose_sysprocset(void) {
   dlclose(_ChSysProcset_handle);
}
atexit(_dlclose_sysproceset);
#endif

#endif /* _SYS_PROCSET_H_ */
