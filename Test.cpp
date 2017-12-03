/*
 * Test.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: OS1
 */

#include <iostream.h>
#include <stdio.h>
#include <dos.h>
#include "PCB.h"
#include "util.h"
#include "SysCall.h"
#include "KernQue.h"
#include "SCHEDULE.h"
#include "Semaphor.h"
#include "user.h"
#include "Idle.h"

extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]) {

#ifndef BCC_BLOCK_IGNORE
	SysCall::oldTimer = getvect(8);
	setvect(8, SysCall::newTimer);
	SysCall::oldroutine = getvect(60);
	setvect(60, SysCall::startSysCall);
#endif

	PCB* pocetna = new PCB(4096, 1, 0);
			pocetna->state = READY;
			PCB::running = pocetna;
			KernelQueues::pcbQQ->put(PCB::running, 0);


			SysCall::SysPCB = new PCB(4096);
			SysCall::SysPCB->createKernelStack();

			Idle* idl = new Idle();

			idl->start();

			KernelQueues::pcbQQ->put(SysCall::SysPCB, 0);

	userMain(argc, argv);



#ifndef BCC_BLOCK_IGNORE
	setvect(8, SysCall::oldTimer);
	setvect(60, SysCall::oldroutine);
#endif


	return 0;
}



