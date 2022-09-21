/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: aio.h
: Note: CH aio.h header file wraper
************************************************************/
#ifndef _AIO_H_
#define	_AIO_H_

#include <sys/types.h>
#include <sys/fcntl.h>
#include <time.h>
#include <signal.h>

#include <ch/aio.h>

extern int aio_read(struct aiocb *aiocbp);
extern int aio_write(struct aiocb *aiocbp);
extern int lio_listio(int mode, struct aiocb* list[], int nent,
                      struct sigevent *sig);
extern int aio_error(const struct aiocb *aiocbp);
extern int aio_return(struct aiocb *aiocbp);
extern int aio_cancel(int fildes, struct aiocb *aiocbp);
extern int aio_suspend(const struct aiocb *aiocbp[], int nent,
                       const struct timespec *timeout);
extern int aio_fsync(int op, struct aiocb *aiocbp);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChAio_handle = dlopen("libaio.dl", RTLD_LAZY);
if(_ChAio_handle == NULL) { 
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChAio_handle in aio.h\n");
   exit(-1);
} 
void _dlclose_aio(void) {
   dlclose(_ChAio_handle);
}
atexit(_dlclose_aio);
#endif  
 
#endif /* _AIO_H_ */
