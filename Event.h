/*
 * Event.h
 *
 *  Created on: Jul 9, 2015
 *      Author: OS1
 */

// File: event.h
#ifndef _event_h_
#define _event_h_

#include "IVTEntry.h"

typedef unsigned char IVTNo;
class KernelEv;

class Event {

public:
 Event (IVTNo ivtNo);
 ~Event ();
 void wait ();

protected:
 friend class KernelEv;
 void signal(); // can call KernelEv

private:
 unsigned int EventID;
};

#define PREPAREENTRY(ivtno, routineflag)\
	void interrupt newRoutine##ivtno(...); \
	IVTEntry ivtentry##ivtno(ivtno, newRoutine##ivtno); \
	void interrupt newRoutine##ivtno(...)\
{\
	ivtentry##ivtno.signalEvents(); \
if (routineflag)\
	ivtentry##ivtno.oldRoutine(); \
}

#endif
