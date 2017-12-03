/*
 * Semaphor.h
 *
 *  Created on: Jul 6, 2015
 *      Author: OS1
 */


#ifndef _semaphor_h_
#define _semaphor_h_

#include "Thread.h"

class KernelSem;
class Semaphore {

public:

	Semaphore (int init=1);
	virtual ~Semaphore ();
	virtual void wait ();
	virtual void signal();
	int val () const; // Returns the current value of the semaphore


private:

	ID SemID;

};
#endif
