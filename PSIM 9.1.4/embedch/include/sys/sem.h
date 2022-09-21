/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: sem.h
: Note: CH sem.h header file wraper
************************************************************/
#ifndef _SYS_SEM_H_
#define _SYS_SEM_H_

#include <sys/ipc.h>
#include <ch/sys/sem.h>

extern int semctl(int semid, int semnum, int cmd, ... /*union semun arg*/);
extern int semget(key_t, int, int);
extern int semop(int, struct sembuf *, unsigned);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysSem_handle = dlopen("libsem.dl", RTLD_LAZY);
if(_ChSysSem_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysSem_handle in sys/sem.h\n");
   exit(-1);
} 
void _dlclose_syssem(void) {
   dlclose(_ChSysSem_handle);
}
atexit(_dlclose_syssem);
#endif

#endif /* _SYS_SEM_H_ */

