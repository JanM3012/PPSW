#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMS) {

	int iCounter;
	
	for(iCounter = 0; iCounter < 5460*iDelayInMS; iCounter++) {}
}

enum eLedState {MOVELEFT, MOVERIGHT};
enum eLedState eState = MOVELEFT;

int main() {
	
	unsigned char ucStepCounter = 0;
	
	LedInit();
	KeyboardInit();
	while(1){
		switch(eState) {
			case MOVELEFT:
				if (ucStepCounter < 3) {
					LedStepLeft();
					ucStepCounter++;
					eState = MOVELEFT;
				}
				else {
					eState = MOVERIGHT;
					LedStepRight();
					ucStepCounter = 1;
				}
				break;
			case MOVERIGHT:
				if (ucStepCounter < 3) {
					LedStepRight();
					ucStepCounter++;
					eState = MOVERIGHT;
				}
				else {
					eState = MOVELEFT;
					LedStepLeft();
					ucStepCounter = 1;
				}
				break;
		}
		Delay(250);
	}
}
