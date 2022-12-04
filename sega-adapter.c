#include "sega-adapter.h"

void setup_pins(void) {
	OSCCON = OSCCON_16MHZ;

	// Enable weak pull-ups
	OPTION_REG = 0b01111111;

	// PORTA is connected to the computer, PORTB to the controller
	// RA1,0,7,6 are up,down,left,right outputs to the computer
	// RB0,1,2,3 are up,down,left,right inputs from the controller
	// RB6 is the select line output to the controller
	// RB7,5 are button inputs from the controller
	// RA3 is the trigger button output to the computer
	// RA4,2 are button 2,3 outputs to the computer
	// /RA5 selects C64 mode
	// RB4 is unused

	LATA = BUTTON_MASK;
	LATB = SELECT_MASK;

	TRISA = 0b11111111;
	TRISB = (uint8_t) ~SELECT_MASK;

	ANSELA = 0;
	// set PORTB4 as analog to save power
	ANSELB = 0b00010000;
}

int main(void) {
	static controller_t controller;

	setup_pins();
	while (1) {
		controller = read_controller();
		if (controller.SNACK_TIME) {
			for (uint8_t i = 0; i < 4; ++i) {
				write_snack(controller);
				slow_delay(500);
			}
		} else {
			write_joy2b(controller);
			slow_delay(2000);
		}
		CLRWDT();
	}

	return 0;
}
