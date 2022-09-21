/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: netdb.h
* Note: netdb.h header file wraper
************************************************************/
#ifndef _NETDB_H_
#define	_NETDB_H_

#include <arpa/inet.h>
#include <ch/netdb.h>

#if defined(_LINUX_) || defined(_LINUXPPC_) || defined(_FREEBSD_) || defined(_QNX_)  
/* Reentrant versions of the functions above.  The additional
   arguments specify a buffer of BUFLEN starting at BUF.  The last
   argument is a pointer to a variable which gets the value which
   would be stored in the global variable `herrno' by the
   non-reentrant functions.  */
extern int gethostent_r (struct hostent * resultbuf,
			 char * buf, size_t buflen,
			 struct hostent ** result,
			 int * h_errnop);

extern int gethostbyaddr_r (void * addr, socklen_t len,
			    int type,
			    struct hostent * resultbuf,
			    char * buf, size_t buflen,
			    struct hostent ** result,
			    int * h_errnop);

extern int gethostbyname_r (char * name,
			    struct hostent * resultbuf,
			    char * buf, size_t buflen,
			    struct hostent ** result,
			    int * h_errnop);

extern int gethostbyname2_r (char * name, int af,
			     struct hostent * resultbuf,
			     char * buf, size_t buflen,
			     struct hostent ** result,
			     int * h_errnop);


extern int getnetent_r (struct netent * resultbuf,
			char * buf, size_t buflen,
			struct netent ** result,
			int * h_errnop);

extern int getnetbyaddr_r (uint32_t net, int type,
			   struct netent * resultbuf,
			   char * buf, size_t buflen,
			   struct netent ** result,
			   int * h_errnop);

extern int getnetbyname_r (char * name,
			   struct netent * resultbuf,
			   char * buf, size_t buflen,
			   struct netent ** result,
			   int * h_errnop);

extern int getservent_r (struct servent * resultbuf,
			 char * buf, size_t buflen,
			 struct servent ** result);

extern int getservbyname_r (char * name,
			    char * proto,
			    struct servent * resultbuf,
			    char * buf, size_t buflen,
			    struct servent ** result);

extern int getservbyport_r (int port, char * proto,
			    struct servent * resultbuf,
			    char * buf, size_t buflen,
			    struct servent ** result);

extern int getprotoent_r (struct protoent * resultbuf,
			  char * buf, size_t buflen,
			  struct protoent ** result);

extern int getprotobyname_r (char * name,
			     struct protoent * resultbuf,
			     char * buf, size_t buflen,
			     struct protoent ** result);

extern int getprotobynumber_r (int proto,
			       struct protoent * resultbuf,
			       char * buf, size_t buflen,
			       struct protoent ** result);

extern int getnetgrent_r (char ** hostp,
			  char ** userp,
			  char ** domainp,
			  char * buffer, size_t buflen);

#else
extern restrict struct hostent	*gethostbyname_r(const char *,		 struct hostent *, char *, int, int *h_errnop);
extern restrict  struct hostent	*gethostbyaddr_r(const char *, int, int, struct hostent *, char *, int, int *h_errnop);
extern struct hostent	*gethostent_r(struct hostent *, char *, int, int *h_errnop);
extern struct servent	*getservbyname_r(const char *name, const char *, struct servent *, char *, int);
extern struct servent	*getservbyport_r(int port,	   const char *, struct servent *, char *, int);
extern struct servent	*getservent_r(struct	servent *, char *, int);
extern struct netent	*getnetbyname_r(const char *, struct netent *, char *, int);
extern struct netent	*getnetbyaddr_r(long, int, struct netent *, char *, int);
extern struct netent	*getnetent_r(struct netent *, char *, int);
extern struct protoent	*getprotobyname_r(const char *, struct protoent *, char *, int);
extern struct protoent	*getprotobynumber_r(int, struct protoent *, char *, int);
extern struct protoent	*getprotoent_r(struct protoent *, char *, int);
#endif

/* Old interfaces that return a pointer to a static area;  MT-unsafe */
extern restrict struct hostent *gethostbyname(const char *name);
extern restrict struct hostent	*gethostbyaddr(const char *, int, int);
extern struct hostent	*gethostent(void);
extern struct netent	*getnetbyname(const char *);
extern struct netent	*getnetbyaddr(long, int);
extern struct netent	*getnetent(void);
extern struct servent	*getservbyname(const char *, const char *);
extern struct servent	*getservbyport(int, const char *);
extern struct servent	*getservent(void);
extern struct protoent	*getprotobyname(const char *);
extern struct protoent	*getprotobynumber(int);
extern struct protoent	*getprotoent(void);

extern int sethostent(int);
extern int endhostent(void);
extern int setnetent(int);
extern int endnetent(void);
extern int setservent(int);
extern int endservent(void);
extern int setprotoent(int);
extern int endprotoent(void);
extern int rcmd(char **, unsigned short, char *, char *, char *, int *);
extern int rexec(char **, unsigned short, char *, char *, char *, int *);
extern int rresvport(int *);
extern int ruserok(char *, int, char *, char *);

/*
  handle extern variables
*/
#if defined(_CHDLL_) && !defined(_WINSOCK2API_) && !defined(_WINSOCK_H) && !defined(_WINSOCK2_H) /* _ChNetdb_handle is handled in winsock.h */
#include <dlfcn.h>
int *_h_errno_ptr;
#define h_errno *_h_errno_ptr
void *_ChNetdb_handle = dlopen("libnetdb.dl", RTLD_LAZY);
if(_ChNetdb_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChNetdb_handle in netdb.h\n");
   exit(-1);
} 
else {
    void *fptr, ChNetdb_hInitialize(int **h_errno_ptr);

    fptr = dlsym(_ChNetdb_handle , "ChNetdb_hInitialize");
    if(fptr == NULL) { 
       fprintf(_stderr, "Error: dlsym(): %s\n", dlerror());
       exit(1);
    }
    dlrunfun(fptr, NULL, ChNetdb_hInitialize, &_h_errno_ptr);
/* 
    _h_errno_ptr = *(int**)dlsym(_ChNetdb_handle, "h_errno_Ch");
    if(_h_errno_ptr == NULL) {
        fprintf(_stderr, "Error: dlsym(): h_errno %s\n", dlerror());
        exit(1);
    }
*/
}
void _dlclose_netdb(void) {
   dlclose(_ChNetdb_handle);
}
atexit(_dlclose_netdb);
#endif /* _CHDLL_ */

#endif /* _NETDB_H_ */
