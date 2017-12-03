/*
 * SysCall.h
 *
 *  Created on: Jun 5, 2015
 *      Author: OS1
 */

#ifndef SYSCALL_H_
#define SYSCALL_H_

#include "CompQue.h"
#include "util.h"

class PCB;

class SysCall
{
public:
	static CompQue* p;
	static void sleep();
	static PCB* SysPCB;
	static PCB* SysCaller;
	static int inSysCall;
	static void interrupt startSysCall(...);
	static void interrupt newTimer(...);
	static void createSysStack();
	static void* caller;
	static int switchOn;
	static int switchOff;
	static unsigned* runningSp;
	static unsigned* runningBp;
	static unsigned* runningSs;
	static unsigned* sysSs;
	static unsigned* sysSp;
	static unsigned* sysBp;
	static int zahtev;
	static InterPtr oldTimer;
	static ID callerID;
	static void destroy();
	static void createSem();
	static void waitToCompl();
	static void semval();
	static void waitSem();
	static void dispatch();
	static void signalSem();
	static InterPtr oldroutine;
	static int prekidjebio;
	static void waitEv();
	static void signalEv();
	static void Evdestructor();
	static void Thrdestructor();
	static void Semdestructor();

};


#endif /* SYSCALL_H_ */
