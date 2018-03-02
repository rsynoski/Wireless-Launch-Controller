/*
 * DirectionalEncoder.h
 *
 *  Created on: Feb 28, 2018
 *      Author: Robert
 */

#ifndef DIRECTIONALENCODER_H_
#define DIRECTIONALENCODER_H_

#define INPUT_PULLUPD
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

#define CC 1
#define CCW -1

class DirectionalEncoder: public Encoder {
private:
	int32_t previousPosition = 0;
public:
	DirectionalEncoder(uint8_t pin1, uint8_t pin2);
	virtual ~DirectionalEncoder();
	int32_t read(void);


};

#endif /* DIRECTIONALENCODER_H_ */
