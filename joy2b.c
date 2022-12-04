#include "sega-adapter.h"

void write_joy2b(const controller_t controller) {
	int8_t c64 = !RA5;
	uint8_t up, button_1, button_2, button_3;
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
