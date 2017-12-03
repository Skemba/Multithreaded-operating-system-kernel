/*
 * CompQue.h
 *
 *  Created on: Jul 8, 2015
 *      Author: OS1
 */

#ifndef COMPQUE_H_
#define COMPQUE_H_

#include "Thread.h"

class CompQue {

public:

	struct Elem {

		PCB* a;
		Elem* next;

		Elem(PCB* aa) {
			a = aa; next = 0;
		}

	};

	CompQue(ID id);

	ID getId();

	Elem* head;

	void put(PCB* a);
	void free();

	ID id;

};



#endif /* COMPQUE_H_ */
