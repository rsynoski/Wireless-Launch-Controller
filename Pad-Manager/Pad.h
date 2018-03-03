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
int number = 0;
char continunity[5] = "00.0";
bool selectState = false;
public:
	Pad();
	virtual ~Pad();

	void refresh();

	int getNumber() const {
		return number;
	}

	void setNumber(int number = 0) {
		this->number = number;
	}
};

#endif /* PAD_H_ */
