

#include "Arduino.h"
#include "Selector.h"
#include "XBee.h"
#include "metro.h"
#include "streaming.h"
//#include "avdweb_switch.h"
#include "Arm.h"
#include "Fire.h"
#include "RotoryKnob.h"
#include "Controller.h"
#include "Controllers.h"
#include "ports.h"


#define DEBUG

Arm armingSwitch{ARMING_SWITCH, ARMING_LED};
Fire fire{FIRE_BUTTON};
RotoryKnob rotoryKnob{ENCODER_A, ENCODER_B, ENCODER_PUSH};
Selector selectors[NUM_SEL] = {
		{ 0, SEL0_SWITCH, SEL0_SELLED, SEL0_CONTLED },
		{ 1, SEL1_SWITCH, SEL1_SELLED, SEL1_CONTLED },
		{ 2, SEL2_SWITCH, SEL2_SELLED, SEL2_CONTLED },
		{ 3, SEL3_SWITCH, SEL3_SELLED, SEL3_CONTLED }
		};
Controllers controllers;
XBee xbee;
Metro d(1000);




//The setup function is called once at startup of the sketch
void setup() {
	Serial.begin(9600);
	delay(2000);
#ifdef DEBGUG
	Serial.println("Setup");
#endif

	Serial1.begin(38400);
	xbee.begin(Serial1);




}

// The loop function is called in an endless loop
void loop() {
#if def DEBUG
	{
		static bool loopStart = true;
		if (loopStart) {
			Serial << "Loop Start" << endl;
			loopStart = false;
		}
	}
#endif

	rotoryKnob.poll();
	armingSwitch.poll();
	fire.poll();
	selectors[0].poll();
	selectors[0].showContinuity("2.0");
	selectors[1].poll();
	selectors[1].showContinuity("0.2");


//	if (d.check()){
//		Serial << X[0].getToggle() << endl;
//		Serial << X[1].getToggle() << endl;
//	}
//	delay(10);

}
