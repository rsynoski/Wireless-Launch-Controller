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
	const char* getContinunity() const;
	void setContinunity(char * val);
	int getNumber() const;
	void setNumber(int number);
	bool isSelectState() const;
	void setSelectState(bool selectState);
};

#endif /* PAD_H_ */
