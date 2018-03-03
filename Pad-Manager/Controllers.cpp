/*
 * Controllers.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: Robert
 */

#include "Controllers.h"

Controllers::Controllers() {
	controllers[0] = new Controller(2, "High_A");
	controllers[1] = new Controller(2, "High_B");
	controllers[2] = new Controller(2, "Low_A");
	controllers[3] = new Controller(2, "Low_B");
	controllerIdx = 0;
}

Controllers::~Controllers() {
	// TODO Auto-generated destructor stub
}

Controller* Controllers::current() {
	return controllers[controllerIdx];
}

Controller* Controllers::next() {
	return controllers[++controllerIdx];
}

Controller* Controllers::previous() {
	return controllers[--controllerIdx];
}
