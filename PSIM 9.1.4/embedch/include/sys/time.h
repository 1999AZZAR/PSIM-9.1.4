/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: time.h
************************************************************/
#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_


struct timeval {
	long	tv_sec;		/* seconds */
	long	tv_usec;	/* and microseconds */
};

struct timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};

#include <sys/types.h>

#define DST_NONE        0       /* not on dst */
#define DST_USA         1       /* USA style dst */
#define DST_AUST        2       /* Australian style dst */
#define DST_WET         3       /* Western European dst */
#define DST_MET         4       /* Middle European dst */
#define DST_EET         5       /* Eastern European dst */
#define DST_CAN         6       /* Canada */
#define DST_GB          7       /* Great Britain and Eire */
#define DST_RUM         8       /* Rumania */
#define DST_TUR         9       /* Turkey */
#define DST_AUSTALT     10      /* Australian style with shift in 1986 */

 
/*
 * Operations on timevals.
 *
 * NB: timercmp does not work for >= or <=.
 */
#define timerisset(tvp)         ((tvp)->tv_sec || (tvp)->tv_usec)
#define timercmp(tvp, uvp, cmp) \
        ((tvp)->tv_sec cmp (uvp)->tv_sec || \
            (tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec)
#define timerclear(tvp)         (tvp)->tv_sec = (tvp)->tv_usec = 0
 
/*
 * Names of the interval timers, and structure
 * defining a timer setting.
 */
#define ITIMER_REAL     0
#define ITIMER_VIRTUAL  1
#define ITIMER_PROF     2
#define ITIMER_REALPROF 3
 
 
struct  itimerval {
        struct  timeval it_interval;    /* timer interval */
        struct  timeval it_value;       /* current value */
};
 
/*
 *      Definitions for commonly used resolutions.
 */
 
#define SEC             1
#define MILLISEC        1000
#define MICROSEC        1000000
#define NANOSEC         1000000000
 

 
#define TIMER_RELTIME   0x0             /* set timer relative */
#define TIMER_ABSTIME   0x1             /* set timer absolute */


/*
 * Time expressed in seconds and nanoseconds
 */
typedef struct  timespec {              /* definition per POSIX.4 */
        time_t          tv_sec;         /* seconds */
        long            tv_nsec;        /* and nanoseconds */
} timespec_t;

typedef struct timespec timestruc_t;    /* definition per SVr4 */

/*
 * Timer specification
 */
typedef struct itimerspec {             /* definition per POSIX.4 */
        struct timespec it_interval;    /* timer period */
        struct timespec it_value;       /* timer expiration */
} itimerspec_t;



/*
 * Select uses bit masks of file descriptors in longs.
 * These macros manipulate such bit fields.
 * FD_SETSIZE may be defined by the user, but the default here
 * should be >= NOFILE (param.h).
 */
#ifndef	FD_SETSIZE
#define	FD_SETSIZE	1024
#endif

#ifndef NBBY		/* number of bits per byte */
#define	NBBY 8
#endif

typedef	long	fd_mask;
#define	NFDBITS	(sizeof (fd_mask) * NBBY)	/* bits per mask */
#ifndef	howmany
#define	howmany(x, y)	(((x)+((y)-1))/(y))
#endif

typedef	struct fd_set {
	fd_mask	fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} fd_set;

#define	FD_SET(n, p)	((p)->fds_bits[(n)/NFDBITS] |= \
			    ((unsigned)1 << ((n) % NFDBITS)))

#define	FD_CLR(n, p)	((p)->fds_bits[(n)/NFDBITS] &= \
			    ~((unsigned)1 << ((n) % NFDBITS)))

#define	FD_ISSET(n, p)	((p)->fds_bits[(n)/NFDBITS] & \
			    ((unsigned)1 << ((n) % NFDBITS)))

#define	FD_ZERO(p)	memset((char *)(p), 0, sizeof (*(p)))

extern int select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
extern int gettimeofday(struct timeval *tv, struct timezone *tz);
extern int settimeofday(const struct timeval *tv , const struct timezone *tz);

#if defined(_HPUX_)
  #define CLOCK_INVALID           0 
  #define CLOCK_REALTIME          1       /* wall clock, not bound */
  #define CLOCK_VIRTUAL           2       /* user CPU usage clock */
  #define CLOCK_PROFILE           4       /* user and system CPU usage clock */
#elif defined(_SOLARIS_) 
  #define CLOCK_VIRTUAL           1       /* user CPU usage clock */
  #define CLOCK_PROFILE           2       /* user and system CPU usage clock */
  #define CLOCK_REALTIME          3       /* wall clock, not bound */
#elif defined(_LINUX_) || defined(_LINUXPPC_) 
/* Identifier for system-wide realtime clock.  */
#   define CLOCK_REALTIME               0       
/* Monotonic system-wide clock.  */        
#   define CLOCK_MONOTONIC              1       
/* High-resolution timer from the CPU.  */      
#   define CLOCK_PROCESS_CPUTIME_ID     2 
/* Thread-specific CPU-time clock.  */
#   define CLOCK_THREAD_CPUTIME_ID      3
#endif

#if defined(_CHDLL_) && !defined(_WIN32_)
#include <dlfcn.h>
void *_ChSysTime_handle = dlopen("libsystime.dl", RTLD_LAZY);
if(_ChSysTime_handle == NULL) { 
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChSysTime_handle in sys/time.h\n");
   exit(-1);
} 
void _dlclose_systime(void) {
   dlclose(_ChSysTime_handle);
}
atexit(_dlclose_systime);
#endif 

#endif /* _SYS_TIME_H_ */
