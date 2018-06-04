/*
 * Pad.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: Robert
 */

#include "Pad.h"
#include "arduino.h"

Pad::Pad() {
	selectState = false;

}

Pad::~Pad() {
	Serial.println("Pad Destr");

	// TODO Auto-generated destructor stub
}

const char* Pad::getContinunity() const {
	return continunity;
}

void Pad::setContinunity(char * val) {
	strncpy(continunity, val, 4);
}

int Pad::getNumber() const {
	return number;
}

void Pad::setNumber(int number) {
	this->number = number;
}

bool Pad::isSelectState() const {
	return selectState;
}

void Pad::setSelectState(bool selectState) {
//	Serial.println(selectState);
	this->selectState = selectState;
}

void Pad::refresh() {
}



