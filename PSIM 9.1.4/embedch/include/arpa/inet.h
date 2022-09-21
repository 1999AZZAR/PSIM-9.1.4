/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: inet.h
************************************************************/
#ifndef _ARPA_INET_H_
#define _ARPA_INET_H_

#include <ch/netinet/in.h>

extern unsigned long inet_addr(const char *);
extern char *inet_ntoa(struct in_addr);
extern struct in_addr inet_makeaddr(int, int);
extern unsigned long inet_network(const char *);
extern unsigned long inet_lnaof(struct in_addr);
extern unsigned long inet_netof(struct in_addr);

extern  int     inet_aton(const char *, struct in_addr *);
extern  int     inet_net_pton(int, const char *, void *, size_t);
extern  int     inet_pton(int, const char *, void *);
extern  const   char *inet_ntop(int, const void *, char *, size_t);

#if defined(_CHDLL_) && !defined(_WINSOCK2API_) && !defined(_WINSOCK_H) && !defined(_WINSOCK2_H) /* _ChArpaInet_handle is handled in winsock.h */
#include <dlfcn.h>
void *_ChArpaInet_handle = dlopen("libinet.dl", RTLD_LAZY);
if(_ChArpaInet_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChArpaInet_handle in sys/inet.h\n");
   exit(-1);
} 
void _dlclose_arpainet(void) {
   dlclose(_ChArpaInet_handle);
}
atexit(_dlclose_arpainet);

#endif

#endif /* _ARPA_INET_H_ */
