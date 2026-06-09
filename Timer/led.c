#include <LPC21xx.H>
#include "led.h"

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

void LedInit(void) {
	
	IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks) {
	
	IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	IO1SET = (LED0_bm<<ucLedIndeks);
}

void LedStep(enum eStepDirection eDirection) {

	static unsigned int uiStepNumber = 0;
	
	switch (eDirection) {
		case LEFT:
			uiStepNumber++;
			break;
		case RIGHT:
			uiStepNumber--;
			break;
	}
	LedOn(uiStepNumber%4);
}

void LedStepLeft(void) {
	LedStep(LEFT);
}

void LedStepRight(void) {
	LedStep(RIGHT);
}
