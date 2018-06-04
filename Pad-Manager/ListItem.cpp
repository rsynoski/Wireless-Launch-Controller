/*
 * ListItem.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: Robert
 */

#include "ListItem.h"

ListItem::ListItem(Controller *controller): controller(controller){
next=NULL;
previous=NULL;

}

ListItem::~ListItem() {
	delete controller;
}

 Controller* ListItem::getController()  {
	return controller;
}

ListItem* ListItem::nextItem() {
	return next;
}
