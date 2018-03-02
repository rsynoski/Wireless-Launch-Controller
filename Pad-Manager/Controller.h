/*
 * Controller.h
 *
 *  Created on: Mar 1, 2018
 *      Author: Robert
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "XBee.h"
#include "Pad.h"

class Controller {
private:
	int padCnt;             // number of pads supported by controller
	XBeeAddress64 address;  // address of the Pad Controller
	char deviceId[];        // XBee device Id i.e. the name of the controller
	long lastMsgTime;       // millis of the last message received
	Pad *pads;
public:
	Controller(int cnt);
	virtual ~Controller();

	const Pad* getPads() const;
};

#endif /* CONTROLLER_H_ */
