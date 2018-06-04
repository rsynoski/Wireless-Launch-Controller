

#include "Arduino.h"
#include "usb_serial.h"
#include "Selector.h"
#include "XBee.h"
#include "metro.h"
#include "streaming.h"
#include "time.h"
#include <openGLCD.h>
//#include "avdweb_switch.h"
#include "XBeeReader.h"
#include "Arm.h"
#include "Fire.h"
#include "RotoryKnob.h"
#include "Controller.h"
#include "Controllers.h"
#include "Display.h"
#include "ports.h"
#include "Notes.h"



// TODO: if no controller, manager can't be armed. Disarm if already armed.
// TODO: add signal strength bar graph
// TODO: Add total select count

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
XBeeReader xBeeReader;
Metro d(1000);
Metro displayMetro(10);
Display display;




//The setup function is called once at startup of the sketch
void setup() {
//	pinMode(11, OUTPUT);
//	digitalWrite(11, LOW);

	// Clear LED Ports
	digitalWrite(ARMING_LED, LOW);
	digitalWrite(SEL0_SELLED, LOW);
	digitalWrite(SEL0_CONTLED, LOW);
	digitalWrite(SEL1_SELLED, LOW);
	digitalWrite(SEL1_CONTLED, LOW);
	digitalWrite(SEL2_SELLED, LOW);
	digitalWrite(SEL2_CONTLED, LOW);
	digitalWrite(SEL3_SELLED, LOW);
	digitalWrite(SEL3_CONTLED, LOW);

	// Setup XBee Serial
	Serial.begin(9600);
	Serial1.begin(115200);
	xbee.begin(Serial1);

	// Init LCD
	GLCD.Init();

	GLCD.OnBacklight();
	GLCD.SelectFont(TimesNewRoman13);
	 GLCD.print("Pad Manager Setup");
#ifdef DEBUG
	Serial.println("Setup");
#endif
//Serial.println("new test");
//Pad *padx = new Pad;
//Serial.println("new test2");
//delete padx;
//Serial.println("new test3");
LEDTest();
delay(1000);
//	 do
//	  {
//		// wait on USB serial port to be ready but timout out after 10 seconds
//		if(millis() > 10000) // millis starts at 0 after reset
//			break;
//	  } while(!Serial);

//	pinMode(30, OUTPUT);
//	digitalWrite(30, HIGH);
//	delay(5000);
//	digitalWrite(30, LOW);

	tone(SPEAKER, NOTE_C3, 100);


//	XBeeAddress64 adr = XBeeAddress64(0, 1);
//	controllers.add(new Controller(2,String("High"), adr));
//	adr.setLsb(2);
//	controllers.add(new Controller(2,String("Low"), adr));
//	char *c = "1.2";
//controllers.current()->getPads()[1].setContinunity(c);
GLCD.ClearScreen();
GLCD.OffBacklight();


}

// The loop function is called in an endless loop
void loop() {
#ifdef DEBUG
	{
		static bool loopStart = true;
		if (loopStart) {
			Serial << "Loop Start" << endl;
			loopStart = false;
		}
	}
#endif
	xbee.readPacket();
	xBeeReader.read();
	controllers.checkTimeout();

	rotoryKnob.poll();
	armingSwitch.poll();
	fire.poll();
	if (controllers.current() != NULL) {
		for (int i=0; i<NUM_SELECTORS; i++){
			selectors[i].poll();
		}
	} else {
		for (int i=0; i<NUM_SELECTORS; i++){
			selectors[i].clear();
		}
	}

	if (displayMetro.check()) display.poll();
	//	if (d.check()){
	//		Serial << X[0].getToggle() << endl;
	//		Serial << X[1].getToggle() << endl;
	//	}
	//	delay(10);


}

#define TESTDELAY 200
void LEDTest () {

	// Blink Arm twice
	digitalWrite(ARMING_LED, HIGH);
	delay(TESTDELAY);
	digitalWrite(ARMING_LED, LOW);
	delay(TESTDELAY);
	digitalWrite(ARMING_LED, HIGH);
	delay(TESTDELAY);
	digitalWrite(ARMING_LED, LOW);
	delay(TESTDELAY);


	//loop through all the Selectors LEDs
	delay(TESTDELAY);
	digitalWrite(SEL0_SELLED, HIGH);
	delay(TESTDELAY);
	digitalWrite(SEL1_SELLED, HIGH);
	delay(TESTDELAY);
	digitalWrite(SEL0_SELLED, LOW);
	digitalWrite(SEL2_SELLED, HIGH);
	delay(TESTDELAY);
	digitalWrite(SEL1_SELLED, LOW);
	digitalWrite(SEL3_SELLED, HIGH);
	delay(TESTDELAY);
	digitalWrite(SEL2_SELLED, LOW);
	digitalWrite(SEL3_CONTLED, HIGH);
	delay(TESTDELAY);
	digitalWrite(SEL3_SELLED, LOW);
	digitalWrite(SEL2_CONTLED, HIGH);
	delay(TESTDELAY);
	digitalWrite(SEL3_CONTLED, LOW);
	digitalWrite(SEL1_CONTLED, HIGH);
	delay(TESTDELAY);
	digitalWrite(SEL2_CONTLED, LOW);
	digitalWrite(SEL0_CONTLED, HIGH);
	delay(TESTDELAY);
	digitalWrite(SEL1_CONTLED, LOW);
	delay(TESTDELAY);
	digitalWrite(SEL0_CONTLED, LOW);
}
