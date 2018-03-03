/*
 * Controller.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: Robert
 */

#include "Controller.h"

Controller::Controller(int cnt, char name[]):padCnt(cnt) , pads(new Pad[cnt]), deviceId(name) {
	for (int i=0;  i<cnt; i++) {
		pads[i].setNumber(i);
	}
}

Controller::~Controller() {
delete pads;
}

const Pad* Controller::getPads() const {
	return pads;
}

const char* Controller::getDeviceId() const {
	return deviceId;
}
