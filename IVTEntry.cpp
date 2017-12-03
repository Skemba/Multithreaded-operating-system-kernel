/*
 * IVTEntry.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: OS1
 */



#include "IVTEntry.h"
#include "Queues.h"
#include "thread.h"
#include "kernev.h"
#include <dos.h>
#include "KernQue.h"

IVTEntry* IVTEntry::entries[256];

IVTEntry::IVTEntry(unsigned char ivtNo, InterPtr newRoutine) {

	this->ivtNo = ivtNo;
#ifndef BCC_BLOCK_IGNORE
	oldRoutine = getvect(ivtNo);
	setvect(ivtNo, newRoutine);
#endif
	events = new EvQue();
	IVTEntry::entries[ivtNo] = this;

}

IVTEntry::~IVTEntry() {
	oldRoutine();
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo, oldRoutine);
#endif
	delete events;
	IVTEntry::entries[ivtNo] = 0;
}

void IVTEntry::signalEvents() {
	for (EvQue::Elem* cur = this->events->head; cur; cur = cur->next)
		cur->kerev->signal();

}
