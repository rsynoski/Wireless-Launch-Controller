/*
 * DirectionalEncoder.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: Robert
 */


#include "DirectionalEncoder.h"
#include "streaming.h"

DirectionalEncoder::DirectionalEncoder(uint8_t pin1, uint8_t pin2):Encoder(pin1, pin2){
	write(0);
}

DirectionalEncoder::~DirectionalEncoder() {
	// TODO Auto-generated destructor stub
}

int32_t DirectionalEncoder::read(){
	int32_t position;

	position = Encoder::read();

	 if (position >> 2  > 0) {
//			Serial << "Pos:" << position << "  Pre:" << previousPosition <<endl;
//		previousPosition = position;
		write(0);
		return position >> 2;
	}
	else if (position / 4  < 0) {
//		Serial << "Pos:" << position << "  Pre:" << previousPosition <<endl;
//		previousPosition = position;
		write(0);
		return (position / 4);
	}
	return 0;

}

