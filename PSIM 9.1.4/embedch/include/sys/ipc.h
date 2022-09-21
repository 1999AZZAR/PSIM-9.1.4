/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: ipc.h
************************************************************/
#ifndef _SYS_IPC_H_
#define _SYS_IPC_H_

#include<sys/types.h>
#include <ch/sys/ipc.h>

key_t ftok(const char *, int);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysIpc_handle = dlopen("libipc.dl", RTLD_LAZY);
if(_ChSysIpc_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysIpc_handle in sys/ipc.h\n");
   exit(-1);
} 
void _dlclose_sysipc(void) {
   dlclose(_ChSysIpc_handle);
}
atexit(_dlclose_sysipc);
#endif



#endif /* _SYS_IPC_H_ */
