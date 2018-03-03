/*
 * Selector.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: Robert
 */

#include "Selector.h"
#include "Arm.h"
#include "Streaming.h"

extern Arm armingSwitch;

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
	if (armingSwitch.isArmed()){
		if (toggle->pushed()) {
			Serial << "cnt: " << cnt++ << endl;
			digitalWrite(selLED, digitalRead(selLED) == HIGH ? LOW : HIGH);
		}
	}else {
		digitalWrite(selLED, LOW);
	}
}

bool Selector::isSelected(){
	return digitalRead(selLED) == HIGH;
}

void Selector::showContinuity(char value[]) {
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

