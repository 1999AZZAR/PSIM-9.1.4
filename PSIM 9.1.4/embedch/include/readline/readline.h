/************************************************************
* File name: readline.h
: Note: readline.h header file 
************************************************************/
#ifndef _READLINE_H_
#define	_READLINE_H_

char * readline(char *prompt);

#if defined(_CHDLL_)
#include <dlfcn.h>
void *_ChReadlineReadline_handle = dlopen("libreadline.dl", RTLD_LAZY);
if(_ChReadlineReadline_handle == NULL) {
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror());
   fprintf(_stderr, "       cannot get _ChReadlineReadline_handle in readline.h\n");
   exit(-1);
} 
void _dlclose_readlinereadline(void) {
   dlclose(_ChReadlineReadline_handle);
}
atexit(_dlclose_readlinereadline);
#endif

#endif /* _READLINE_H_ */
