/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: stdarg.h
************************************************************/
#ifndef _STDARG_H_
#define _STDARG_H_

#include <sys/va_list.h>
/* used as 2nd arg of va_start() for func(...) */
#define VA_NOARG 

#define va_start(list, name) list = __va_start()
#define va_count(list) __va_count(list)
#define va_copy(des,src) des=src
#define va_arg(list, type) ((type *)__va_arg((type*)&list))[0]
#define va_datatype(list) __va_array(list, -1)
#define va_arraydim(list) __va_array(list, -2)
#define va_arraytype(list) __va_array(list, -3) 
#define va_arraynum(list) __va_array(list, -4) 
/* int a[n][m]; index 0 for n, index 1 for m */ 
#define va_arrayextent(list, index) __va_array(list, index)
extern void va_end(va_list);
#define va_end(list) 
/*     va_elementtype(), va_dim, va_isarray(), va_extent() are obsolete */ 
/* use va_datatype(), va_arraydim(), va_arraytype(), va_arrayextent() */
#define va_elementtype(list) __va_array(list, -1)
#define va_dim(list) __va_array(list, -2)
#define va_isarray(list) __va_array(list, -3) 
#define va_extent(list, index) __va_array(list, index)
#define va_tagname(list) __va_tagname(list)

extern int arraycopy(void *des, int destype, void *src, int srctype, unsigned int n);

/* data type in Ch */
typedef enum _elementtype {
    CH_UNDEFINETYPE,/* undefined type */
    /* simple type */
    CH_CHARTYPE=10, /* char */
    CH_UCHARTYPE,   /* unsigned char */
    CH_SHORTTYPE,   /* short */
    CH_USHORTTYPE,  /* unsigned short */
    CH_INTTYPE,     /* int, long int */
    CH_UINTTYPE,    /* unsigned int, unsigned long int */
    CH_LLINTTYPE,   /* long long int */
    CH_ULLINTTYPE,  /* unsigned long long int */
    CH_FLOATTYPE,   /* float */
    CH_DOUBLETYPE,  /* double */
    CH_LDOUBLETYPE, /* long double */
    CH_COMPLEXTYPE, /* float complex */
    CH_LCOMPLEXTYPE,/* long complex */
    CH_STRINGTYPE,  /* string_t type */
    CH_FILETYPE,    /* FILE */
    CH_VOIDTYPE,    /* void */
    CH_PROCTYPE,    /* function type */
    CH_STRUCTTYPE,  /* struct */
    CH_CLASSTYPE,   /* class */
    CH_UNIONTYPE,   /* union */
    CH_ENUMTYPE,    /* enum */

/* returned Ch array type for Ch_VaArrayType(), Ch_ArrayType(), and Ch_FuncArgArrayType() */
/* CH_CARRAYTYPE and CH_CHARRAYTYPE are also used in ChVarArgsAddArg() and Ch_SetVar() */
/* Ch_VarArgsAddArg(&arglist, CH_CARRAYTYPE, CH_INTTYPE, a, dim, extent, ...) */
/* Ch_VarArgsAddArg(&arglist, CH_CHARRAYTYPE, CH_INTTYPE, a, dim, extent, ...) */
    CH_CARRAYTYPE=80,  /* int a[3] */
    CH_CARRAYPTRTYPE,  /* int f(int (*ap)[3]); Ch_FuncArgDataType(ap) is CH_INTTYPE, 
                           Ch_FuncArgArrayType(ap) is CH_CARRAYPTRTYPE */
                       /* int (*p)[3]); p is pointer to int when not inside a function arg, 
                          Ch_DataType(p) is CH_INTPTRTYPE, Ch_ArrayType(ap) is CH_UNDEFINETYPE */
    CH_CARRAYVLATYPE,  /* int a[n]; int func(int a[n], int b[:], int c[&]) */
    CH_CHARRAYTYPE,    /* array int a[3] */
    CH_CHARRAYPTRTYPE, /* array int (*ap)[3] */
    CH_CHARRAYVLATYPE, /* array int a[n]; int fun(array int a[n], array int b[:], array int c[&]) */

    /* pointer */
    CH_NULLTYPE = 100, /* NULL */
    CH_VOIDPTRTYPE,    /* void* */
    CH_CHARPTRTYPE,    /* char* */
    CH_UCHARPTRTYPE,   /* unsigned char* */
    CH_SHORTPTRTYPE,   /* short* */
    CH_USHORTPTRTYPE,  /* unsigned short* */
    CH_INTPTRTYPE,     /* int*, long int * */
    CH_UINTPTRTYPE,    /* unsigned int*, unsigned long int * */
    CH_LLINTPTRTYPE,   /* long long int* */
    CH_ULLINTPTRTYPE,  /* unsigned long long int* */
    CH_FLOATPTRTYPE,   /* float* */
    CH_DOUBLEPTRTYPE,  /* double* */
    CH_LDOUBLEPTRTYPE, /* long double* */
    CH_COMPLEXPTRTYPE, /* float complex* */
    CH_LCOMPLEXPTRTYPE,/* long complex* */
    CH_STRINGPTRTYPE,  /* string_t * */
    CH_PROCPTRTYPE,    /* function ptr type */
    CH_FILEPTRTYPE,    /* FILE * */
    CH_STRUCTPTRTYPE,  /* struct * */
    CH_CLASSPTRTYPE,   /* class* */
    CH_UNIONPTRTYPE,   /* union * */
    CH_ENUMPTRTYPE,    /* enum * */

    /* double pointer */
    CH_VOIDPTR2TYPE=200,/* void** */
    CH_CHARPTR2TYPE,    /* char** */
    CH_UCHARPTR2TYPE,   /* unsigned char** */
    CH_SHORTPTR2TYPE,   /* short** */
    CH_USHORTPTR2TYPE,  /* unsigned short** */
    CH_INTPTR2TYPE,     /* int*, long int** */
    CH_UINTPTR2TYPE,    /* unsigned int**, unsigned long int** */
    CH_LLINTPTR2TYPE,   /* long long int** */
    CH_ULLINTPTR2TYPE,  /* unsigned long long int** */
    CH_FLOATPTR2TYPE,   /* float** */
    CH_DOUBLEPTR2TYPE,  /* double** */
    CH_LDOUBLEPTR2TYPE, /* long double** */
    CH_COMPLEXPTR2TYPE, /* float complex** */
    CH_LCOMPLEXPTR2TYPE,/* long complex** */
    CH_STRINGPTR2TYPE,  /* string_t ** */
    CH_FILEPTR2TYPE,    /* FILE ** */
    CH_STRUCTPTR2TYPE,  /* struct ** for now */
    CH_CLASSPTR2TYPE,   /* class ** */
    CH_UNIONPTR2TYPE,    /* union ** */
    CH_ENUMPTR2TYPE     /* enum ** */
} ChType_t;

#endif  /* _STDARG_H_ */  
