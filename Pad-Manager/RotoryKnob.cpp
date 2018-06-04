/*
 * RotoryKnob.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: Robert
 */

#include "Arduino.h"
#include "RotoryKnob.h"
#include "Streaming.h"
#include "Ports.h"
#include "Display.h"
#include "Notes.h"

extern Display display;


//#define NOTE_C8  1186
//#define NOTE_A7  3520
//#define NOTE_B7  3951

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
		tone(SPEAKER, NOTE_A6, 50);
		Serial << "CC" << endl;
		if (controllers.current() != NULL) {
			controllers.next();
		}
	}
	if (direction == CCW) {
		tone(SPEAKER, NOTE_B6, 50);
		if (controllers.current() != NULL) {
			controllers.previous();
		}
	}
	pushSwitch->poll();
	if (pushSwitch->pushed()) display.toggleBacklight();
	if (pushSwitch->doubleClick()) Serial << "Knob Click" << endl;
}
