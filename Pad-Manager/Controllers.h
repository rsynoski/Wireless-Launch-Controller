/*
 * Controllers.h
 *
 *  Created on: Mar 3, 2018
 *      Author: Robert
 */

#ifndef CONTROLLERS_H_
#define CONTROLLERS_H_

#include "Controller.h"

class Controllers {
private:
	Controller *controllers[4];
	unsigned short controllerIdx : 2;
public:
	Controllers();
	virtual ~Controllers();

	Controller* current();
	Controller* next();
	Controller* previous();
};

#endif /* CONTROLLERS_H_ */
