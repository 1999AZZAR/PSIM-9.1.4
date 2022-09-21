/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: poll.h
************************************************************/
#ifndef _POLL_H_
#define _POLL_H_
/*
 * Structure of file descriptor/event pairs supplied in
 * the poll arrays.
 */
typedef struct pollfd {
        int fd;                         /* file desc to poll */
        short events;                   /* events of interest on fd */
        short revents;                  /* events that occurred on fd */
} pollfd_t;

/*
 * Testable select events
 */
#define POLLIN          0x0001          /* fd is readable */
#define POLLPRI         0x0002          /* high priority info at fd */
#define POLLOUT         0x0004          /* fd is writeable (won't block) */
#define POLLRDNORM      0x0040          /* normal data is readable */
#define POLLWRNORM      POLLOUT
#define POLLRDBAND      0x0080          /* out-of-band data is readable */
#define POLLWRBAND      0x0100          /* out-of-band data is writeable */

#define POLLNORM        POLLRDNORM

/*
 * Non-testable poll events (may not be specified in events field,
 * but may be returned in revents field).
 */
#define POLLERR         0x0008          /* fd has error condition */
#define POLLHUP         0x0010          /* fd has been hung up on */
#define POLLNVAL        0x0020          /* invalid pollfd entry */

int poll(struct pollfd *fds, unsigned int nfds, int timeout);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChPoll_handle = dlopen("libpoll.dl", RTLD_LAZY);
if(_ChPoll_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChPoll_handle in poll.h\n");
   exit(-1);
}
void _dlclose_poll(void) {
   dlclose(_ChPoll_handle);
}
atexit(_dlclose_poll);
#endif
 
#endif /* _POLL_H_ */
