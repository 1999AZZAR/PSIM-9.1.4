/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: time.h
: Note: time header file
************************************************************/
#ifndef _TIME_H_
#define _TIME_H_

#ifndef _WIN32_        /* struct timeval is defined in winsock2.h */
#include <sys/time.h>  /* needed for struct timespec */
#endif
#include <signal.h>        /* needed for struct sigevent */

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#if defined(_M64_) || defined(_WIN32_)
typedef long long ssize_t;
#else
typedef int ssize_t;     
#endif
#endif   
 
#ifndef _CLOCK_T
#define _CLOCK_T
#ifdef _M64_
typedef long long clock_t;
#else
typedef int  clock_t;
#endif
#endif  

#ifndef _TIME_T
#define _TIME_T
#ifdef _M64_
typedef long long time_t;
#else
typedef int  time_t;
#endif
#endif

#ifndef _CLOCKID_T
#define _CLOCKID_T
typedef int     clockid_t;
#endif

#ifndef _TIMER_T
#define _TIMER_T
#if defined(_M64_) && !defined(_SOLARIS_) 
typedef long long timer_t;
#else
typedef int  timer_t;
#endif
#endif
 
#ifdef _WIN32_
#define CLOCKS_PER_SEC          1000
#else
#define CLOCKS_PER_SEC          1000000
#endif

#ifndef _TM_DEFINED
struct tm {
        int     tm_sec;
        int     tm_min;
        int     tm_hour;
        int     tm_mday;
        int     tm_mon;
        int     tm_year;
        int     tm_wday;
        int     tm_yday;
        int     tm_isdst;
#if defined(_LINUX_) || defined(_LINUXPPC_) || defined(_DARWIN_) || defined(_FREEBSD_) || defined(_QNX_)
        long int __tm_gmtoff;         /* Seconds east of UTC.  */
        char *__tm_zone;      /* Timezone abbreviation.  */
#endif 
};
#define _TM_DEFINED
#endif

extern clock_t clock(void);
extern double difftime(time_t, time_t);
extern time_t mktime(struct tm *);
extern time_t time(time_t *);
extern char *asctime(const struct tm *);
extern char *ctime (const time_t *);
extern struct tm *gmtime(const time_t *);
extern struct tm *localtime(const time_t *);
extern size_t strftime(char *, size_t, const char *, const struct tm *);

extern char *asctime_r(const struct tm *, char *, int);
extern char *ctime_r (const time_t *, char *, int);
extern struct tm *gmtime_r(const time_t *, struct tm *);
extern struct tm *localtime_r(const time_t *, struct tm *);

extern void tzset(void);
extern int cftime(char *, char *, const time_t *);
extern int ascftime(char *, const char *, const struct tm *);


extern int clock_getres(clockid_t, struct timespec *);
extern int clock_gettime(clockid_t, struct timespec *);
extern restrict int clock_settime(clockid_t, const struct timespec *);

extern int timer_create(clockid_t, struct sigevent *, timer_t *);
extern int timer_delete(timer_t);
extern int timer_getoverrun(timer_t);
extern int timer_gettime(timer_t, struct itimerspec *);
extern int timer_settime(timer_t, int, const struct itimerspec *,
                struct itimerspec *);
extern int nanosleep(const struct timespec *, struct timespec *);

/*
  handle extern variables 
*/
#if  defined(_CHDLL_) 
#include <dlfcn.h>
time_t timezone;
int daylight;
#if _isvar("tzname")
#pragma remvar(tzname)
#endif
char **tzname;
extern void *_ChTime_handle = dlopen("libtime.dl", RTLD_LAZY);
if(_ChTime_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChTime_handle in time.h\n");
   exit(-1);
} 
#if !defined(_SUN_)
else {
    void *fptr, ChTime_hInitialize(time_t *timezone, int *daylight, char ***tzname);

    fptr = dlsym(_ChTime_handle , "ChTime_hInitialize");
    if(fptr == NULL) { 
       fprintf(_stderr, "Error: dlsym(): ChTime_hInitialize() in time.h: %s\n", dlerror());
       exit(1);
    }
    dlrunfun(fptr, NULL, ChTime_hInitialize, &timezone, &daylight, &tzname);
}
#endif /* !defined(_SUN_) */
void _dlclose_time(void) {
   dlclose(_ChTime_handle);
}
atexit(_dlclose_time);
#endif

#endif /* _TIME_H_ */
