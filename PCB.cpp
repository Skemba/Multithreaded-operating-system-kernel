/*
 * PCB.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: OS1
 */

#include "PCB.h"
#include "Thread.h"
#include <dos.h>
#include <iostream.h>
#include "CompQue.h"
#include "util.h"

ID PCB::Id = 0;
PCB* PCB::running = 0;

PCB::PCB(StackSize st) {

	id = 0;
	s = st;
	bp = sp = ss = 0;
	stack = 0;
	state = CREATED;
	t = 10;
	thr = 0;
	complSem = 0;
	proteklo_vreme = 0;
	doTheFlop = 0;

}

PCB::PCB(StackSize st, Time ts, Thread* t) {

	if(ts == 0) doTheFlop = 0;
	else doTheFlop = 1;
	id = ++Id;
	thr = t;
	this->complSem = new CompQue(this->id);
	s = st;
	this->t = ts;
	bp = 0;
	sp = 0;
	ss = 0;
	stack = 0;
	state = CREATED;
	proteklo_vreme = 0;


}

PCB::~PCB() {

	if(this->id == 0) dispatch();

}

void PCB::createStack() {

	stack = new unsigned[s];
#ifndef BCC_BLOCK_IGNORE
		stack[s-1] = FP_SEG(thr);
		stack[s-2] = FP_OFF(thr);
		stack[s-5] = 0x200;
		stack[s-6] = FP_SEG(Thread::wrapper);
		stack[s-7] = FP_OFF(Thread::wrapper);
		this->sp = FP_OFF(&stack[s - 16]);		//SP treba da bude na ovom mestu (namestamo ga na to mesto)
		this->bp = FP_OFF(&stack[s - 16]);
		this->ss = FP_SEG(&stack[s - 16]);		//SEG kupi segment od adrese koju prosledimo
#endif

}

void PCB::createKernelStack() {
	stack = new unsigned[4096];
}
