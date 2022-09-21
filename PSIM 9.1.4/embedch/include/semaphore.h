/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: semaphore.h
************************************************************/
#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <sys/types.h>
#include <sys/fcntl.h>

#if defined(_LINUX_) || defined(_LINUXPPC_)
typedef struct {
  long int sem_status;
  int sem_spinlock;
} sem_t;
#elif defined(_SUN_) || defined(_SOLARIS_)
typedef struct {
	/* this structure must be the same as sema_t in <synch.h> */
	uint32_t	sem_count;	/* semaphore count */
	uint32_t	sem_type;
	uint64_t	sem_pad1[3];	/* reserved for a mutex_t */
	uint64_t 	sem_pad2[2];	/* reserved for a cond_t */
}	sem_t;
#elif defined(_HPUX_)
typedef unsigned long sem_t;
#elif defined(_DARWIN_)
typedef int sem_t;
#elif defined(_FREEBSD_) || defined(_QNX_)
struct sem;
typedef struct sem * sem_t;
#else
#error header file <semaphore.h> has not been tested for this platform
#endif

/*
 * function prototypes
 */
int	sem_init(sem_t *sem, int pshared, unsigned int value);
int	sem_destroy(sem_t *sem);
sem_t	*sem_open(const char *name, int oflag, ...); 
int	sem_close(sem_t *sem);
int	sem_unlink(const char *name);
int	sem_wait(sem_t *sem);
int	sem_trywait(sem_t *sem);
int	sem_post(sem_t *sem);
int	sem_getvalue(sem_t *sem, int *sval);
/* available in Linux only 
int sem_timedwait(sem_t *sem, timespec *abs_timeout);
*/



#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSemaphore_handle = dlopen("libsemaphore.dl", RTLD_LAZY);
if(_ChSemaphore_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSemaphore_handle in semaphore.h\n");
   exit(-1);
}
void _dlclose_semaphore(void) {
   dlclose(_ChSemaphore_handle);
}
atexit(_dlclose_semaphore);
#endif

#endif /* _SEMAPHORE_H_ */
