#ifndef SEGA_ADAPTER_H
#define SEGA_ADAPTER_H

#include <xc.h>
#include "controller.h"

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

const uint8_t OSCCON_16MHZ=0b01111000;
const uint8_t OSCCON_31KHZ=0b00000000;
const unsigned long CLOCK_FACTOR=516;	// 16MHz/31kHz
#define _XTAL_FREQ 31000	// Use n*CLOCK_FACTOR at 16MHz
#define slow_delay(us) OSCCON = OSCCON_31KHZ; __delay_us(us); OSCCON = OSCCON_16MHZ

controller_t read_controller(void);
void write_joy2b(const controller_t controller);
void write_snack(const controller_t controller);

#endif // SEGA_ADAPTER_H
