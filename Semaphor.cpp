/*
 * Semaphor.cpp
 *
 *  Created on: Jul 6, 2015
 *      Author: OS1
 */

#include "Semaphor.h"
#include "util.h"
#include "SysCall.h"
#include <dos.h>
#include "KernQue.h"

Argumenti* argg = new Argumenti();

Semaphore::Semaphore(int init) {

	argg->init = init;
	int flag = 5;
	unsigned off,sg;



#ifndef BCC_BLOCK_IGNORE
	off = FP_OFF(argg);
	sg = FP_SEG(argg);
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

		int 60;

	}
#endif


	SemID = argg->semID;

}

Semaphore::~Semaphore() {


		argg->semID = SemID;
		int flag = 16;
		unsigned off,sg;



		#ifndef BCC_BLOCK_IGNORE
			off = FP_OFF(argg);
			sg = FP_SEG(argg);
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

			int 60;

		}
	#endif



}

void Semaphore::signal() {
	argg->semID = SemID;
	int flag = 9;
	unsigned off,sg;



	#ifndef BCC_BLOCK_IGNORE
		off = FP_OFF(argg);
		sg = FP_SEG(argg);
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

		int 60;

	}
#endif


}

int Semaphore::val() const {


	argg->semID = SemID;
	int flag = 7;
	unsigned off,sg;

	#ifndef BCC_BLOCK_IGNORE
		off = FP_OFF(argg);
		sg = FP_SEG(argg);
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

		int 60;

	}
#endif



	return argg->val;
}

void Semaphore::wait() {
		argg->semID = SemID;
		int flag = 8;
		unsigned off,sg;



		#ifndef BCC_BLOCK_IGNORE
			off = FP_OFF(argg);
			sg = FP_SEG(argg);
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

		int 60;

	}
#endif


}



