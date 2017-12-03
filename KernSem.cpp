#include "Thread.h"
#include "KernSem.h"
#include "util.h"
#include "SysCall.h"
#include "SCHEDULE.H"

ID KernelSem::Id = 0;

KernelSem::KernelSem(int init) {

	id = ++Id;
	this->val = init;
	blocked = new Queues<PCB>();
	
}

int KernelSem::value() {
	return this->val;
}

ID KernelSem::getId() {
	return id;
}

KernelSem::~KernelSem() {
	delete blocked;
}

void KernelSem::wait() {

	if(--val<0)

		block();

}

void KernelSem::signal() {


	if(val++<0)

		deblock();

}


void KernelSem:: block() {

	PCB::running->state=BLOCKED;
	blocked->put(PCB::running,0);
	SysCall::dispatch();
}

void KernelSem:: deblock(){

	PCB* temp = blocked->getFirst();
	temp->state=READY;
	Scheduler::put(temp);
}

