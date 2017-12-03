/*
 * IVTEntry.h
 *
 *  Created on: Jul 9, 2015
 *      Author: OS1
 */


#ifndef _ivtentry_h_
#define _ivtentry_h_

#include "util.h"
#include "EvQue.h"
#include "Event.h"

class ListEv;

class IVTEntry
{
public:

	IVTEntry(IVTNo ivtNo, InterPtr newRoutine);
	~IVTEntry();

	IVTNo ivtNo;
	InterPtr oldRoutine;
	void signalEvents();
	EvQue* events;
	static IVTEntry* entries[256];

};

#endif
