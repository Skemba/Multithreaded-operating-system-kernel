/*
 * KernQue.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: OS1
 */


#include "KernQue.h"

Queues<PCB>* KernelQueues::pcbQQ = new Queues<PCB>();
Queues<KernelSem>* KernelQueues::semQQ = new Queues<KernelSem>();
SleepQue* KernelQueues::sleep = new SleepQue();
Queues<CompQue>* KernelQueues::WaitToCompl = new Queues<CompQue>();
Queues<KernelEv>* KernelQueues::evQQ = new Queues<KernelEv>();

