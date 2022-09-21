/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/* ISO C99: 7.18 Integer types <stdint.h> */

#ifndef _STDINT_H
#define _STDINT_H	1

/* Exact integral types.  */

/* Signed.  */

typedef signed char		int8_t;
typedef short int		int16_t;
typedef int			int32_t;
typedef long long int		int64_t;

/* Unsigned.  */
typedef unsigned char		uint8_t;
typedef unsigned short int	uint16_t;
typedef unsigned int		uint32_t;
typedef unsigned long long int	uint64_t;


/* Small types.  */

/* Signed.  */
typedef signed char		int_least8_t;
typedef short int		int_least16_t;
typedef int			int_least32_t;
typedef long long int		int_least64_t;

/* Unsigned.  */
typedef unsigned char		uint_least8_t;
typedef unsigned short int	uint_least16_t;
typedef unsigned int		uint_least32_t;
typedef unsigned long long int	uint_least64_t;


/* Fast types.  */

/* Signed.  */
typedef signed char		int_fast8_t;
typedef int			int_fast16_t;
typedef int			int_fast32_t;
typedef long long int		int_fast64_t;

/* Unsigned.  */
typedef unsigned char		uint_fast8_t;
typedef unsigned int		uint_fast16_t;
typedef unsigned int		uint_fast32_t;
typedef unsigned long long int	uint_fast64_t;


/* Types for `void *' pointers.  */
typedef int			intptr_t;
typedef unsigned int		uintptr_t;

/* Largest integral types.  */
typedef long long int		intmax_t;
typedef unsigned long long int	uintmax_t;


/* The ISO C99 standard specifies that in C++ implementations these
   macros should only be defined if explicitly requested.  */
#if defined __STDC_LIMIT_MACROS
#define __INT64_C(c)	c ## LL
#define __UINT64_C(c)	c ## ULL
# endif

/* Limits of integral types.  */

/* Minimum of signed integral types.  */
#define INT8_MIN		_SCHAR_MIN
#define INT16_MIN		_SHRT_MIN
#define INT32_MIN		_INT_MIN
#define INT64_MIN		_LLONG_MIN
/* Maximum of signed integral types.  */
#define INT8_MAX		_SCHAR_MAX
#define INT16_MAX		_SHRT_MAX
#define INT32_MAX		_INT_MAX
#define INT64_MAX		_LLONG_MAX

/* Maximum of unsigned integral types.  */
#define UINT8_MAX		_UCHAR_MAX
#define UINT16_MAX		_USHRT_MAX
#define UINT32_MAX		_UINT_MAX
#define UINT64_MAX		_ULLONG_MAX


/* Minimum of signed integral types having a minimum size.  */

#define INT_LEAST8_MIN		_SCHAR_MIN
#define INT_LEAST16_MIN		_SHRT_MIN
#define INT_LEAST32_MIN		_INT_MIN
#define INT_LEAST64_MIN		_LLONG_MIN
/* Maximum of signed integral types having a minimum size.  */
#define INT_LEAST8_MAX		_SCHAR_MAX
#define INT_LEAST16_MAX        _SHRT_MAX
#define INT_LEAST32_MAX        _INT_MAX
#define INT_LEAST64_MAX        _LLONG_MAX

/* Maximum of unsigned integral types having a minimum size.  */
#define UINT_LEAST8_MAX		_UCHAR_MAX
#define UINT_LEAST16_MAX        _USHRT_MAX
#define UINT_LEAST32_MAX        _UINT_MAX
#define UINT_LEAST64_MAX        _ULLONG_MAX

/* Minimum of fast signed integral types having a minimum size.  */
#define INT_FAST8_MIN		_SCHAR_MIN
#define INT_FAST16_MIN	        _INT_MIN
#define INT_FAST32_MIN	        _INT_MIN
#define INT_FAST64_MIN		_LLONG_MIN
/* Maximum of fast signed integral types having a minimum size.  */
#define INT_FAST8_MAX	_SCHAR_MAX
#define INT_FAST16_MAX	_INT_MAX
#define INT_FAST32_MAX	_INT_MAX
#define INT_FAST64_MAX	_LLONG_MAX

/* Maximum of fast unsigned integral types having a minimum size.  */
#define UINT_FAST8_MAX  _UCHAR_MAX
#define UINT_FAST16_MAX	_UINT_MAX
#define UINT_FAST32_MAX	_UINT_MAX
#define UINT_FAST64_MAX	_ULLONG_MAX


/* Values to test for integral types holding `void *' pointer.  */
#define INTPTR_MIN		(-2147483647-1)
#define INTPTR_MAX		(2147483647)
#define UINTPTR_MAX		(4294967295U)


/* Minimum for largest signed integral type.  */
# define INTMAX_MIN	_LLONG_MIN
/* Maximum for largest signed integral type.  */
# define INTMAX_MAX	_LLONG_MAX

/* Maximum for largest unsigned integral type.  */
# define UINTMAX_MAX    _ULLONG_MAX


/* Limits of other integer types.  */

/* Limits of `ptrdiff_t' type.  */
#ifdef _M64_
#define PTRDIFF_MIN		_LLONG_MIN
#define PTRDIFF_MAX		_LLONG_MAX
#else
#define PTRDIFF_MIN		(-2147483647-1)
#define PTRDIFF_MAX		(2147483647)
#endif

/* Limits of `sig_atomic_t'.  */
# define SIG_ATOMIC_MIN		(-2147483647-1)
# define SIG_ATOMIC_MAX		(2147483647)

/* Limit of `size_t' type.  */
#define SIZE_MAX		(4294967295U)

/* Limits of `wchar_t'.  */
/* These constants might also be defined in <wchar.h>.  */
#ifndef WCHAR_MAX
#define WCHAR_MAX       2147483647
#endif
#ifndef WCHAR_MIN
#define WCHAR_MIN       (-2147483647-1)
#endif

/* Limits of `wint_t'.  */
# define WINT_MIN		(0u)
# define WINT_MAX		(4294967295u)


/* The ISO C99 standard specifies that in C++ implementations these
   should only be defined if explicitly requested.  */

/* Signed.  */
# define INT8_C(c)	c
# define INT16_C(c)	c
# define INT32_C(c)	c
# define INT64_C(c)	c ## LL

/* Unsigned.  */
# define UINT8_C(c)	c ## U
# define UINT16_C(c)	c ## U
# define UINT32_C(c)	c ## U
# define UINT64_C(c)	c ## ULL

/* Maximal type.  */
#define INTMAX_C(c)	c ## LL
#define UINTMAX_C(c)	c ## ULL


#endif /* stdint.h */
