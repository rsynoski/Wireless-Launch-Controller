/*
 * Controller.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: Robert
 */

#include "Controller.h"
#include "streaming.h"

extern XBee xbee;

Controller::Controller(int cnt, String name, XBeeAddress64& adr):padCnt(cnt), pads(new Pad[cnt]), deviceId(name), address(adr) {
	for (int i=0;  i<cnt; i++) {
		pads[i].setNumber(i);
	}
}

Controller::Controller(int cnt, XBeeAddress64& adr):padCnt(cnt), pads(new Pad[cnt]), address(adr) {
	deviceId = String("Temp");
	for (int i=0;  i<cnt; i++) {
			pads[i].setNumber(i);
		}
}


Controller::~Controller() {
	Serial.println("Controller Destr");
delete [] pads;
Serial.println("Controller Destr 2");

}

 Pad* Controller::getPads()  {
	return pads;
}

 String& Controller::getDeviceId()  {
	return deviceId;
}

void Controller::reset() {
	for (int i=0; i<padCnt; i++) {
		pads[i].setSelectState(false);
//		pads[i].setContinunity("9999");
	}
	sendReset();
}

const XBeeAddress64& Controller::getAddress() const {
	return address;
}

long Controller::getLastMsgTime() const {
	return lastMsgTime;
}

void Controller::setLastMsgTime(long lastMsgTime) {
	this->lastMsgTime = lastMsgTime;
}

void Controller::sendReset() {
	ZBTxRequest txRequest;
	char data[1] = {'X'};
	txRequest.setAddress64(address);
	txRequest.setPayload((uint8_t*)data);
	txRequest.setPayloadLength(sizeof(data));
	xbee.send(txRequest);
}

void Controller::setDeviceId(const String& deviceId) {
	this->deviceId = deviceId;
}

int Controller::getPadCnt() const {
	return padCnt;
}

void Controller::sendPadSelect(int i) {
	ZBTxRequest txRequest;
	char data[2] = {'S', ' '};
	txRequest.setAddress64(address);
	byte x = byte(i);
	data[1] = 0x30 ^ x;
	txRequest.setPayload((uint8_t*)data);
	txRequest.setPayloadLength(sizeof(data));
	xbee.send(txRequest);
}

void Controller::sendPadUnselect(int i) {
	ZBTxRequest txRequest;
	char data[2] = {'U', ' '};
	txRequest.setAddress64(address);
	byte x = byte(i);
	data[1] = 0x30 ^ x;
	txRequest.setPayload((uint8_t*)data);
	txRequest.setPayloadLength(sizeof(data));
	xbee.send(txRequest);
}

void Controller::togglePadSelection(int pad) {
	getPads()[pad].setSelectState(!getPads()[pad].isSelectState());
	if (getPads()[pad].isSelectState()) {
		sendPadSelect(pad);
	} else {
		sendPadUnselect(pad);
	}
}

void Controller::sendFirePress() {
	ZBTxRequest txRequest;
	char data[1] = {'F'};
		txRequest.setAddress64(address);
		txRequest.setPayload((uint8_t*)data);
		txRequest.setPayloadLength(sizeof(data));
		xbee.send(txRequest);
}

void Controller::sendFireRelease() {
	ZBTxRequest txRequest;
	char data[1] = {'R'};
		txRequest.setAddress64(address);
		txRequest.setPayload((uint8_t*)data);
		txRequest.setPayloadLength(sizeof(data));
		xbee.send(txRequest);
}

const char* Controller::getBattVoltage() const {
	return battVoltage;
}

void Controller::processXBeeResponse(Rx64Response& response) {
	struct __attribute__((__packed__))  DiscoverResponse {
		char fill;
		char cmd;
		char number;
		char voltage[4];
		char continunity[8][4];
	}*N;
//	Serial.println("RxResponse");
	unsigned char *data;
	data = response.getData();
	N = (struct DiscoverResponse*)data;
	if (N->cmd == 'c') {
		memcpy(battVoltage, N->voltage, sizeof(N->voltage));
		for (int i=0; i<padCnt; i++) {
			pads[i].setContinunity(N->continunity[i]);
		}
	}
	setLastMsgTime(millis());
}

void Controller::firePress() {
	bool selected = false;
	for (int i=0; i<padCnt; i++) {
		selected |= pads[i].isSelectState();
	}
	if (selected) {
		sendFirePress();
	}
}

const int Controller::selectCnt() {
	int cnt = 0;
	for (int i=0; i<padCnt; i++) {
		cnt += pads[i].isSelectState()? 1:0;
//		pads[i].setContinunity("9999");
	}
	return cnt;
}

void Controller::fireRelease() {
	bool selected = false;
	for (int i=0; i<padCnt; i++) {
		selected |= pads[i].isSelectState();
	}
	if (selected) {
		sendFireRelease();
	}
}
