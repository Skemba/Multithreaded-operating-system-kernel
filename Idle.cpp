/*
 * Idle.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: OS1
 */

#include "Idle.h"
#include "KernQue.h"
#include "iostream.h"

Idle::Idle() : Thread(1024)
{

}

void Idle::run()
{
	while (1);

}
