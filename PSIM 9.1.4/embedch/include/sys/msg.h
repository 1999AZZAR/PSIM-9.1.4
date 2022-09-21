/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: msg.h
: Note: CH msg.h header file wraper
************************************************************/
#ifndef _SYS_MSG_H_
#define _SYS_MSG_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <ch/sys/msg.h>


/*int msgctl(int, int, ...);*/
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
int msgget(key_t, int);
int msgrcv(int, void *, size_t, long, int);
 int msgsnd(int, const void *, size_t, int);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChSysMsg_handle = dlopen("libmsg.dl", RTLD_LAZY);
if(_ChSysMsg_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysMsg_handle in sys/msg.h\n");
   exit(-1);
}
void _dlclose_sysmsg(void) {
   dlclose(_ChSysMsg_handle);
}
atexit(_dlclose_sysmsg);
#endif

#endif /* _SYS_MSG_H_ */
