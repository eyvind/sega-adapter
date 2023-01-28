#include "sega-adapter.h"

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
		LATB6 = (state % 2) == 1;
	}

	if (three_button && !controller.THREE_BUTTON) {
		controller.TWO_BUTTON = 0;
	}

	if (!controller.C) {
		controller.TWO_BUTTON = 1;
	}

	if (!controller.START) {
		if (!controller.MODE && !(controller.Z && controller.X && controller.C)) {
			controller.SNACK_TIME = controller.Z;	// inverted
			controller.SNACK_RETRO = controller.X;	// inverted
			controller.MODE = controller.START =
				controller.Z = controller.X = controller.C = 1;
			controller.START_COUNTER = 0;
		}

		if (!controller.SNACK_TIME) {
			if (controller.START_COUNTER < 200) {
				++controller.START_COUNTER;
			} else if (controller.START_COUNTER == 200) {
				controller.A_IS_UP = !controller.A_IS_UP;
				++controller.START_COUNTER;
			} else {
				controller.START = 1;
			}
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
