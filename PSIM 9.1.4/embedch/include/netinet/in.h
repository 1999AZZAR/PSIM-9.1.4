/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: in.h
************************************************************/
#ifndef _NETINET_IN_H_
#define _NETINET_IN_H_

#include<sys/types.h> 

#include <ch/netinet/in.h>

/* Functions to convert between host and network byte order. */
extern  u_long htonl(u_long);
extern  u_short htons(u_short);
extern  u_long ntohl(u_long);
extern  u_short ntohs(u_short);

#if defined(_CHDLL_) && !defined(_WINSOCK2API_) && !defined(_WINSOCK_H) && !defined(_WINSOCK2_H) /* _ChNetinetIn_handle is handled in winsock.h */
#include <dlfcn.h>
void *_ChNetinetIn_handle = dlopen("libin.dl", RTLD_LAZY);
if(_ChNetinetIn_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChNetinetIn_handle in netinet/in.h\n");
   exit(-1);
} 
void _dlclose_netinetin(void) {
   dlclose(_ChNetinetIn_handle);
}
atexit(_dlclose_netinetin);
#endif

#endif	/* _NETINET_IN_H_ */
