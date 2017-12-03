/*
 * util.h
 *
 *  Created on: Jun 24, 2015
 *      Author: OS1
 */

#ifndef UTIL_H_
#define UTIL_H_


#include <iostream.h>
#include "Thread.h"
class Event;


#define lock() { asm pushf; asm cli; }
#define unlock() { asm popf; }


typedef void interrupt(*InterPtr)(...);

struct Argumenti {

	StackSize sz;
	Event* ev;
	Time tm;
	Thread* thr;
	ID id;
	int zahtev;
	ID semID;
	int init;
	unsigned char ivt;
	int val;
	ID evID;

};

#endif /* UTIL_H_ */
