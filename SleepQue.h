/*
 * SleepQue.h
 *
 *  Created on: Jul 8, 2015
 *      Author: OS1
 */

#ifndef SLEEPQUE_H_
#define SLEEPQUE_H_

#include "SCHEDULE.H"
#include "Thread.h"
#include "PCB.h"

class SleepQue {

public:
	struct Elem {
					Time t;
					PCB* a;
					Elem* next;
					Elem () {
						a = 0; next = 0; t = 0;
					}
					Elem(PCB* aa, Time tt) {
						t = tt;
						a = aa;
						next = 0;
					}
				};

	SleepQue();
	~SleepQue();

	void check();
	Elem* head;

	int len;
	void putsleep(PCB* a, Time t);
	void remove(PCB* a);
	int length() const;
	void removeAll();
};

#endif /* SLEEPQUE_H_ */
