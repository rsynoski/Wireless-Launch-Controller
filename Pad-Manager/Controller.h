/*
 * Controller.h
 *
 *  Created on: Mar 1, 2018
 *      Author: Robert
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "arduino.h"
#include "XBee.h"
#include "Pad.h"

class Controller {
private:
	int padCnt;             // number of pads supported by controller
	XBeeAddress64 address;  // address of the Pad Controller
	String deviceId;        // XBee device Id i.e. the name of the controller
	long lastMsgTime = 0;       // millis of the last message received
	Pad *pads = NULL;
	char battVoltage[5] = "    ";

	void sendReset();
	void sendPadSelect(int pad);
	void sendPadUnselect(int pad);
	void sendFirePress();
	void sendFireRelease();
public:
	Controller(int cnt, String deviceId, XBeeAddress64& adr);
	Controller(int cnt, XBeeAddress64& adr);
	virtual ~Controller();

	 Pad* getPads() ;
	 String& getDeviceId() ;
	void reset();
	const int selectCnt();
	const XBeeAddress64& getAddress() const;
	long getLastMsgTime() const;
	void setLastMsgTime(long lastMsgTime = 0);
	int getPadCnt() const;
	void setDeviceId(const String& deviceId);
	void togglePadSelection(int pad);
	void processXBeeResponse(Rx64Response& response);
	const char* getBattVoltage() const;
	void firePress();
	void fireRelease();
};

#endif /* CONTROLLER_H_ */
