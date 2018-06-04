/*
 * ControllerList.h
 *
 *  Created on: Mar 7, 2018
 *      Author: Robert
 */

#ifndef CONTROLLERLIST_H_
#define CONTROLLERLIST_H_



#include "arduino.h"
#include "ListItem.h"
#include "XBee.h"


class ControllerList {
private:
	ListItem *currentItem;
	ListItem *start;

public:
	ControllerList();
	virtual ~ControllerList();

	 void add(Controller *controller);
	 void remove(); // remove current item
	 Controller *next();
	 Controller *previous();
	 Controller* find(String deviceId);
	 Controller* find(XBeeAddress64 adr);
	 ListItem * select(XBeeAddress64 adr);

	 ListItem* getCurrentItem()  {
		return currentItem;
	}

	 ListItem*& getStart()  {
		return start;
	}
};

#endif /* CONTROLLERLIST_H_ */
