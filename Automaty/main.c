#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMS) {

	int iCounter;
	
	for(iCounter = 0; iCounter < 5460*iDelayInMS; iCounter++) {}
}

enum eLedState {MOVELEFT,MOVERIGHT,IDLE};
enum eLedState eState = IDLE;

int main() {
	LedInit();
	KeyboardInit();
	while(1){
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
		Delay(100);
	}
}
