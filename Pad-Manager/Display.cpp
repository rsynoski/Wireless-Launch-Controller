/*
 * Display.cpp
 *
 *  Created on: Mar 20, 2018
 *      Author: Robert
 */

#include "Time.h"
#include "Arduino.h"
#include "Display.h"
#include "openGLCD.h"
#include "ARM.h"

#include "Controllers.h"
#include "Streaming.h"

extern Arm armingSwitch;
extern Controllers controllers;

Display::Display() {
	// TODO Auto-generated constructor stub

}

void Display::poll() {

	// TODO: display total number of pads selected

	const char armed[] = "Armed";
	const char noController[] = "No Controller";
	const char volt[]= "v";
	static int idWidth =1;

	GLCD.GotoXY(145, 0);
	GLCD.SelectFont(TimesNewRoman16_bold);
	int armedWidth = GLCD.StringWidth(armed);
//	GLCD.GotoXY(x, y)
//	GLCD.FillRect(0, 35, 10	, 10, BLACK);
	if (armingSwitch.isArmed()) {
		GLCD.print(armed);
	} else {

		GLCD.SetPixels(145, 0, armedWidth, GLCD.CharHeight('A'), 0);
		//		GLCD.print("            ");
	}
	GLCD.GotoXY(0, 10);
	GLCD.SelectFont(Cooper26);
	if (controllers.current() != NULL) {
		int newWidth = GLCD.StringWidth(controllers.current()->getDeviceId());
		GLCD.SetPixels(0+newWidth, 10, 0+idWidth, GLCD.CharHeight('A')+10, 0);
		GLCD.print(controllers.current()->getDeviceId());
		idWidth = newWidth;
		//		idWidth =  GLCD.StringWidth(controllers.current()->getDeviceId());
		GLCD.SelectFont(System5x7);

		int cnt = controllers.current()->getPadCnt();
		// TODO: Clear for less then 4 pads
		// TODO: Add Selected pad count
		for (int i=0; i< 4; i++) {
			if (i<cnt){
			GLCD.GotoXY(i*30+10, 37);
			GLCD.PrintNumber(i+1);
//			GLCD.Printf("%d", i+1);
			if(controllers.current()->getPads()[i].isSelectState()) {
			GLCD.FillRect(i*30, 46, 25, 7, BLACK);
			} else {
				GLCD.DrawRect(i*30, 46, 25, 7, BLACK);
				GLCD.FillRect(i*30+1, 47, 23, 5, WHITE);
			}
			GLCD.GotoXY(i*30, 56);
			GLCD.Printf("%s", controllers.current()->getPads()[i].getContinunity());
			} else {
				GLCD.SetPixels(i*30, 37, (i+1)*30, 63, WHITE);
			}
		}
		GLCD.GotoXY(50, 0);
		GLCD.print(controllers.current()->getBattVoltage());
		GLCD.print(volt);

		GLCD.SelectFont(lcdnums14x24);
		GLCD.GotoXY(160, 30);
		GLCD.PrintNumber(controllers.selectCnt());
	} else {

		int noControllerWidth = GLCD.StringWidth(noController);
		GLCD.SetPixels(50+noControllerWidth, 10, 50+idWidth, GLCD.CharHeight('A')+10, 0);
		GLCD.print(noController);
		idWidth =  noControllerWidth;
		GLCD.SetPixels(0, 37, 191, 63, WHITE);


	}


	GLCD.GotoXY(0, 0);
	GLCD.SelectFont(Callibri10);
	GLCD.Printf("%02d:%02d:%02d", hourFormat12(), minute(),  second() );

}

Display::~Display() {
	// TODO Auto-generated destructor stub
}

void Display::backlightOn() {
	GLCD.OnBacklight();
}

void Display::backlightOff() {
	GLCD.OffBacklight();
}

void Display::toggleBacklight() {
	if(blState){
		backlightOff();
	} else {
		backlightOn();
	}
	blState = !blState;
}
