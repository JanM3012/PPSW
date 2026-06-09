#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMS) {

	int iCounter;
	
	for(iCounter = 0; iCounter < 5460*iDelayInMS; iCounter++) {}
}

enum eLedState {IDLE,MOVERIGHT};
enum eLedState eState = IDLE;

int main() {
	
	unsigned char ucStepCounter = 0;
	
	LedInit();
	KeyboardInit();
	while(1){
		switch(eState) {
			case IDLE:
				if (eReadKeyboard() == BUTTON_0) {
					eState = MOVERIGHT;
				}
				else {
					eState = IDLE;
				}
				break;
			case MOVERIGHT:
				if (ucStepCounter < 3) {
					LedStepRight();
					ucStepCounter++;
					eState = MOVERIGHT;
				}
				else {
					eState = IDLE;
					ucStepCounter = 0;
				}
				break;
		}
		Delay(250);
	}
}
