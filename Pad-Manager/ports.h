/*
 * ports.h
 *
 *  Created on: Feb 24, 2018
 *      Author: Robert
 */

#ifndef PORTS_H_
#define PORTS_H_

#ifdef DEV
#define NUM_SEL 4

#define SEL0_SWITCH  4
#define SEL0_SELLED  5
#define SEL0_CONTLED  6

#define SEL1_SWITCH  24
#define SEL1_SELLED  25
#define SEL1_CONTLED  26

#define SEL2_SWITCH 32
#define SEL2_SELLED 31
#define SEL2_CONTLED 30

#define SEL3_SWITCH 29
#define SEL3_SELLED 28
#define SEL3_CONTLED 27

#define ARMING_SWITCH  2
#define ARMING_LED    3

#define FIRE_BUTTON 33

#define ENCODER_A  37
#define ENCODER_B  36
#define ENCODER_PUSH 35

#define SPEAKER 14

#define NUM_SELECTORS 2
#else
#define NUM_SEL 4

#define SEL0_SWITCH  4
#define SEL0_SELLED  6
#define SEL0_CONTLED 5

#define SEL1_SWITCH  24
#define SEL1_SELLED  26
#define SEL1_CONTLED  25

#define SEL2_SWITCH 15
#define SEL2_SELLED 13
#define SEL2_CONTLED 14

#define SEL3_SWITCH 27
#define SEL3_SELLED 29
#define SEL3_CONTLED 28

#define ARMING_SWITCH  2
#define ARMING_LED    3

#define FIRE_BUTTON 33

#define ENCODER_A  36
#define ENCODER_B  37
#define ENCODER_PUSH 35

#define SPEAKER 38

#define NUM_SELECTORS 4
#endif

#endif /* PORTS_H_ */
