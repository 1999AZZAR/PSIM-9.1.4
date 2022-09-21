/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: utime.h
************************************************************/
#ifndef _UTIME_H_
#define	_UTIME_H_

#include <sys/types.h>

/* utimbuf is used by utime(2) */
struct utimbuf {
        time_t actime;          /* access time */
        time_t modtime;         /* modification time */
};

extern int utime(const char *, const struct utimbuf *);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChUtime_handle = dlopen("libutime.dl", RTLD_LAZY);
if(_ChUtime_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChUtime_handle in utime.h\n");
   exit(-1);
}
void _dlclose_utime(void) {
   dlclose(_ChUtime_handle);
}
atexit(_dlclose_utime);
#endif

#endif	/* _UTIME_H_ */

