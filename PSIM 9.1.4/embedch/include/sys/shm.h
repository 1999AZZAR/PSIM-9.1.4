/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: shm.h
: Note: CH shm.h header file wraper
************************************************************/
#ifndef _SYS_SHM_H_
#define _SYS_SHM_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <ch/sys/shm.h>

/* int shmctl(int, int, ...); */
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
int shmget(key_t, int, int);
void *shmat(int, void *, int);
int shmdt(void *);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysShm_handle = dlopen("libshm.dl", RTLD_LAZY);
if(_ChSysShm_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysShm_handle in sys/shm.h\n");
   exit(-1);
}
void _dlclose_sysshm(void) {
   dlclose(_ChSysShm_handle);
}
atexit(_dlclose_sysshm);
#endif

#endif /* _SYS_SHM_H_ */
