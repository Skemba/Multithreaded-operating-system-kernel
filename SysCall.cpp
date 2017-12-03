/*
 * SysCall.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: OS1
 */

#include <dos.h>
#include <stdio.h>
#include <iostream.h>
#include "SysCall.h"
#include "Thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "KernQue.h"
#include "KernSem.h"
#include "Semaphor.h"
#include "SleepQue.h"
#include "util.h"
#include "KernEv.h"

#define ARGG 15

extern void tick();

int clle;
unsigned adrr;
unsigned sgg;
unsigned offf;

CompQue* SysCall::p = 0;
int SysCall::prekidjebio = 0;
KernelSem* dva;
InterPtr SysCall::oldTimer = NULL;
InterPtr SysCall::oldroutine = 0;
int SysCall::inSysCall = 0;
PCB* SysCall::SysCaller = 0;
PCB* SysCall::SysPCB = 0;
unsigned* SysCall::runningSp = 0;
unsigned* SysCall::runningBp = 0;
unsigned* SysCall::runningSs = 0;
unsigned* SysCall::sysSs = 0;
unsigned* SysCall::sysSp = 0;
unsigned* SysCall::sysBp = 0;
Argumenti* ar;
void* SysCall::caller = 0;
static int argcnt = 0;
ID SysCall::callerID = 0;

int SysCall::zahtev = 0;

int i;

PCB* jedan;
KernelEv* one;


void interrupt SysCall::startSysCall(...) {

#ifndef BCC_BLOCK_IGNORE
	asm {
		sti;
	}
#endif

	SysCall::zahtev = 1;

	//if in sys mode do nothing
	if (SysCall::inSysCall > 0 || PCB::running == 0)
		return;

		SysCall::inSysCall++;

		SysCall::SysCaller = PCB::running;

#ifndef BCC_BLOCK_IGNORE
		PCB::running->ss = _SS;
		PCB::running->sp = _SP;
		PCB::running->bp = _BP;
#endif

#ifndef BCC_BLOCK_IGNORE
		SysCall::runningSp = (unsigned*)MK_FP(PCB::running->ss, PCB::running->sp);
		SysCall::runningBp = (unsigned*)MK_FP(PCB::running->ss, PCB::running->bp);
		SysCall::runningSs = (unsigned*)MK_FP(PCB::running->ss, PCB::running->ss);
#endif

		SysCall::sysSp = SysCall::SysPCB->stack + 4096 - 121; //121 - mesto za argumente koji su nam potrebni

		for (argcnt = 0; argcnt < ARGG; argcnt++)
				SysCall::sysSp[argcnt] = SysCall::runningSp[argcnt];



#ifndef BCC_BLOCK_IGNORE
		_SS = FP_SEG(SysCall::sysSp);
		_SP = FP_OFF(SysCall::sysSp);
		_BP = FP_OFF(SysCall::sysSp);
#endif


	clle = SysCall::sysSp[5];

	if(clle == 1) {

		offf = SysCall::sysSp[6];
		sgg = SysCall::sysSp[7];

#ifndef BCC_BLOCK_IGNORE

		ar = (Argumenti*) MK_FP(sgg, offf);

		jedan = new PCB(ar->sz, ar->tm, ar->thr);
		ar->id = jedan->getId();
#endif

		KernelQueues::pcbQQ->put(jedan, 0);

	}

	if(clle == 2) {

		destroy();

	}

	if(clle == 3) {

		SysCall::dispatch();

	}

	if(clle == 4) {


		offf = SysCall::sysSp[6];
		sgg = SysCall::sysSp[7];

#ifndef BCC_BLOCK_IGNORE

		ar = (Argumenti*) MK_FP(sgg, offf);

		callerID = ar->id;

#endif


		jedan = KernelQueues::pcbQQ->getById(callerID);
		jedan->createStack();
		jedan->state = READY;
		Scheduler::put(jedan);

	}

	if(clle == 5) {

		createSem();

	}

	if(clle == 6) {
		waitToCompl();
	}

	if(clle == 7) {
		semval();
	}

	if(clle == 8) {
		waitSem();
	}

	if(clle == 9) {
		signalSem();
	}

	if(clle == 10) {
		sleep();
	}

	if(clle == 11) {


		offf = SysCall::sysSp[6];
		sgg = SysCall::sysSp[7];

		#ifndef BCC_BLOCK_IGNORE

				ar = (Argumenti*) MK_FP(sgg, offf);

				one = new KernelEv(ar->ivt, ar->ev);
				ar->evID = one->getId();
		#endif

				KernelQueues::evQQ->put(one, 0);


	}

	if (clle == 12) {

		waitEv();

	}

	if(clle == 13) {

		signalEv();

	}

	if(clle == 14) {
		Evdestructor();
	}

	if(clle == 15) {
		Thrdestructor();
	}

	if(clle == 16) {
		Semdestructor();
	}
#ifndef BCC_BLOCK_IGNORE
	SysCall::sysSp = (unsigned*)MK_FP(_SS, _SP);
#endif

	for (argcnt = 0; argcnt < 12; argcnt++)
			SysCall::runningSp[argcnt] = SysCall::sysSp[argcnt];

	SysCall::inSysCall--;


#ifndef BCC_BLOCK_IGNORE
		_SS = PCB::running->ss;
		_SP = PCB::running->sp;
		_BP = PCB::running->bp;
#endif

		SysCall::zahtev = 0;
}

void interrupt SysCall::newTimer(...) {


					SysCall::oldTimer();
					tick();
					KernelQueues::sleep->check();
					PCB::running->proteklo_vreme++;

				if ((PCB::running->proteklo_vreme >= PCB::running->t || SysCall::prekidjebio) && PCB::running->doTheFlop) 	{
					if(SysCall::zahtev == 1) SysCall::prekidjebio = 1;
					else {


	#ifndef BCC_BLOCK_IGNORE
					PCB::running->sp = _SP;
					PCB::running->ss = _SS;
					PCB::running->bp = _BP;
	#endif


					if (PCB::running->state == READY && PCB::running->getId() != 1) {
						Scheduler::put(PCB::running); }


					PCB::running = Scheduler::get();
					if(PCB::running == 0)  {  PCB::running = KernelQueues::pcbQQ->getById(2); }

	#ifndef BCC_BLOCK_IGNORE
					_SP = PCB::running->sp;
					_SS = PCB::running->ss;
					_BP = PCB::running->bp;
	#endif

					PCB::running->proteklo_vreme = 0;
					SysCall::prekidjebio = 0;
				} }


}

void SysCall::destroy() {

	offf = SysCall::sysSp[6];
	sgg = SysCall::sysSp[7];

	#ifndef BCC_BLOCK_IGNORE

			ar = (Argumenti*) MK_FP(sgg, offf);
	#endif

			jedan = KernelQueues::pcbQQ->getById(ar->id);
			jedan->state = DONE;
			KernelQueues::sleep->removeAll();
		     p = KernelQueues::WaitToCompl->getById(ar->id);
			if(p) {
				p->free();
				KernelQueues::WaitToCompl->remove(p); }


}

void SysCall::dispatch() {


			if (PCB::running->state == READY) {
				Scheduler::put(PCB::running);
			}



			PCB::running = Scheduler::get();


			if(PCB::running == 0)  { cout << "RUNNING JE 0! " << endl; PCB::running = KernelQueues::pcbQQ->getById(2); }


			PCB::running->proteklo_vreme = 0;


}

void SysCall::createSem() {

		offf = SysCall::sysSp[6];
		sgg = SysCall::sysSp[7];

		#ifndef BCC_BLOCK_IGNORE

				ar = (Argumenti*) MK_FP(sgg, offf);
		#endif

		dva = new KernelSem(ar->init);
		ar->semID = dva->getId();

		KernelQueues::semQQ->put(dva,0);

}

void SysCall::waitToCompl() {

		offf = SysCall::sysSp[6];
		sgg = SysCall::sysSp[7];

			#ifndef BCC_BLOCK_IGNORE

					ar = (Argumenti*) MK_FP(sgg, offf);
			#endif

		if (KernelQueues::pcbQQ->getById(ar->id)->state != DONE) {
			p = KernelQueues::WaitToCompl->getById(ar->id);
			if(!p) {
				p = new CompQue(ar->id);
				KernelQueues::WaitToCompl->put(p,0);
			}

			p->put(PCB::running);
			PCB::running->state = BLOCKED;
			SysCall::dispatch();

		}
}

void SysCall::semval() {

		offf = SysCall::sysSp[6];
		sgg = SysCall::sysSp[7];

				#ifndef BCC_BLOCK_IGNORE

						ar = (Argumenti*) MK_FP(sgg, offf);
				#endif

		dva = KernelQueues::semQQ->getById(ar->semID);
		ar->val = dva->value();

}

void SysCall::waitSem() {

		offf = SysCall::sysSp[6];
		sgg = SysCall::sysSp[7];

			#ifndef BCC_BLOCK_IGNORE

					ar = (Argumenti*) MK_FP(sgg, offf);
			#endif

		dva = KernelQueues::semQQ->getById(ar->semID);
		dva->wait();

}

void SysCall::signalSem() {

		offf = SysCall::sysSp[6];
		sgg = SysCall::sysSp[7];

			#ifndef BCC_BLOCK_IGNORE

					ar = (Argumenti*) MK_FP(sgg, offf);
			#endif

		dva = KernelQueues::semQQ->getById(ar->semID);
		dva->signal();

}

void SysCall::sleep() {

		offf = SysCall::sysSp[6];
		sgg = SysCall::sysSp[7];

			#ifndef BCC_BLOCK_IGNORE

					ar = (Argumenti*) MK_FP(sgg, offf);
			#endif

		KernelQueues::sleep->putsleep(PCB::running, ar->tm);
		SysCall::dispatch();

}


void SysCall::waitEv() {

			offf = SysCall::sysSp[6];
			sgg = SysCall::sysSp[7];

				#ifndef BCC_BLOCK_IGNORE

						ar = (Argumenti*) MK_FP(sgg, offf);
				#endif

			one = KernelQueues::evQQ->getById(ar->evID);
			one->wait();
			dispatch();

}

void SysCall::signalEv() {

			offf = SysCall::sysSp[6];
			sgg = SysCall::sysSp[7];

				#ifndef BCC_BLOCK_IGNORE

						ar = (Argumenti*) MK_FP(sgg, offf);
				#endif

			one = KernelQueues::evQQ->getById(ar->evID);
			one->signal();


}

void SysCall::Evdestructor() {

			offf = SysCall::sysSp[6];
			sgg = SysCall::sysSp[7];

					#ifndef BCC_BLOCK_IGNORE

							ar = (Argumenti*) MK_FP(sgg, offf);
					#endif

			KernelQueues::evQQ->remove(KernelQueues::evQQ->getById(ar->evID));

}

void SysCall::Thrdestructor() {

			offf = SysCall::sysSp[6];
			sgg = SysCall::sysSp[7];

					#ifndef BCC_BLOCK_IGNORE

							ar = (Argumenti*) MK_FP(sgg, offf);
					#endif

			KernelQueues::pcbQQ->remove(KernelQueues::pcbQQ->getById(ar->id));

}

void SysCall::Semdestructor() {

	offf = SysCall::sysSp[6];
	sgg = SysCall::sysSp[7];

			#ifndef BCC_BLOCK_IGNORE

					ar = (Argumenti*) MK_FP(sgg, offf);
			#endif

	KernelQueues::semQQ->remove(KernelQueues::semQQ->getById(ar->semID));

}
