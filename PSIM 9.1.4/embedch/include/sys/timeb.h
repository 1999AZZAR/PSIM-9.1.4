/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
#ifndef _SYS_TIMEB_H
#define _SYS_TIMEB_H	1

#ifdef _CH_
#include <chdl.h>
LOAD_CHDL(timeb)
#endif

#include <time.h>
/* Structure returned by the `ftime' function.  */
struct timeb
  {
    time_t time;		/* Seconds since epoch, as from `time'.  */
    unsigned short int millitm;	/* Additional milliseconds.  */
    short int timezone;		/* Minutes west of GMT.  */
    short int dstflag;		/* Nonzero if Daylight Savings Time used.  */
  };

/* Fill in TIMEBUF with information about the current time.  */
extern int ftime (struct timeb *__timebuf);

#endif	/* sys/timeb.h */
