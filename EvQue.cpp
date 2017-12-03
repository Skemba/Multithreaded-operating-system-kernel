/*
 * EvQue.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: OS1
 */

#include <stdlib.h>
#include "EvQue.h"


class KernelEv;


EvQue:: EvQue() {
	head=NULL;
}

EvQue:: ~EvQue() {
	Elem* prev;
	while (head) {
		prev=head;
		head=head->next;
		delete prev;
	}
}

void EvQue:: put(KernelEv* kerev) {
	if(head==0) {
		head= new Elem(kerev);
		return;
	}
	Elem* cur=head;
	Elem* prev=0;
	while (cur) {
		if (cur->kerev==kerev)
			return;
		prev=cur;
		cur=cur->next;
	}
	prev->next= new Elem(kerev);
}

void EvQue:: remove(KernelEv* kernev) {
	if(head==0) return;
	Elem* prev=0;
	Elem* cur=head;
	while (cur) {
		if(cur->kerev==kernev) break;
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



