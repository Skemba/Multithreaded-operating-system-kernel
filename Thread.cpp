/*
 * Thread.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: OS1
 */
#include "Thread.h"
#include "SysCall.h"
#include "util.h"
#include <dos.h>
#include <iostream.h>
#include "KernQue.h"
#include "SleepQue.h"
#include "PCB.h"

Argumenti* arg = new Argumenti();

unsigned int sg;
unsigned off;

int flag;

Thread::Thread (StackSize stackSize, Time timeSlice) {


	flag = 1;

	arg->sz = stackSize;
	arg->tm = timeSlice;
	arg->thr = this;



#ifndef BCC_BLOCK_IGNORE
	off = FP_OFF(arg);
	sg = FP_SEG(arg);
#endif
#ifndef BCC_BLOCK_IGNORE
	asm {

		mov dx, flag
		mov cx, off
		mov bx, sg

	}
#endif

#ifndef BCC_BLOCK_IGNORE
	asm {

		int 60

	}
#endif
	id = arg->id;





}

Thread::~Thread() {

		waitToComplete();

		flag = 15;

		arg->id = this->id;

	#ifndef BCC_BLOCK_IGNORE
		off = FP_OFF(arg);
		sg = FP_SEG(arg);
	#endif
	#ifndef BCC_BLOCK_IGNORE
		asm {

			mov dx, flag
			mov cx, off
			mov bx, sg

		}
	#endif

	#ifndef BCC_BLOCK_IGNORE
		asm {

			int 60

		}
	#endif

}


void Thread::waitToComplete() {


	flag = 6;

	arg->id = this->id;



#ifndef BCC_BLOCK_IGNORE
	off = FP_OFF(arg);
	sg = FP_SEG(arg);
#endif
#ifndef BCC_BLOCK_IGNORE
	asm {

		mov dx, flag
		mov cx, off
		mov bx, sg

	}
#endif

#ifndef BCC_BLOCK_IGNORE
	asm {

		int 60

	}
#endif



}

void Thread::sleep(Time t) {


	flag = 10;

	arg->tm = t;

#ifndef BCC_BLOCK_IGNORE
	off = FP_OFF(arg);
	sg = FP_SEG(arg);
#endif
#ifndef BCC_BLOCK_IGNORE
	asm {

		mov dx, flag
		mov cx, off
		mov bx, sg

	}
#endif

#ifndef BCC_BLOCK_IGNORE
	asm {

		int 60

	}
#endif


}

void Thread:: wrapper(Thread* running) {

		running->run();


	flag = 2;

		arg->id = running->id;

	#ifndef BCC_BLOCK_IGNORE
		off = FP_OFF(arg);
		sg = FP_SEG(arg);
	#endif

	#ifndef BCC_BLOCK_IGNORE
		asm {

			mov dx, flag
			mov cx, off
			mov bx, sg

		}
	#endif

	#ifndef BCC_BLOCK_IGNORE
		asm {

			int 60

		}
	#endif



		dispatch();


}

void dispatch() {


	flag = 3;

	arg->zahtev = 1;



#ifndef BCC_BLOCK_IGNORE
	off = FP_OFF(arg);
	sg = FP_SEG(arg);
#endif
#ifndef BCC_BLOCK_IGNORE
	asm {

		mov dx, flag
		mov cx, off
		mov bx, sg

	}
#endif

#ifndef BCC_BLOCK_IGNORE
	asm {

		int 60

	}
#endif



}

void Thread::start() {


	flag = 4;

	arg->thr = this;
	arg->id = this->id;


#ifndef BCC_BLOCK_IGNORE
	off = FP_OFF(arg);
	sg = FP_SEG(arg);
#endif
#ifndef BCC_BLOCK_IGNORE
	asm {

		mov dx, flag
		mov bx, sg
		mov cx, off

		int 60

	}
#endif


}

void Thread::run() {}

