/*
 * Event.cpp
 *
 *  Created on: Aug 27, 2015
 *      Author: OS1
 */

#include "Event.h"
#include "util.h"
#include <dos.h>
#include "KernQue.h"

Argumenti* arggg = new Argumenti();

Event::Event(IVTNo ivtNo) {

	unsigned int sg;
		unsigned off;
		int flag = 11;

		arggg->ivt = ivtNo;
		arggg->ev = this;



	#ifndef BCC_BLOCK_IGNORE
		off = FP_OFF(arggg);
		sg = FP_SEG(arggg);
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
		EventID = arggg->evID;



}

Event::~Event() {

	arggg->evID = EventID;
	int flag = 14;
	unsigned off,sg;

#ifndef BCC_BLOCK_IGNORE
				off = FP_OFF(arggg);
				sg = FP_SEG(arggg);
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



void Event::wait() {

			arggg->evID = EventID;
			int flag = 12;
			unsigned off,sg;



			#ifndef BCC_BLOCK_IGNORE
				off = FP_OFF(arggg);
				sg = FP_SEG(arggg);
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


void Event::signal() {

		arggg->evID = EventID;
		int flag = 13;
		unsigned off,sg;



		#ifndef BCC_BLOCK_IGNORE
			off = FP_OFF(arggg);
			sg = FP_SEG(arggg);
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
