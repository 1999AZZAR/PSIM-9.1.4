/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: glob.h
: Note: glob.h header file wraper
************************************************************/
#ifndef _GLOB_H_
#define	_GLOB_H_

#include <sys/types.h>
#include <ch/glob.h>

extern int glob(const char *pattern, int flags, int errfunc(const char * epath, int eerrno), glob_t *pglob);
extern void globfree(glob_t *pglob);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChGlob_handle = dlopen("libglob.dl", RTLD_LAZY);
if(_ChGlob_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChGlob_handle in glob.h\n");
   exit(-1);
} 
void _dlclose_glob(void) {
   dlclose(_ChGlob_handle);
}
atexit(_dlclose_glob);
#endif

#endif /* _GLOB_H_ */


