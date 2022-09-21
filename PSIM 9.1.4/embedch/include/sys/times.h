/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: times.h
************************************************************/
#ifndef _SYS_TIMES_H_
#define _SYS_TIMES_H_

#include <sys/types.h>

/*
 * Structure returned by times()
 */
struct tms {
	clock_t	tms_utime;		/* user time */
	clock_t	tms_stime;		/* system time */
	clock_t	tms_cutime;		/* user time, children */
	clock_t	tms_cstime;		/* system time, children */
};

extern clock_t times(struct tms *);


#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysTimes_handle = dlopen("libtimes.dl", RTLD_LAZY);
if(_ChSysTimes_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysTimes_handle in sys/times.h\n");
   exit(-1);
}
void _dlclose_systimes(void) {
   dlclose(_ChSysTimes_handle);
}
atexit(_dlclose_systimes);
#endif

#endif /* _SYS_TIMES_H_ */
