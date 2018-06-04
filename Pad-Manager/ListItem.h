/*
 * ListItem.h
 *
 *  Created on: Mar 7, 2018
 *      Author: Robert
 */

#ifndef LISTITEM_H_
#define LISTITEM_H_

#include "Controller.h"
//#include "ControllerList.h"

class ListItem {
private:
	ListItem *previous;
	ListItem *next;
	Controller *controller;
public:
	ListItem(Controller *controller);
	virtual ~ListItem();
	 Controller* getController() ;
	 ListItem * nextItem();

	friend class ControllerList;
};

#endif /* LISTITEM_H_ */
