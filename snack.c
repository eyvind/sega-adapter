#include "sega-adapter.h"

void write_snack(const controller_t controller) {
	TRISAbits_t trisa = TRISAbits;

	trisa.TRISA7 = 1;
	if (!controller.START) {
		trisa.TRISA0 = 1;
		trisa.TRISA1 = 1;
	} else if (!controller.MODE) {
		trisa.TRISA0 = 1;
		trisa.TRISA1 = 0;
	} else if (!controller.X) {
		trisa.TRISA0 = 0;
		trisa.TRISA1 = 1;
	} else if (!controller.Y) {
		trisa.TRISA0 = 0;
		trisa.TRISA1 = 0;
	} else {
		trisa.TRISA7 = 0;
		trisa.TRISA0 = !controller.A;
		trisa.TRISA1 = !controller.B;
	}
	trisa.TRISA6 = !controller.C;
	trisa.TRISA3 = !controller.Z;
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
