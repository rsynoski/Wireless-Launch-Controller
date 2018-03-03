/*
 * RotoryKnob.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: Robert
 */

#include "RotoryKnob.h"
#include "Streaming.h"

RotoryKnob::RotoryKnob(uint8_t pinA, uint8_t pinB, uint8_t push) {
	encoder = new DirectionalEncoder(pinA, pinB);
	pushSwitch = new Switch(push);

}

RotoryKnob::~RotoryKnob() {
	delete encoder;
	delete pushSwitch;
}

void RotoryKnob::poll() {
	int direction;
	 direction = encoder->read();
	if (direction == CC) {
		controllers.next();
		Serial << controllers.current()->getDeviceId() << endl;
	}
	if (direction == CCW) {
		controllers.previous();
		Serial << controllers.current()->getDeviceId() << endl;
	}
	pushSwitch->poll();
	if (pushSwitch->pushed()) Serial << "Knob Pressed" << endl;
	if (pushSwitch->doubleClick()) Serial << "Knob Click" << endl;
}
