/*
 * Pad.h
 *
 *  Created on: Mar 1, 2018
 *      Author: Robert
 */

#ifndef PAD_H_
#define PAD_H_

class Pad {
private:
char continunity[5] = "00.0";
bool selectState = false;
public:
	Pad();
	virtual ~Pad();
};

#endif /* PAD_H_ */
