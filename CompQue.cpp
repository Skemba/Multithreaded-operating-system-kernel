/*
 * CompQue.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: OS1
 */


#include "CompQue.h"
#include "PCB.h"
#include "util.h"
#include "SCHEDULE.h"

CompQue::CompQue(ID id) {
	head = 0;
	this->id = id;

}

void CompQue::put(PCB* a) {
	if(head==0) {
		head = new Elem(a);
		return;
	}

	Elem* cur = head;
	while(cur->next != 0) cur = cur->next;
	cur->next = new Elem(a);

}

void CompQue::free() {

if(head!= 0) {
	Elem* cur = head;
	while(cur) {
		head = head->next;
		cur->a->state = READY;
		Scheduler::put(cur->a);
		delete cur;
		cur = head;
	}
}


}

ID CompQue::getId() {
	return id;
}
