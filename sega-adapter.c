#include <xc.h>

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
	TRISB = ~SELECT_MASK;

	ANSELA = 0;
	// set PORTB4 as analog to save power
	ANSELB = 0b00010000;
}

controller_t read_controller() {
	static controller_t controller;
	int8_t three_button = controller.THREE_BUTTON;
	int8_t six_button_next = 0;

	controller.A = controller.X = controller.Y = controller.Z = 1;
	controller.MODE = controller.START = 1;
	controller.THREE_BUTTON = 0;

	for (int8_t state = 0; state < 8; state++) {
		switch (state) {
			case 0:
				controller.UP = RB0;
				controller.DOWN = RB1;
				controller.LEFT = RB2;
				controller.RIGHT = RB3;
				controller.B = RB7;
				controller.C = RB5;
				break;
			case 1:
				if (!RB2 && !RB3) {
					controller.TWO_BUTTON = 1;
					controller.THREE_BUTTON = 1;
					controller.A = RB7;
					controller.START = RB5;
				}
				break;
			case 5:
				if (!RB0 && !RB1 && !RB2 && !RB3) {
					six_button_next = 1;
				}
				break;
			case 6:
				if (six_button_next) {
					six_button_next = 0;

					controller.Z = RB0;
					controller.Y = RB1;
					controller.X = RB2;
					controller.MODE = RB3;
				}
				break;
		}
		LATB6 = state % 2;
	}

	if (three_button && !controller.THREE_BUTTON) {
		controller.TWO_BUTTON = 0;
	}

	if (!controller.C) {
		controller.TWO_BUTTON = 1;
	}

	if (!controller.START) {
		if (controller.START_COUNTER < 200) {
			++controller.START_COUNTER;
		} else if (controller.START_COUNTER == 200) {
			controller.A_IS_UP = !controller.A_IS_UP;
			++controller.START_COUNTER;
		} else {
			controller.START = 1;
		}
	} else {
		controller.START_COUNTER = 0;
	}

	if (++controller.X_COUNTER > af_max || controller.X) {
		controller.X_COUNTER = 0;
	}
	if (++controller.Y_COUNTER > af_max || controller.Y) {
		controller.Y_COUNTER = 0;
	}
	if (++controller.Z_COUNTER > af_max || controller.Z) {
		controller.Z_COUNTER = 0;
	}

	return controller;
}

void write_controller(const controller_t controller) {
	int8_t c64 = !RA5;
	int8_t up, button_1, button_2, button_3;
	TRISAbits_t trisa = TRISAbits;
	LATAbits_t lata = LATAbits;

	button_1 = controller.B && controller.START;
	if (!controller.Y) {
		button_1 &= (controller.Y_COUNTER >= af_release);
	}

	button_2 = controller.C;
	if (!controller.Z) {
		button_2 &= (controller.Z_COUNTER >= af_release);
	}

	up = controller.UP;
	if (controller.A_IS_UP) {
		up &= controller.A;
		button_3 = 1;
	} else {
		button_3 = controller.A;
	}
	if (!controller.X) {
		button_3 &= (controller.X_COUNTER >= af_release);
	}

	trisa.TRISA1 = up;
	trisa.TRISA0 = controller.DOWN;
	trisa.TRISA7 = controller.LEFT;
	trisa.TRISA6 = controller.RIGHT;
	trisa.TRISA3 = button_1;

	if (c64) {
		// Buttons are active high.  The 8-bit Commodores don't
		// appreciate having them pulled low, so we toggle the
		// tristate between input and high output.

		lata.LATA4 = lata.LATA2 = 1;
		trisa.TRISA4 = button_2;
		trisa.TRISA2 = button_3;

	} else {
		// Buttons are active low.  Toggling the tristate
		// between input and output works on an Atari, but the
		// Amiga expects buttons to be pulled low.

		lata.LATA4 = button_2;
		trisa.TRISA4 = !controller.TWO_BUTTON;

		lata.LATA2 = button_3;
		trisa.TRISA2 = !controller.THREE_BUTTON;
	}

	LATAbits = lata;
	TRISAbits = trisa;
}

int main(void) {
	static controller_t controller;

	setup_pins();
	while (1) {
		controller = read_controller();
		write_controller(controller);
		// Clock down to save power while idle
		OSCCON = OSCCON_31KHZ;
		__delay_ms(2);
		OSCCON = OSCCON_16MHZ;
		CLRWDT();
	}

	return 0;
}
