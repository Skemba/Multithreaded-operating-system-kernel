/*
 * Thread.h
 *
 *  Created on: May 29, 2015
 *      Author: OS1
 */


// File: thread.h
#ifndef _thread_h_
#define _thread_h_

typedef unsigned long StackSize;

const StackSize defaultStackSize = 4096;

typedef unsigned int Time; // time, x 55ms

const Time defaultTimeSlice = 1; // default = 2*55ms

typedef int ID;

class PCB; // Kernel's implementation of a user's thread

class Thread {
public:
	void start();
	void waitToComplete();
	virtual ~Thread();
	static void sleep(Time timeToSleep);

protected:

	friend class PCB;
	Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run();

private:
	static void wrapper(Thread* running);
	ID id;
	};

void dispatch ();

#endif
