/*
 * PCB.h
 *
 *  Created on: May 29, 2015
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "Thread.h"
#include "KernSem.h"
#include "CompQue.h"

enum STATES { CREATED = 0, READY = 1, BLOCKED = 2, DONE = 3, SLEEP = 4 };
class KernelSem;

class PCB {

public :

	PCB(StackSize st);
	PCB(StackSize st, Time ts, Thread* t);
	~PCB();
	ID getId() { return id; }
	void createStack();
	void createKernelStack();
	static PCB* running;
	void initKernelPCBsem();
	STATES state;
	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned* stack;
	int proteklo_vreme;
	Time t;
	CompQue *complSem;
	int doTheFlop;

private :
	static ID Id;
	ID id;
	Thread *thr;
	StackSize s;


};



#endif /* PCB_H_ */
