/*
 * KernQue.h
 *
 *  Created on: Jul 5, 2015
 *      Author: OS1
 */

#ifndef _KERNQUE_H_
#define _KERNQUE_H_

#include "Queues.h"
#include "KernSem.h"
#include "SleepQue.h"
#include "CompQue.h"
#include "KernEv.h"
#include "PCB.h"



class KernelQueues {

public:
	static Queues<KernelEv>* evQQ;
	static Queues<PCB> *pcbQQ;
	static Queues<KernelSem> *semQQ;
	static SleepQue* sleep;
	static Queues<CompQue>* WaitToCompl;
};


#endif /* _KERNQUE_H_ */
