/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: float.h
************************************************************/
#ifndef _FLOAT_H_
#define	_FLOAT_H_

#define FLT_MINIMUM     _FLT_MINIMUM
#ifdef _LYNX_         /* LynxOS */
#define FLT_RADIX       2
#define FLT_DIG         6
#define FLT_EPSILON     0.0000000596047
#define FLT_MANT_DIG    23
#define FLT_MAX         3.4028234663852890e38
#define FLT_MAX_EXP     127
#define FLT_MIN         1.17549436e-38        
#define FLT_MIN_EXP     (-37)
#define DBL_DIG         15
#define DBL_EPSILON     2e-16
#define DBL_MANT_DIG    52
#define DBL_MAX         1.797693134862315e308
#define DBL_MAX_EXP     1023
#define DBL_MIN         2.2250739e-308  
#else  /* SunOS HP-UX IRIX ULTRIX AIX Linux  Windows_NT */
#define FLT_RADIX         2
#define FLT_ROUNDS        1
#define FLT_MANT_DIG      24
#define FLT_EPSILON       1.19209290E-07F
#define FLT_DIG           6
#define FLT_MIN_EXP       (-125)
#define FLT_MIN           1.17549435E-38F
#define FLT_MIN_10_EXP    (-37)
#define FLT_MAX_EXP       128
#define FLT_MAX           3.40282347E+38F
#define FLT_MAX_10_EXP    38
 
#define DBL_MINIMUM     _DBL_MINIMUM
#define DBL_MANT_DIG      53
#define DBL_EPSILON       2.2204460492503131E-16
#define DBL_DIG           15
#define DBL_MIN_EXP       (-1021)
#define DBL_MIN           2.2250738585072014E-308
#define DBL_MIN_10_EXP    (-307)
#define DBL_MAX_EXP       1024
#define DBL_MAX           1.797693134862315E+308
#define DBL_MAX_10_EXP    308
#endif
 
#define LDBL_MANT_DIG    DBL_MANT_DIG   
#define LDBL_EPSILON     DBL_EPSILON   
#define LDBL_DIG         DBL_DIG      
#define LDBL_MIN_EXP     DBL_MIN_EXP 
#define LDBL_MIN         DBL_MIN    
#define LDBL_MIN_10_EXP  DBL_MIN_10_EXP
#define LDBL_MAX_EXP     DBL_MAX_EXP  
#define LDBL_MAX         DBL_MAX     
#define LDBL_MAX_10_EXP  DBL_MAX_10_EXP 

/*
#define LDBL_MANT_DIG     113
#define LDBL_EPSILON      1.9259299443872358530559779425849273E-34L
#define LDBL_DIG          33
#define LDBL_MIN_EXP      (-16381)
#define LDBL_MIN          3.3621031431120935062626778173217526026E-4932L
#define LDBL_MIN_10_EXP   (-4931)
#define LDBL_MAX_EXP      16384
#define LDBL_MAX          1.1897314953572317650857593266280070162E4932L
#define LDBL_MAX_10_EXP   4932
*/

#define FLT_EVAL_METHOD -1
#define DECIMAL_DIG 21
#define HUGE_VALF FLT_MAX
#define MATH_ERRNO 1
#define MATH_ERREXCEPT 0
#define math_errhandling MATH_ERRNO

typedef float float_t;
typedef double double_t;

#endif /* _FLOAT_H_ */
