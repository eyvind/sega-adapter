#ifndef SEGA_ADAPTER_H
#define SEGA_ADAPTER_H

#define _XTAL_FREQ 500000 	// 500 kHz

#pragma config FOSC = INTOSC	// Oscillator Selection
#pragma config WDTE = ON	// Watchdog Timer Enable
#pragma config PWRTE = OFF	// Power-up Timer Enable
#pragma config MCLRE = OFF	// MCLR Pin Function Select
#pragma config CP = OFF		// Flash Program Memory Code Protection
#pragma config CPD = OFF	// Data Memory Code Protection
#pragma config BOREN = ON	// Brown-out Reset Enable
#pragma config CLKOUTEN = OFF	// Clock Out Enable
#pragma config IESO = ON	// Internal/External Switchover
#pragma config FCMEN = ON	// Fail-Safe Clock Monitor Enable
#pragma config WRT = OFF	// Flash Memory Self-Write Protection
#pragma config PLLEN = OFF	// PLL Enable
#pragma config STVREN = ON	// Stack Overflow/Underflow Reset Enable
#pragma config BORV = LO	// Brown-out Reset Voltage Selection
#pragma config LVP = OFF	// Low-Voltage Programming Enable

const uint8_t BUTTON_MASK=0b00010100;
const uint8_t SELECT_MASK=0b01000000;

typedef struct {
	uint8_t START_COUNTER;

	unsigned UP :1;
	unsigned DOWN :1;
	unsigned LEFT :1;
	unsigned RIGHT :1;
	unsigned A :1;
	unsigned B :1;
	unsigned C :1;
	unsigned START :1;

	unsigned TWO_BUTTON :1;
	unsigned THREE_BUTTON :1;
	unsigned A_IS_UP :1;
} controller_t;

#endif // SEGA_ADAPTER_H
