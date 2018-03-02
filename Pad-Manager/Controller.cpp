/*
 * Controller.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: Robert
 */

#include "Controller.h"

Controller::Controller(int cnt):padCnt(cnt) , pads(new Pad[cnt]) {


}

Controller::~Controller() {
delete pads;
}

const Pad* Controller::getPads() const {
	return pads;
}
