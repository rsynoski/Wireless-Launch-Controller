/*
 * Controllers.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: Robert
 */

#include "Controllers.h"

Controllers::Controllers() {
//	controller[0] = new Controller(2, "High_A");
//	controller[1] = new Controller(2, "High_B");
//	controller[2] = new Controller(2, "Low_A");
//	controller[3] = new Controller(2, "Low_B");
//	controllerIdx = 0;
}

Controllers::~Controllers() {
	// TODO Auto-generated destructor stub
}

Controller* Controllers::current() {
	Controller* ret = NULL;
	if (controllers.getCurrentItem() != NULL) {
		ret =  controllers.getCurrentItem()->getController();
	}
	return ret;
}

Controller* Controllers::next() {
	return controllers.next();
}

Controller* Controllers::previous() {
	return controllers.previous();
}

void Controllers::add(Controller* controller) {
	controller->setLastMsgTime(millis());
	controllers.add(controller);
}

void Controllers::clearControllers() {
	if (controllers.getStart() != NULL) {
		ListItem *i = controllers.getStart();
		do {
			i->getController()->reset();
			i = i->nextItem();
		} while (i != controllers.getStart());

//	for (Controller  *i= controllers.getStart(); i !=; i++){
//		controller[i]->clear();
//	}
	}
}
const int Controllers::selectCnt(){
	int cnt=0;
	if (controllers.getStart() != NULL) {
		ListItem *i = controllers.getStart();
		do {
			cnt += i->getController()->selectCnt();
			i = i->nextItem();
		} while (i != controllers.getStart());
	}
	return cnt;

}

Controller* Controllers::find(String deviceId) {
	return controllers.find(deviceId);
}

Controller* Controllers::find(XBeeAddress64 adr) {
	return controllers.find(adr);
}

ListItem* Controllers::select(XBeeAddress64 adr) {
	return controllers.select(adr);
}

void Controllers::firePress() {
	if (controllers.getStart() != NULL) {
		ListItem *i = controllers.getStart();
		do {
			i->getController()->firePress();
			i = i->nextItem();
		} while (i != controllers.getStart());
	}
}

void Controllers::fireRelease() {
	if (controllers.getStart() != NULL) {
		ListItem *i = controllers.getStart();
		do {
			i->getController()->fireRelease();
			i = i->nextItem();
		} while (i != controllers.getStart());
	}
}

void Controllers::checkTimeout() {
	long time = millis();
	XBeeAddress64 current = this->current()->getAddress();
	if (controllers.getStart() != NULL) {
		ListItem *i = controllers.getStart();
		do {
			if (time - i->getController()->getLastMsgTime() > 20000){
				Serial.println("timeout");
				if (controllers.select(i->getController()->getAddress()) != NULL){
//					Serial.println("selected");
					this->current()->reset();
					controllers.remove();
					Serial.println("removed");

					controllers.select(current);
				}
				break;
			}
//			Serial.println("here");
			i = i->nextItem();
		} while (i != controllers.getStart());
//		Serial.println("Done Remove");
	}
//	Serial.println((long unsigned int)this->current(), HEX);
//	Serial.println((long unsigned int)controllers.getStart()  , HEX);
}
