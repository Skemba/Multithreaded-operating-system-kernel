/*
 * SleepQue.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: OS1
 */

#include "SleepQue.h"
#include "util.h"
#include <iostream.h>



SleepQue::SleepQue() {
	head=0;
	len=0;
}

SleepQue::~SleepQue() {
	while (head) {
		Elem* old=head;
		head=head->next;
		delete old;
	}
	len=0;
}

void SleepQue::putsleep(PCB* a, Time t){

	if(head==0) {
			head= new Elem(a, t);
			head->a->state = SLEEP;
			len++;
			return;
		}
		Elem* cur=head;
		Elem* prev=0;
		while (cur) {
			if (cur->a==a)
				return;
			cur=cur->next;
		}
		cur = head;
		prev = cur;
		while(cur->t <= t && cur != 0) {
			t -= cur->t;
			prev = cur;
			cur = cur->next;
		}
		if(cur == 0) {
			cur = new Elem(a,t);
			prev->next = cur;
			cur->next = 0;
			len++;
			cur->a->state = SLEEP;
			return;
		}
		if(cur == head) {
			cur = new Elem(a,t);
			cur->next = head;
			cur->next->t = cur->next->t - cur->t;
			head = cur;
			len++;
			cur->a->state = SLEEP;
			return;
		}
		else if(cur != head && cur != 0){
			cur = new Elem(a,t);
			cur->t = t;
			cur->next = prev->next;
			prev->next = cur;
			len++;
			cur->a->state = SLEEP;
			return;
		}
}


void SleepQue::check() {

	if(head == 0) return;
	Elem* cur = head;
	Elem *cur1 = head;
	int p;
	cur->t--;
	if(cur->t == 0) {
		while(cur->t == 0 && cur != 0) {
			cur1 = cur->next;
			cur->a->state = READY;
			len--;
			Scheduler::put(cur->a);
			remove(cur->a);

			cur = cur1;
		}
		if(cur == 0) head = 0;
	}

}

void SleepQue::remove(PCB* a) {
	if(head==0) return;
	Elem* cur=head;
	Elem* prev=0;
	while (cur && cur->a!=a ) {
		prev=cur;
		cur=cur->next;
	}
	if(cur==0) return;
	if(cur==head) {
		head = cur->next;
		delete cur;
		return;
	}
	if(prev==0)
		head=0;
	else
		prev->next=cur->next;
	delete cur;
	len--;
}


int SleepQue::length() const{
	return len;
}

void SleepQue::removeAll() {
	Elem* cur = head;
	Elem* cur1 = head;

	while(cur != 0) {
				cur1 = cur->next;
				cur->a->state = READY;
				len--;
				Scheduler::put(cur->a);
				remove(cur->a);

				cur = cur1;
			}
			if(cur == 0) head = 0;

}

