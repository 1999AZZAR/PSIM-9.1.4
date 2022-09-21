/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: locale.h
************************************************************/
#ifndef _LOCALE_H_
#define _LOCALE_H_

struct  lconv   {
        char *decimal_point;
        char *thousands_sep;
        char *grouping;
        char *int_curr_symbol;
        char *currency_symbol;
        char *mon_decimal_point;
        char *mon_thousands_sep;
        char *mon_grouping;
        char *positive_sign;
        char *negative_sign;
        char int_frac_digits;
        char frac_digits;
        char p_cs_precedes;
        char p_sep_by_space;
        char n_cs_precedes;
        char n_sep_by_space;
        char p_sign_posn;
        char n_sign_posn;
};

#ifdef _HPUX_
#define LC_CTYPE        0
#define LC_NUMERIC      1
#define LC_TIME         2
#define LC_COLLATE      3
#define LC_MONETARY     4
#define LC_MESSAGES     5
#define LC_ALL          6
#else
#define LC_ALL          0
#define LC_COLLATE      1
#define LC_CTYPE        2
#define LC_MONETARY     3
#define LC_NUMERIC      4
#define LC_TIME         5
#define LC_MESSAGES     6
#define LC_MIN          LC_ALL
#define LC_MAX          LC_TIME
#endif

extern char *setlocale(int, const char *);
extern struct lconv *localeconv(void);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChLocale_handle = dlopen("liblocale.dl", RTLD_LAZY);
if(_ChLocale_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChLocale_handle in locale.h\n");
   exit(-1);
} 
void _dlclose_locale(void) {
   dlclose(_ChLocale_handle);
}
atexit(_dlclose_locale);
#endif

#endif	/* _LOCALE_H_ */
