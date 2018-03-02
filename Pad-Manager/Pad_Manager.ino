

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
#include "ports.h"


#define DEBUG

Arm armingSwitch{ARMING_SWITCH, ARMING_LED};
Fire fire{FIRE_BUTTON};
RotoryKnob rotoryKnob{ENCODER_A, ENCODER_B, ENCODER_PUSH};
Selector X[NUM_SEL] = {
		{ SEL0_SWITCH, SEL0_SELLED, SEL0_CONTLED },
		{ SEL1_SWITCH, SEL1_SELLED, SEL1_CONTLED },
		{ SEL2_SWITCH, SEL2_SELLED, SEL2_CONTLED },
		{ SEL3_SWITCH, SEL3_SELLED, SEL3_CONTLED }
		};
XBee xbee;
Metro d(1000);

Controller *controllers[2];
struct {
unsigned short cc : 2;
}currentControllerIdx;


//The setup function is called once at startup of the sketch
void setup() {
	Serial.begin(9600);
	delay(2000);
#ifdef DEBGUG
	Serial.println("Setup");
#endif

	Serial1.begin(38400);
	xbee.begin(Serial1);
	controllers[0] = new Controller(2);
	controllers[1] = new Controller(2);
	currentControllerIdx.cc = 0;



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
	X[0].poll();
	X[0].showContinuity("22.0");
	X[1].poll();


//	if (d.check()){
//		Serial << X[0].getToggle() << endl;
//		Serial << X[1].getToggle() << endl;
//	}
//	delay(10);

}
