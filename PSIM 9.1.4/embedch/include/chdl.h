/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
#ifndef _CHDL_H_
#define _CHDL_H_

#if defined(_CHDLL_)
#include <dlfcn.h>

#define LOAD_CHDL(module_name)                  \
void* _Ch##module_name##_handle;                \
_Ch##module_name##_handle =                     \
   dlopen("lib" #module_name ".dl", RTLD_LAZY); \
if(_Ch##module_name##_handle == NULL) {                     \
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());    \
   fprintf(_stderr, "       cannot get _Ch"                 \
           #module_name"_handle in " #module_name ".h\n");  \
   _exit(-1);                                                \
}                                                           \
                                                            \
void _dlclose_lib##module_name(void) {                      \
  dlclose(_Ch##module_name##_handle);                       \
}                                                           \
atexit(_dlclose_lib##module_name);

/* LOAD_CHDL_CODE() is obsolete, use LOAD_CHDL() */
#define LOAD_CHDL_CODE(module_name,handle_prefix)                            \
void* _Ch##handle_prefix##_handle;                                           \
_Ch##handle_prefix##_handle = dlopen("lib" #module_name ".dl", RTLD_LAZY);   \
if(_Ch##handle_prefix##_handle == NULL) {                                    \
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());                     \
   fprintf(_stderr, "       cannot get _Ch"                                  \
           #handle_prefix "_handle in " #module_name ".h\n");                \
   exit(-1);                                                                 \
}                                                                            \
                                                                             \
void _dlclose_lib##module_name(void) {                                       \
  dlclose(_Ch##handle_prefix##_handle);                                      \
}                                                                            \
                                                                             \
atexit(_dlclose_lib##module_name);

#else /* empty */
#define LOAD_CHDL_CODE(module_name,handle_prefix) 
#define LOAD_CH_DL(module_name) 
#endif

#endif /*_CHDL_H_*/
