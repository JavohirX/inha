/*
 * BlinkyC.c
 * Author : hjeong
 */ 


#include <avr/io.h>
#define F_CPU 16000000UL
#include "util/delay.h"
int main(void)
{
	DDRB = 0xFF;           // Set PORTB as output
	uint8_t value = 0xAA;  // Initial pattern

	while (1) {
		PORTB = value;     // Output current value
		value = ~value;    // Flip all bits
		_delay_ms(1000);   // Wait 1 second
	}
}

