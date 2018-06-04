/*
 * Controllers.h
 *
 *  Created on: Mar 3, 2018
 *      Author: Robert
 */

#ifndef CONTROLLERS_H_
#define CONTROLLERS_H_

#include "ControllerList.h"


class Controllers {
private:
	ControllerList controllers;
//	unsigned short controllerIdx : 2;
public:
	Controllers();
	virtual ~Controllers();

	 void add(Controller *controller);
	Controller* current();
	Controller* next();
	Controller* previous();
	void clearControllers();
	const int selectCnt();
	 Controller* find(String deviceId);
	 Controller* find(XBeeAddress64 adr);
	 ListItem * select(XBeeAddress64 adr);
	 void firePress();
	 void fireRelease();
	 void checkTimeout();

};

#endif /* CONTROLLERS_H_ */
