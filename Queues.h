/*
 * Queues.h
 *
 *  Created on: Jul 5, 2015
 *      Author: OS1
 */

#ifndef _QUEUES_H_
#define _QUEUES_H_

#include <iostream.h>
#include <stdlib.h>
#include "Thread.h"

template<class A>


class Queues {

public:

	struct Elem {
				Time t;
				A* a;
				Elem* next;
				Elem () {
					a = 0; next = 0; t = 0;
				}
				Elem(A* aa, Time tt) {
					t = tt;
					a = aa;
					next = 0;
				}
			};

	struct Elem* head;


	Queues();
	~Queues();

	A* getById(ID tempID);

	void put(A* a, Time t);
	A* getFirst();
	void remove(A* a);
	void check();
	void putsleep(A* a, Time t);


};

template<class A>
Queues<A>::Queues() {
	head=0;
}

template<class A>
Queues<A>::~Queues() {
	while (head) {
		Elem* old=head;
		head=head->next;
		delete old;
	}
}

template<class A>
void Queues<A>::put(A* a, Time t) {
	if(head==0) {
		head= new Elem(a, t);
		return;
	}
	Elem* cur=head;
	Elem* prev=0;
	while (cur) {
		if (cur->a==a)
			return;
		prev=cur;
		cur=cur->next;
	}
	prev->next= new Elem(a, t);
}

template<class A>
A* Queues<A>:: getFirst() {
	if(head==0) return 0;
	Elem* cur=head;
	A* a;
	head=head->next;
	a=cur->a;
	delete cur;
	return a;
}

template<class A>
A* Queues<A>::getById(ID tempID) {
	if(head==0) return 0;
	Elem* cur=head;
	while (cur && (cur->a->getId())!=tempID)
		cur=cur->next;
	if(cur==0) return 0;
	return cur->a;

}

template<class A>
void Queues<A>:: remove(A* a) {
	if(head==0) return;
	Elem* cur=head;
	Elem* prev=0;
	while (cur && cur->a!=a ) {
		prev=cur;
		cur=cur->next;
	}
	if(cur==0) return;
	if(prev==0)
		head=0;
	else
		prev->next=cur->next;
	delete cur;
}






#endif
