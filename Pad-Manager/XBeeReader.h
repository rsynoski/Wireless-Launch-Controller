/*
 * XBeeReader.h
 *
 *  Created on: Mar 12, 2018
 *      Author: Robert
 */

#ifndef XBEEREADER_H_
#define XBEEREADER_H_

#include "Xbee.h"

typedef  struct {
	uint8_t option;
	char cmd;
	char padCnt;
	char batt[4];
	char continunity[16][4];
} Continunity;


class XBeeReader {
private:
	void newController(Rx64Response& dataResponse);
public:
	XBeeReader();
	virtual ~XBeeReader();
	void read();
};

#endif /* XBEEREADER_H_ */
