/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: fenv.h
: Note: ANSI C fenv.h header file wraper
************************************************************/
#ifndef _FENV_H_
#define	_FENV_H_

extern int fegetround(void);
extern int fesetround(int round);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChFenv_handle = dlopen("libfenv.dl", RTLD_LAZY);
if(_ChFenv_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChFenv_handle in fenv.h\n");
   exit(-1);
} 
void _dlclose_fenv(void) {
   dlclose(_ChFenv_handle);
}
atexit(_dlclose_fenv);
#endif

#endif /* _FENV_H_ */
