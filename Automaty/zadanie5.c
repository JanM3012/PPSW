#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMS) {

	int iCounter;
	
	for(iCounter = 0; iCounter < 5460*iDelayInMS; iCounter++) {}
}

enum eLedState {IDLE,MOVERIGHT};
enum eLedState eState = MOVERIGHT;

int main() {
	LedInit();
	KeyboardInit();
	while(1){
		switch(eState) {
			case MOVERIGHT:
				if (eReadKeyboard() == BUTTON_0) {
					eState = IDLE;
				}
				else {
					LedStepRight();
					eState = MOVERIGHT;
				}
				break;
			case IDLE:
				if (eReadKeyboard() == BUTTON_1) {
					eState = MOVERIGHT;
				}
				else {
					eState = IDLE;
				}
				break;
		}
		Delay(250);
	}
}
