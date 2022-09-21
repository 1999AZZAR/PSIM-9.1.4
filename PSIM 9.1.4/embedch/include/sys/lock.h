/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: lock.h
************************************************************/
#ifndef _SYS_LOCK_H_
#define _SYS_LOCK_H_

/*
 * flags for locking procs and texts
 */
#define	UNLOCK	 0
#define	PROCLOCK 1
#define	TXTLOCK	 2
#define	DATLOCK	 4

int plock(int);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysLock_handle = dlopen("liblock.dl", RTLD_LAZY);
if(_ChSysLock_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysLock_handle in sys/lock.h\n");
   exit(-1);
}
void _dlclose_syslock(void) {
   dlclose(_ChSysLock_handle);
}
atexit(_dlclose_syslock);
#endif

#endif /* _SYS_LOCK_H_ */
