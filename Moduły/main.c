#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMS) {

	int iCounter;
	
	for(iCounter = 0; iCounter < 5460*iDelayInMS; iCounter++) {}
}

	
int main() {
	LedInit();
	KeyboardInit();
	while(1){
		switch (eReadKeyboard()) {
			case BUTTON_1:
				LedStepRight();
				break;
			case BUTTON_2:
				LedStepLeft();
				break;
			default:
				break;
		}
		Delay(250);
	}

}
