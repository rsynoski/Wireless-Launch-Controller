/*
 * ControllerList.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: Robert
 */

#include "Arduino.h"
#include "ControllerList.h"
//#include <bits/stdc++.h>

ControllerList::ControllerList() {
	currentItem = NULL;
	start = NULL;

}

ControllerList::~ControllerList() {
	// TODO Auto-generated destructor stub
}

void ControllerList::add(Controller* controller) {
	ListItem *insertPoint;

	// empty list
	if (currentItem == NULL) {
		currentItem = new ListItem(controller);
		start = currentItem;
		currentItem->previous = currentItem;
		currentItem->next = currentItem;
	} else {
		if (find(controller->getAddress()) == NULL) {
			insertPoint = start;
			while (insertPoint->controller->getDeviceId() < controller->getDeviceId()){
				if (insertPoint->next == start) break;
				insertPoint = insertPoint->next;
			}
			insertPoint = insertPoint->previous;
			ListItem *newItem = new ListItem(controller);

			newItem->previous = insertPoint;
			newItem->next = insertPoint->next;

			insertPoint->next->previous = newItem;
			insertPoint->next = newItem;

			// establish new start
			insertPoint = start;
			while (insertPoint->previous->controller->getDeviceId() < insertPoint->controller->getDeviceId()) {
				insertPoint = insertPoint->previous;
			}
			start = insertPoint;
	//		cout << "Start: " << start->controller->getName() <<endl;
		}
	}
}

Controller* ControllerList::next() {
	Controller *ret = NULL;
	if (currentItem != NULL) {
		currentItem = currentItem->next;
		ret = currentItem->controller;
	}
	return ret;
}

void ControllerList::remove() {
	ListItem * save = currentItem;
	//	Serial.println((long unsigned int)save, HEX);
	if (currentItem != NULL) {
		Serial.println("here 1");
		if (currentItem->next == currentItem) {
			Serial.println("here 2");
			currentItem = NULL;
			start = NULL;
		} else {
			Serial.println("here 3");
			if (start == currentItem) {
				start = currentItem->next;
			}

			currentItem->previous->next = currentItem->next;
			currentItem->next->previous = currentItem->previous;

			currentItem = currentItem->next;
		}
		Serial.println("here 4");

		delete save;
		Serial.println("here 5");
	}
}

Controller* ControllerList::previous() {
	Controller *ret = NULL;
	if (currentItem != NULL) {
		currentItem = currentItem->previous;
		ret = currentItem->controller;
	}
	return ret;
}

Controller* ControllerList::find(const String name) {

	ListItem *i=NULL;

	if (start != NULL) {
		i = start;
		do {
			if ( i->controller->getDeviceId() == name) {
				return i->controller;
				break;
			}

			i = i->next;
		} while (i != start);

	}
		return NULL;
}

Controller* ControllerList::find(const XBeeAddress64 adr) {

	ListItem *i=NULL;

	if (start != NULL) {
		i = start;
		do {
			if ( i->controller->getAddress() == adr) {
				return i->controller;
				break;
			}

			i = i->next;
		} while (i != start);

	}
		return NULL;
}



ListItem* ControllerList::select(const XBeeAddress64 adr) {
	ListItem *i=NULL;

	if (start != NULL) {
		i = start;
		do {
			if ( i->controller->getAddress() == adr) {
				currentItem = i;
				return i;
				break;
			}

			i = i->next;
		} while (i != start);

	}
		return NULL;
}
