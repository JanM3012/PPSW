#include "led.h"
#include "keyboard.h"
#include "timer.h"

//git test
int main() {
	LedInit();
	KeyboardInit();
	InitTimer0Match0(250000);
	while(1){
		WaitOnTimer0Match0();
		LedStepLeft();
		}
}
