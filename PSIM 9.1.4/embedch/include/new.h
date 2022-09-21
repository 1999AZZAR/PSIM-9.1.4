/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: new.h
************************************************************/
#ifndef _NEW_H_
#define _NEW_H_

void (*set_new_handler (void(*)(void)))(void);
/* the same as
typedef void (*FuncHandler_t)(void);
FuncHandler_t set_new_handler(FuncHandler);
*/

#endif	/* _NEW_H_ */
