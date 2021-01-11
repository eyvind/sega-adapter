#include <xc.h>

#include "sega-adapter.h"


void setup_pins(void) {
	// Set system clock to 500 kHz
	OSCCON = 0b00111000;

	// Enable weak pull-ups
	OPTION_REG = 0b01111111;

	// RA1,0,7,6 are up,down,left,right outputs to the Atari
	// RB0,1,2,3 are up,down,left,right inputs from the controller
	// RA3 is the select line output to the controller
	// RB4,5 are button inputs from the controller
	// RA2 is the trigger button output to the Atari
	// RB6,7 are button 2,3 outputs to the Atari
	//     NB: configured as inputs until controller is detected
	// RA4,5 are unused

	// Set latches high since output is active low
	LATA = 0b11001111;
	LATB = 0;

	TRISA = 0b00110000;
	// TRISB6,7 are low-impedance inputs until a controller is
	// detected
	TRISB = 0b11111111;

	// set PORTA4 as analog to save power
	ANSELA = 0b00010000;
	ANSELB = 0;
}

controller_t read_controller() {
	static controller_t controller;

	controller.A = controller.X = controller.Y = controller.Z = 1;
	controller.START = controller.MODE = 1;
	controller.THREE_BUTTON = controller.SIX_BUTTON = 0;

	int8_t six_button_next = 0;

	for (int8_t state = 0; state < 8; state++) {
		LATA3 = state % 2;

		switch (state % 2) {
			case 0:
				if (!RB0 && !RB1) {
					controller.SIX_BUTTON = 1;
					six_button_next = 1;
					continue;
				}

				if (!RB2 && !RB3) {
					controller.THREE_BUTTON = 1;
					controller.A = RB4;
					controller.START = RB5;
				}
				break;
			case 1:
				if (six_button_next) {
					controller.X = RB2;
					controller.Y = RB1;
					controller.Z = RB0;
					controller.MODE = RB3;
					six_button_next = 0;

				} else {
					controller.UP = RB0;
					controller.DOWN = RB1;
					controller.LEFT = RB2;
					controller.RIGHT = RB3;
					controller.B = RB4;
					controller.C = RB5;
				}
				break;
		}
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

	if (controller.THREE_BUTTON) {
		if (TRISB7) {
			// three-button controller inserted
			TRISB6 = TRISB7 = 0;
		}

	} else {
		if (!TRISB7) {
			// three-button controller removed
			WPUB6 = TRISB6 = WPUB7 = TRISB7 = 1;
		} else if (TRISB6 && !controller.C) {
			// Non-Megadrive two-button joystick
			TRISB6 = 0;
		}
	}

	return controller;
}

void write_controller(const controller_t *controller) {
	if (controller->A_IS_UP) {
		LATA1 = controller->UP && controller->A;
		LATB7 = 1;
	} else {
		LATA1 = controller->UP;
		LATB7 = controller->A;
	}
	LATA0 = controller->DOWN;
	LATA7 = controller->LEFT;
	LATA6 = controller->RIGHT;
	LATA2 = controller->B && controller->START;
	LATB6 = controller->C;
}

int main(void) {
	static controller_t controller;

	setup_pins();
	while (1) {
		controller = read_controller();
		write_controller(&controller);
		__delay_ms(2);
		CLRWDT();
	}

	return 0;
}
