/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: netdir.h
************************************************************/
#ifndef _NETDIR_H_
#define _NETDIR_H_

#include <netconfig.h>
#include <tiuser.h>
struct nd_addrlist {
	int 		n_cnt;		/* number of netbufs */
	struct netbuf 	*n_addrs;	/* the netbufs */
};

struct nd_hostservlist {
	int			h_cnt;		/* number of nd_hostservs */
	struct nd_hostserv	*h_hostservs;	/* the entries */
};

struct nd_hostserv {
	char		*h_host;	/* the host name */
	char		*h_serv;	/* the service name */
};

struct nd_mergearg {
	char		*s_uaddr;	/* servers universal address */
	char		*c_uaddr;	/* clients universal address */
	char		*m_uaddr;	/* merged universal address */
};

/*
 * These are all objects that can be freed by netdir_free
 */
#define	ND_HOSTSERV	0
#define	ND_HOSTSERVLIST	1
#define	ND_ADDR		2
#define	ND_ADDRLIST	3

/*
 * These are the various errors that can be encountered while attempting
 * to translate names to addresses. Note that none of them (except maybe
 * no memory) are truely fatal unless the ntoa deamon is on its last attempt
 * to translate the name. First four errors are to failitate return values
 * from DNS, that are used by mail and others.
 *
 * Negative errors terminate the search resolution process, positive errors
 * are treated as warnings.
 */

#define	ND_TRY_AGAIN	-5	/* Non-Authoritive Host not found, or */
				/* SERVERFAIL */
#define	ND_NO_RECOVERY	-4	/* Non recoverable errors, FORMERR, REFUSED, */
				/* NOTIMP */
#define	ND_NO_DATA	-3	/* Valid name, no data record of requested */
				/* type */
#define	ND_NO_ADDRESS ND_NO_DATA /* no address, look for MX record */
#define	ND_BADARG	-2	/* Bad arguments passed 	*/
#define	ND_NOMEM 	-1	/* No virtual memory left	*/
#define	ND_OK		0	/* Translation successful	*/
#define	ND_NOHOST	1	/* Hostname was not resolvable	*/
#define	ND_NOSERV	2	/* Service was unknown		*/
#define	ND_NOSYM	3	/* Couldn't resolve symbol	*/
#define	ND_OPEN		4	/* File couldn't be opened	*/
#define	ND_ACCESS	5	/* File is not accessable	*/
#define	ND_UKNWN	6	/* Unknown object to be freed	*/
#define	ND_NOCTRL	7	/* Unknown option passed to netdir_options */
#define	ND_FAILCTRL	8	/* Option failed in netdir_options */
#define	ND_SYSTEM	9	/* Other System error		*/

/*
 * The following netdir_options commands can be given to the fd. These is
 * a way of providing for any transport specific action which the caller
 * may want to initiate on his transport. It is up to the trasport provider
 * to support the netdir_options he wants to support.
 */

#define	ND_SET_BROADCAST	1	/* Do t_optmgmt to support broadcast */
#define	ND_SET_RESERVEDPORT	2	/* bind it to reserve address */
#define	ND_CHECK_RESERVEDPORT	3	/* check if address is reserved */
#define	ND_MERGEADDR		4	/* Merge universal address */

/*
 *	The following special case host names are used to give the underlying
 *	transport provides a clue as to the intent of the request.
 */

#define	HOST_SELF	"\\1"
#define	HOST_ANY	"\\2"
#define	HOST_BROADCAST	"\\3"
#define	HOST_SELF_BIND	HOST_SELF
#define	HOST_SELF_CONNECT	"\\4"


int netdir_options(struct netconfig *, int option, int fd, char *par);
int netdir_getbyname(struct netconfig *, struct nd_hostserv *,
    struct nd_addrlist **);
int netdir_getbyaddr(struct netconfig *, struct nd_hostservlist **,
    struct netbuf *);
int netdir_mergeaddr(struct netconfig *, char **muaddr, char *uaddr,
    char *ruaddr);
void netdir_free(void *, int);
struct netbuf *uaddr2taddr(struct netconfig *, char *);
char *taddr2uaddr(struct netconfig *, struct netbuf *);
void netdir_perror(char *);
char *netdir_sperror();

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChNetdir_handle = dlopen("libnetdir.dl", RTLD_LAZY);
if(_ChNetdir_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChNetdir_handle in netdir.h\n");
   exit(-1);
}
void _dlclose_netdir(void) {
   dlclose(_ChNetdir_handle);
}
atexit(_dlclose_netdir);
#endif

#endif /* _NETDIR_H_ */
