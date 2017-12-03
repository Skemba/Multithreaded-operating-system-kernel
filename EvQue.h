/*
 * EvQue.h
 *
 *  Created on: Jul 9, 2015
 *      Author: OS1
 */

#ifndef EVQUE_H_
#define EVQUE_H_

#include "KernEv.h"


class EvQue {

public:
	struct Elem {
		KernelEv* kerev;
		Elem* next;
		Elem () {
			kerev = 0; next = 0;
		}
		Elem(KernelEv* kkerev) {
			kerev=kkerev;
			next=0;
		}
	};

	Elem* head;

	EvQue();
	~EvQue();

	void put(KernelEv* kkerev);
	void remove(KernelEv*);

};


#endif /* EVQUE_H_ */
