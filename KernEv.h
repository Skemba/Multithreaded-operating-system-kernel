/*
 * KernEv.h
 *
 *  Created on: Jul 9, 2015
 *      Author: OS1
 */

#ifndef _KERNEV_H_
#define _KERNEV_H_

class Event;
typedef unsigned char IVTNo;


class PCB;
typedef int ID;
class KernelEv {
public:
		static ID posId;
		KernelEv(IVTNo ivtNo,Event* eev);
		~KernelEv();
		int value;
		unsigned char ivtNo;
		PCB* canUse;
		Event* ev;

		ID getId() { return id; }
		void wait();
		void signal();
		void block();
		void deblock();
		int val() const;
		ID id;
};

#endif
