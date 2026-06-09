#include <LPC21xx.H>

#define COUNTER_ENABLE_bm (1<<0)
#define COUNTER_RESET_bm (1<<1)
#define INTERRUPT_ON_MR0_bm (1<<0)
#define RESET_ON_MR0_bm (1<<1)


void InitTimer0(void) {
	T0TCR = COUNTER_ENABLE_bm; // Wlaczamy timer 0 napisac same skutki
}

void WaitOnTimer0(unsigned int uiTime) {
	T0TCR = T0TCR | COUNTER_RESET_bm; // Resetujemy timer 
	T0TCR = T0TCR & ~(COUNTER_RESET_bm); // Konczymy resetowanie sie timera
	while(T0TC < (uiTime*15)) {}
}

void InitTimer0Match0(unsigned int uiDelayTime) {
	T0MR0 = uiDelayTime*15; // Definiujemy czas w us do ktorego czeka T0MR0 na T0TR by wywolac przerwanie
	T0MCR = T0MCR | (INTERRUPT_ON_MR0_bm | RESET_ON_MR0_bm); // Wywolujemy przerwanie i resetujemy licznik gdy T0MR0 i T0TR beda takie same 
	T0TCR = T0TCR | COUNTER_RESET_bm; // Resetujemy timer
	T0TCR = T0TCR & ~(COUNTER_RESET_bm); // Konczymy resetowanie sie timera
	T0TCR = COUNTER_ENABLE_bm; // Wlaczamy timer
}

void WaitOnTimer0Match0(void) {
	while(0 == (T0IR & INTERRUPT_ON_MR0_bm)) {}
	T0IR = INTERRUPT_ON_MR0_bm; // Resetujemy przerwanie timera
}

