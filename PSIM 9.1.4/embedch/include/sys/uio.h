/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: uio.h
************************************************************/
#ifndef _SYS_UIO_H_
#define _SYS_UIO_H_

#include<sys/types.h>

typedef struct iovec {
        caddr_t iov_base;
        int     iov_len;
} iovec_t;

enum uio_rw{ UIO_READ, UIO_WRITE};

extern int readv(int, struct iovec *, int);
extern int writev(int, const struct iovec *, int);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysUio_handle = dlopen("libuio.dl", RTLD_LAZY);
if(_ChSysUio_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysUio_handle in sys/uio.h\n");
   exit(-1);
}
void _dlclose_sysuio(void) {
   dlclose(_ChSysUio_handle);
}
atexit(_dlclose_sysuio);
#endif

#endif /* _SYS_UIO_H_ */
