/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: limits.h
: Note: CH limits.h header file wraper
************************************************************/
#ifndef _LIMITS_H_
#define	_LIMITS_H_

/*
 * Sizes of integral types
 */
#define CHAR_BIT        8             /* number of bits in a char */ 
#define SCHAR_MIN       _SCHAR_MIN    /* min value of a "signed char" */
#define SCHAR_MAX       _SCHAR_MAX    /* max value of a "signed char" */
#define UCHAR_MAX       _UCHAR_MAX    /* max value of an "unsigned char" */
#define CHAR_MIN        _SCHAR_MIN    /* min value of a "char" */
#define CHAR_MAX        _SCHAR_MAX    /* max value of a "char" */
#define SHRT_MIN        _SHRT_MIN     /* min value of a "short int" */
#define SHRT_MAX        _SHRT_MAX     /* max value of a "short int" */
#define USHRT_MAX       _USHRT_MAX    /* max value of "unsigned short int" */
#define INT_MIN         _INT_MIN      /* min value of an "int" */
#define INT_MAX         _INT_MAX      /* max value of an "int" */
#define UINT_MAX        _UINT_MAX     /* max value of an "unsigned int" */
#define LONG_MIN        _LONG_MIN     /* min value of a "long int" */
#define LONG_MAX        _LONG_MAX     /* max value of a "long int" */
#define ULONG_MAX       _ULONG_MAX    /* max value of "unsigned long int" */
#define LLONG_MIN       _LLONG_MIN    /* min value of a "long long int" */
#define LLONG_MAX       _LLONG_MAX    /* max value of a "long long int" */
#define ULLONG_MAX      _ULLONG_MAX   /* max value of "unsigned long long int" */
#include <ch/limits.h>
 
#endif /* _LIMITS_H_ */
