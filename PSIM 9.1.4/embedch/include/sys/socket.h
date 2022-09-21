/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: socket.h
: Note: CH socket.h header file wraper
************************************************************/
#ifndef _SYS_SOCKET_H_
#define _SYS_SOCKET_H_

#include <sys/types.h>
#include <sys/uio.h>

#ifndef _WIN32_
typedef int SOCKET;
#endif
     
#include <ch/sys/socket.h>

extern restrict SOCKET accept(SOCKET, struct sockaddr *, int *);
extern int bind(SOCKET, struct sockaddr *, int);
extern int connect(SOCKET, struct sockaddr *, int);
extern int getpeername(SOCKET, struct sockaddr *, int *);
extern int getsockname(SOCKET, struct sockaddr *, int *);
extern int getsockopt(SOCKET, int, int, char *, int *);
extern int listen(SOCKET, int);
extern int recvfrom(SOCKET, char *, int, int, struct sockaddr *, int *);
extern int send(SOCKET, const char *, int, int);
extern int sendto(SOCKET, const char *, int, int, struct sockaddr *, int);
extern int setsockopt(SOCKET, int, int, const char *, int);
extern restrict SOCKET socket(int, int, int);
extern int recvmsg(SOCKET, struct msghdr *, int);
extern int sendmsg(SOCKET, struct msghdr *, int);
extern int shutdown(SOCKET, int);
extern restrict int socketpair(SOCKET, int, int, int *);

extern restrict ssize_t recv(int s, void *buf, size_t len, int flags);


#if defined(_CHDLL_) && !defined(_WINSOCK2API_) && !defined(_WINSOCK_H) && !defined(_WINSOCK2_H) /* _ChSysSocket_handle is handled in winsock.h */

#include <dlfcn.h>
void *_ChSysSocket_handle = dlopen("libsocket.dl", RTLD_LAZY);
if(_ChSysSocket_handle == NULL) { 
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysSocket_handle in sys/socket.h\n");
   exit(-1);
}
void _dlclose_syssocket(void) {
   dlclose(_ChSysSocket_handle);
}
atexit(_dlclose_syssocket);
#endif 

#endif /* _SYS_SOCKET_H_ */
