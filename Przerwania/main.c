#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"

void Automat(void) {
	enum eLedState {MOVELEFT,MOVERIGHT,IDLE};
	static enum eLedState eState = IDLE;
	switch(eState) {
			case MOVELEFT:
				if (eReadKeyboard() == BUTTON_1) {
					eState = IDLE;
				}
				else {
					LedStepLeft();
					eState = MOVELEFT;
				}
				break;
			case MOVERIGHT:
				if (eReadKeyboard() == BUTTON_1) {
					eState = IDLE;
				}
				else {
					LedStepRight();
					eState = MOVERIGHT;
				}
				break;
			case IDLE:
				if (eReadKeyboard() == BUTTON_0) {
					eState = MOVELEFT;
				}
				else if (eReadKeyboard() == BUTTON_2) {
					eState = MOVERIGHT;
				}
				else {
					eState = IDLE;
				}
				break;
		}

}


int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	KeyboardInit();
	Timer0Interrupts_Init(20000, &Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}
