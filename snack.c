#include "sega-adapter.h"

void write_snack(const controller_t controller) {
	TRISAbits_t trisa = TRISAbits;

	uint8_t snes_a, snes_b, snes_y, snes_l, snes_r;
	uint8_t snes_x = controller.Y;
	if (controller.SNACK_RETRO) {
		snes_a = controller.B;
		snes_b = controller.A;
		snes_y = controller.X;
		snes_l = controller.Z;
		snes_r = controller.C;
	} else {
		snes_a = controller.C;
		snes_b = controller.B;
		snes_y = controller.A;
		snes_l = controller.X;
		snes_r = controller.Z;
	}

	trisa.TRISA7 = 1;
	if (!controller.START) {
		trisa.TRISA0 = 1;
		trisa.TRISA1 = 1;
	} else if (!controller.MODE) {
		trisa.TRISA0 = 1;
		trisa.TRISA1 = 0;
	} else if (!snes_y) {
		trisa.TRISA0 = 0;
		trisa.TRISA1 = 1;
	} else if (!snes_x) {
		trisa.TRISA0 = 0;
		trisa.TRISA1 = 0;
	} else {
		trisa.TRISA7 = 0;
		trisa.TRISA0 = !snes_b;
		trisa.TRISA1 = !snes_a;
	}
	trisa.TRISA3 = !snes_l;
	trisa.TRISA6 = !snes_r;
	trisa.TRISA4 = !controller.RIGHT;
	trisa.TRISA2 = !controller.DOWN;

	LATA = BUTTON_MASK;
	TRISAbits = trisa;

	__delay_us(8 * CLOCK_FACTOR);
	// Stop charging the pot capacitors if controls are centered
	trisa.TRISA4 = controller.LEFT;
	trisa.TRISA2 = controller.UP;

	TRISAbits = trisa;
}
