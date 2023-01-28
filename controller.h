#ifndef CONTROLLER_H
#define CONTROLLER_H

const uint8_t BUTTON_MASK=0b00010100;
const uint8_t SELECT_MASK=0b01000000;

const uint8_t af_max=20;
const uint8_t af_release=af_max/2;

typedef struct {
	uint8_t START_COUNTER;
	uint8_t X_COUNTER;
	uint8_t Y_COUNTER;
	uint8_t Z_COUNTER;

	unsigned UP :1;
	unsigned DOWN :1;
	unsigned LEFT :1;
	unsigned RIGHT :1;
	unsigned A :1;
	unsigned B :1;
	unsigned C :1;
	unsigned START :1;
	unsigned X :1;
	unsigned Y :1;
	unsigned Z :1;
	unsigned MODE :1;

	unsigned TWO_BUTTON :1;
	unsigned THREE_BUTTON :1;
	unsigned A_IS_UP :1;
	unsigned SNACK_TIME :1;
	unsigned SNACK_RETRO :1;
} controller_t;

#endif // CONTROLLER_H
