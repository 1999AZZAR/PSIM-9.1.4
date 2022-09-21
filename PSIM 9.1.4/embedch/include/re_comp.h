/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: re_comp.h
: Note: re_comp.h header file wraper
************************************************************/
#ifndef _RE_COMP_H_
#define _RE_COMP_H_

extern char *re_comp(const char *string);
extern int re_exec(const char *string);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChRe_comp_handle = dlopen("libre_comp.dl", RTLD_LAZY);
if(_ChRe_comp_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChRe_comp_handle in re_comp.h\n");
   exit(-1);
} 
void _dlclose_re_comp(void) {
   dlclose(_ChRe_comp_handle);
}
atexit(_dlclose_re_comp);
#endif

#endif  /* _RE_COMP_H_ */
