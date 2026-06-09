#include <LPC21xx.H>

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

#define S0_bm (1<<4)
#define S1_bm (1<<6)
#define S2_bm (1<<5)
#define S3_bm (1<<7)

void Delay(int iDelayInMS) {

	int iCounter;
	
	for(iCounter = 0; iCounter < 5460*iDelayInMS; iCounter++) {}
}

void LedInit(void) {
	
	IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks) {
	
	IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	switch (ucLedIndeks) {
		case 0:
			IO1SET = LED0_bm;
			break;
		case 1:
			IO1SET = LED1_bm;
			break;
		case 2:
			IO1SET = LED2_bm;
			break;
		case 3:
			IO1SET = LED3_bm;
			break;
		default:
			break;
	}
}

enum eStepDirection {LEFT, RIGHT};
void LedStep(enum eStepDirection eDirection) {

	static unsigned char ucStepNumber = 0;
	
	switch (eDirection) {
		case LEFT:
			ucStepNumber++;
			break;
		case RIGHT:
			ucStepNumber--;
			break;
	}
	LedOn(ucStepNumber%4);
}

void LedStepLeft(void) {
	LedStep(LEFT);
}

void LedStepRight(void) {
	LedStep(RIGHT);
}

void KeyboardInit(void) {
	IO0DIR = IO0DIR & (~(S0_bm | S1_bm | S2_bm | S3_bm));

}

enum ButtonState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
enum ButtonState eReadKeyboard(void)  {
	if (0==(IO0PIN & S0_bm)) {
		return BUTTON_0;
	} 
	else if (0==(IO0PIN & S1_bm)) {
		return BUTTON_1;
	}	
	else if (0==(IO0PIN & S2_bm)) {
		return BUTTON_2;
	}	
	else if (0==(IO0PIN & S3_bm)) {
		return BUTTON_3;
	} 
	else { 
		return RELEASED;
	}
}
	
int main() {
	LedInit();
	KeyboardInit();
	while(1){
		switch (eReadKeyboard()) {
			case BUTTON_1:
				LedStep(RIGHT);
				break;
			case BUTTON_2:
				LedStep(LEFT);
				break;
			default:
				break;
		}
		Delay(250);
	}

}
