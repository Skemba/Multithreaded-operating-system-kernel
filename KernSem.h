#ifndef _KERNSEM_H_
#define _KERNSEM_H_

#include "Thread.h"
#include "Queues.h"
#include "PCB.h"

class KernelSem {


public:
	KernelSem(int init);
	virtual ~KernelSem();
	virtual void signal();
	virtual void wait();
	ID getId();
	int value();

private: 
	static ID Id;
	ID id;
	int val;
	Queues<PCB> *blocked;
	void block();
	void deblock();

};

#endif
