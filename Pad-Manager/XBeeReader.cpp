/*
 * XBeeReader.cpp
 *
 *  Created on: Mar 12, 2018
 *      Author: Robert
 */

#include "arduino.h"
#include "Controllers.h"
#include "XBeeReader.h"
#include "streaming.h"

#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))



extern XBee xbee;
extern Controllers controllers;

XBeeReader::XBeeReader() {
	// TODO Auto-generated constructor stub

}

XBeeReader::~XBeeReader() {
	// TODO Auto-generated destructor stub
}

void XBeeReader::newController(Rx64Response& dataResponse) {
	Continunity *pkData = (Continunity*)dataResponse.getData();
	int cnt = int (pkData->padCnt & 0x0f);
	controllers.add(new Controller(cnt, dataResponse.getRemoteAddress64()));
	Serial << "New Controller Added,cnt: " << cnt << endl;
	uint8_t cmd[2] = {'N', 'D'};
	AtCommandRequest atCommandRequest = AtCommandRequest(cmd, NULL, 0);
	xbee.send(atCommandRequest);
	return;
}

void XBeeReader::read() {

	Rx64Response dataResponse;
	AtCommandResponse atResponse;
	ZBTxStatusResponse txResponse;
	uint16_t address;


	int length;

	Controller *controller;
	if (xbee.getResponse().isAvailable()) {
//		Serial.println("Got Message");
		XBeeResponse& response = xbee.getResponse();
		if (!response.isError()) {
//			Serial << "APID" << xbee.getResponse().getApiId() << endl;

			switch (xbee.getResponse().getApiId()) {

			case ZB_RX_RESPONSE:
				response.getRx64Response(dataResponse);

				controller = controllers.find(dataResponse.getRemoteAddress64());
				if (controller == NULL) {
					Serial.println("Not Found");
					newController(dataResponse);
				} else {
					controller->processXBeeResponse(dataResponse);
				}
				break;

			case RX_64_RESPONSE:
				break;

			case ZB_TX_STATUS_RESPONSE:
//				response.getZBTxStatusResponse(txResponse);
//				address = txResponse.getFrameId();
//				Serial.print("address: ");
//				Serial.println(address, HEX);
//				controller = controllers.find(address);
//				if (controller != NULL) {
//					controller->processXBeeResponse(txResponse);
//				}
				break;


			case AT_COMMAND_RESPONSE:
//								struct __attribute__((__packed__))  DiscoverResponse {
//								  uint8_t stuff[2];
//								  uint32_t addressMSB;
//								  uint32_t addressLSB;
//								}*N;
	//							DiscoveryResponse *discoveryResponse;
				response.getAtCommandResponse(atResponse);
				//				Serial << "Length :" << atResponse.getFrameDataLength() << endl;
				//				length= atResponse.getValueLength();
				if (atResponse.getCommand()[0] == 'N' && atResponse.getCommand()[1] == 'D') {
					//				for (int i=0; i<length; i++) {
					//					Serial.print(char(atResponse.getValue()[i]));
					//				}
					//				Serial << endl;
					//				for (int i=0; i<length; i++) {
					//					Serial.print(atResponse.getValue()[i], HEX);
					//					Serial.print(' ');
					//				}
					//				Serial.println();
					//		        discoverResponse = (DiscoverResponse*)atResponse.getValue();
					uint32_t addrMSB;
					uint32_t addrLSB;
					char nodeId[21];
					memcpy(&addrMSB, atResponse.getValue()+2, 4);
					addrMSB = SWAP_UINT32(addrMSB);
					memcpy(&addrLSB, atResponse.getValue()+6, 4);
					addrLSB = SWAP_UINT32(addrLSB);
					strncpy(nodeId,  (const char *)atResponse.getValue()+10, 20);
					//				Serial << nodeId << endl;

					//		        Serial.print("Stuff: "); Serial.println(discoverResponse->stuff, HEX);
					//		        Serial.print("MSB: "); Serial.println(discoverResponse->addressMSB, HEX);
					XBeeAddress64 rAddr = XBeeAddress64(addrMSB, addrLSB);
					//		        XBeeAddress64 rAddr = XBeeAddress64(discoveryResponse->addressMSB, discoveryResponse->addressLSB);


					//				Serial.println(addrMSB, HEX);
					//  0013A200 4152E8B8
					//				XBeeAddress64 rAddr = XBeeAddress64((uint32_t)(atResponse.getFrameData()+6), (uint32_t)(atResponse.getFrameData()+10));
					//				Serial << "msb: ";
					//				Serial.println(rAddr.getMsb(), HEX);
					controller = controllers.find(rAddr);
					if ( controller != NULL) {
						controller->setDeviceId(nodeId);
						controller->setLastMsgTime(millis());
						controller->reset();
					}
				} else {
					Serial << "Unknown AT command response" <<endl;
				}
				break;

			default:
				Serial.println("APIID not found");
				break;
			}
			controllers.checkTimeout();
		} else {
			Serial.println("Error");
		}
	}
}
