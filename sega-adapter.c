#include <xc.h>

#include "sega-adapter.h"


void setup_pins(void) {
	// Set system clock to 500 kHz
	OSCCON = 0b00111000;

	// Enable weak pull-ups
	OPTION_REG = 0b01111111;

	// PORTA is connected to the Atari, PORTB to the controller
	// RA1,0,7,6 are up,down,left,right outputs to the Atari
	// RB0,1,2,3 are up,down,left,right inputs from the controller
	// RB6 is the select line output to the controller
	// RB7,5 are button inputs from the controller
	// RA3 is the trigger button output to the Atari
	// RA4,2 are button 2,3 outputs to the Atari
	// /RA5 selects C64 mode
	// RB4 is unused

	LATA = BUTTON_MASK;
	LATB = SELECT_MASK;

	TRISA = 0b11111111;
	TRISB = ~SELECT_MASK;

	ANSELA = 0;
	// set PORTB4 as analog to save power
	ANSELB = 0b00010000;
}

controller_t read_controller() {
	static controller_t controller;
	int8_t three_button = controller.THREE_BUTTON;
	int8_t six_button_next = 0;

	controller.A = controller.START = 1;
	controller.THREE_BUTTON = 0;

	for (int8_t state = 0; state < 8; state++) {
		LATB6 = state % 2;

		switch (state % 2) {
			case 0:
				if (!RB0 && !RB1) {
					six_button_next = 1;
					continue;
				}

				if (!RB2 && !RB3) {
					controller.TWO_BUTTON = 1;
					controller.THREE_BUTTON = 1;
					controller.A = RB7;
					controller.START = RB5;
				}
				break;
			case 1:
				if (six_button_next) {
					six_button_next = 0;

				} else {
					controller.UP = RB0;
					controller.DOWN = RB1;
					controller.LEFT = RB2;
					controller.RIGHT = RB3;
					controller.B = RB7;
					controller.C = RB5;
				}
				break;
		}
	}

	if (three_button && !controller.THREE_BUTTON) {
		controller.TWO_BUTTON = 0;
	}

	if (!controller.C) {
		controller.TWO_BUTTON = 1;
	}

	if (!controller.START) {
		if (controller.START_COUNTER < 128) {
			++controller.START_COUNTER;
		} else if (controller.START_COUNTER == 128) {
			controller.A_IS_UP = !controller.A_IS_UP;
			++controller.START_COUNTER;
		} else {
			controller.START = 1;
		}
	} else {
		controller.START_COUNTER = 0;
	}

	return controller;
}

void write_controller(const controller_t controller) {
	int8_t c64 = !RA5;
	int8_t button_3;
	TRISAbits_t trisa = TRISAbits;

	if (controller.A_IS_UP) {
		trisa.TRISA1 = controller.UP && controller.A;
		button_3 = 1;
	} else {
		trisa.TRISA1 = controller.UP;
		button_3 = controller.A;
	}
	trisa.TRISA0 = controller.DOWN;
	trisa.TRISA7 = controller.LEFT;
	trisa.TRISA6 = controller.RIGHT;
	trisa.TRISA3 = controller.B && controller.START;

	if (c64) {
		trisa.TRISA4 = controller.C;
		trisa.TRISA2 = button_3;

	} else {
		// In Atari mode, buttons are low both when active and
		// when not connected.
		trisa.TRISA4 = !(controller.TWO_BUTTON && controller.C);
		trisa.TRISA2 = !(controller.THREE_BUTTON && button_3);
	}

	TRISAbits = trisa;
}

int main(void) {
	static controller_t controller;

	setup_pins();
	while (1) {
		controller = read_controller();
		write_controller(controller);
		__delay_ms(2);
		CLRWDT();
	}

	return 0;
}
