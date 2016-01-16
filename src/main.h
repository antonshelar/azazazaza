/*
 * main.h
 *
 *  Created on: Jan 7, 2016
 *      Author: os
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>

#define	MESSAGE(text)	printf("%s:%d %s(): %s", __FILE__, __LINE__, __func__, text);


static inline void _assert(){


}

extern int wnd_id;

#endif /* MAIN_H_ */
