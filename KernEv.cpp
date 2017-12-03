/*
 * KernEv.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: OS1
 */




#include "kernEv.h"
#include "EvQue.h"
#include <dos.h>
#include "util.h"
#include "SCHEDULE.H"
#include "pcb.h"
#include "IVTEntry.h"
#include "KernQue.h"
#include "SysCall.h"

ID KernelEv:: posId=0;

KernelEv::KernelEv(IVTNo i, Event* ev)
{

	this->ev = ev;
	ivtNo=i;
	canUse = PCB::running;
	//cout << "Can use is :" << PCB::running->getId() << endl;
	IVTEntry::entries[i]->events->put(this);
	id=++posId;
	value = 0;

}

KernelEv::~KernelEv()
{

	if (IVTEntry::entries[ivtNo])
		IVTEntry::entries[ivtNo]->events->remove(this);

}

void KernelEv::wait()
{

	if (canUse != PCB::running) {
			cout << "nope" << endl;
			return;}


		value--;
		if (value<0) {
			block();
		}

}

void KernelEv::signal(){

		if (value++ < 0) deblock();

	if(SysCall::inSysCall == 0) {

		dispatch();
	}



}

void KernelEv:: block() {
	PCB::running->state=BLOCKED;
}

void KernelEv:: deblock(){
	canUse->state=READY;
	Scheduler::put(canUse);
}

int KernelEv:: val() const {
	return value;
}
