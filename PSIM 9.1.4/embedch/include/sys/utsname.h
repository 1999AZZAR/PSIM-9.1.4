/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: utsname.h
************************************************************/
#ifndef _SYS_UTSNAME_H_
#define _SYS_UTSNAME_H_

#include <ch/sys/utsname.h>

int uname(struct utsname *);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysUtsname_handle = dlopen("libutsname.dl", RTLD_LAZY);
if(_ChSysUtsname_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysUtsname_handle in sys/utsname.h\n");
   exit(-1);
} 
void _dlclose_sysutsname(void) {
   dlclose(_ChSysUtsname_handle);
}
atexit(_dlclose_sysutsname);
#endif

#endif /* _SYS_UTSNAME_H_ */
