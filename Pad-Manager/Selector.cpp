/*
 * Selector.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: Robert
 */

#include "Selector.h"
#include "Arm.h"
#include "Streaming.h"
#include "Controllers.h"
#include "Notes.h"
#include "Ports.h"

extern Arm armingSwitch;
extern Controllers controllers;

//Selector::Selector() {
//	// TODO Auto-generated constructor stub
//
//}

Selector::Selector(int num, byte a, int b, int c) : togglePort(a), selLED(b), contLED(c), number(num){
	toggle = new Switch(togglePort);
	pinMode(selLED, OUTPUT);
	pinMode(contLED, OUTPUT);
};

Selector::~Selector() {
	delete toggle;
}

bool Selector::getToggle() {
	return toggle->on();
}

void Selector::poll(){
	toggle->poll();
	showSelection();
	showContinuity();

}

bool Selector::isSelected(){
	return digitalRead(selLED) == HIGH;
}

void Selector::showSelection() {
	if (armingSwitch.isArmed()){
		if (toggle->pushed()) {
			tone(SPEAKER, NOTE_C5, 50);
			Serial << "Pushed" << endl;
			Serial << controllers.current()->getPads()[number].isSelectState() << endl;
			controllers.current()->togglePadSelection(number);
		}
		digitalWrite(selLED, controllers.current()->getPads()[number].isSelectState() ? HIGH : LOW);
	}else {
		controllers.current()->getPads()[number].setSelectState(false);
		digitalWrite(selLED, LOW);
	}

}
void Selector::showContinuity() {
	const char *value = controllers.current()->getPads()[number].getContinunity();
	float val = String(value).toFloat();
	if (val > NO_CONT) {
		digitalWrite(contLED, LOW);
	} else if (val > SHORTED) {
		digitalWrite(contLED, HIGH);
	} else {
		if (blink.check()){
			digitalWrite(contLED, digitalRead(contLED)== HIGH ? LOW : HIGH);
		}
	}
}

void Selector::clear() {
	digitalWrite(contLED, LOW);
}
