/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: mqueue.h
************************************************************/
#ifndef _MQUEUE_H_
#define _MQUEUE_H_

#include <sys/types.h>
#include <sys/fcntl.h>
#include <signal.h>
#include <sys/time.h>

typedef void	*mqd_t;		/* opaque message queue descriptor */

struct mq_attr {
	long	mq_flags;	/* message queue flags */
	long	mq_maxmsg;	/* maximum number of messages */
	long	mq_msgsize;	/* maximum message size */
	long	mq_curmsgs;	/* number of messages currently queued */
	int	mq_pad[12];
};

/*
 * function prototypes
 */
mqd_t	mq_open(const char *name, int oflag, ...);
int	mq_close(mqd_t mqdes);
int	mq_unlink(const char *name);
int	mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len,
		unsigned int msg_prio);
ssize_t	mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len,
		unsigned int *msg_prio);
int	mq_notify(mqd_t mqdes, const struct sigevent *notification);
int	mq_getattr(mqd_t mqdes, struct mq_attr *mqstat);
int	mq_setattr(mqd_t mqdes, const struct mq_attr *mqstat,
		struct mq_attr *omqstat);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChMqueue_handle = dlopen("libmqueue.dl", RTLD_LAZY);
if(_ChMqueue_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChMqueue_handle in mqueue.h\n");
   exit(-1);
} 
void _dlclose_mqueue(void) {
   dlclose(_ChMqueue_handle);
}
atexit(_dlclose_mqueue);
#endif

#endif /* _MQUEUE_H_ */
