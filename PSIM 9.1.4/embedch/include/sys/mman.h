/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: mman.h
************************************************************/
#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#include <sys/types.h>
#include <ch/sys/mman.h>

extern void *mmap(void *, size_t, int, int, int, off_t);
extern int munmap(void *, size_t);
extern int mprotect(void *, size_t, int);
extern int msync(void *, size_t, int);
extern int mlock(void *, size_t);
extern int munlock(void *, size_t);
extern int shm_open(const char *, int, mode_t);
extern int shm_unlink(const char *);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysMman_handle = dlopen("libmman.dl", RTLD_LAZY);
if(_ChSysMman_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysMman_handle in sys/mman.h\n");
   exit(-1);
} 
void _dlclose_sysmman(void) {
   dlclose(_ChSysMman_handle);
}
atexit(_dlclose_sysmman);
#endif

#endif /* _SYS_MMAN_H_ */
