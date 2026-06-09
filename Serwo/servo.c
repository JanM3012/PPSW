#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"

#define DETECTOR_bm (1<<10)

void DetectorInit(void) {
	IO0DIR = IO0DIR & ~DETECTOR_bm;
}
enum DetectorState {INACTIVE, ACTIVE};
enum DetectorState eReadDetector(void) {
	if (0==(IO0PIN & DETECTOR_bm)) {
		return ACTIVE;
	}
	else {
		return INACTIVE;
	}
}

enum ServoState {CALLIB,OFFSET ,IDLE, IN_PROGRESS};
struct Servo {
	enum ServoState eState; 
	unsigned int uiCurrentPosition; 
	unsigned int uiDesiredPosition;
}; 

struct Servo sServo;

void Automat(void) {
	switch(sServo.eState) {
		case CALLIB:
			if (eReadDetector() == ACTIVE) {
				sServo.eState = OFFSET;
				sServo.uiCurrentPosition = 0;
				sServo.uiDesiredPosition = 0;
			}
			else {
				LedStepLeft();
				sServo.eState = CALLIB;
			}
			break;
		case OFFSET:
			if(sServo.uiCurrentPosition < 12) {
				sServo.eState = OFFSET;
				LedStepLeft();
				sServo.uiCurrentPosition++;
			}
			else {
				sServo.eState = IDLE;
				sServo.uiCurrentPosition = 0;
				sServo.uiDesiredPosition = 0;
			}
			break;
		case IDLE:
			if (sServo.uiCurrentPosition == sServo.uiDesiredPosition) {
				sServo.eState = IDLE;
			}
			else {
				sServo.eState = IN_PROGRESS;
			}
			break;
		case IN_PROGRESS:
			if (sServo.uiCurrentPosition > sServo.uiDesiredPosition) {
				LedStepRight();
				sServo.uiCurrentPosition--;
			}
			else if (sServo.uiCurrentPosition < sServo.uiDesiredPosition) {
				LedStepLeft();
				sServo.uiCurrentPosition++;
			}
			else {
				sServo.eState = IDLE;
			}
	}
}

void ServoInit(unsigned int uiServoFrequency) {
	LedInit();
	DetectorInit();
	Timer0Interrupts_Init((1000000/uiServoFrequency), &Automat);
	sServo.eState = CALLIB;
}

void ServoCallib(void) {
	sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition) {
	sServo.uiDesiredPosition = uiPosition;
}
