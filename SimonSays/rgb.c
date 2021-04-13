/*
 * rgb.c
 *
 * Created: 12-4-2021 15:56:05
 *  Author: timoj
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include "rgb.h"

void rgbWait(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

//Init the rgb leds
void rgbLedInit(void)
{
	OCR1A = 0;				// R: default, min power
	OCR1B = 0;				// G: default, min power
	OCR1C = 0;				// B: default, min power
	TCCR1A = 0b10101001;	// compare output OC1A, OC1B, OC1C
	TCCR1B = 0b00001011;	// fast PWM 8 bit, prescaler=64, RUN
	
	DDRB = 0xFF; // Set port B as output
	DDRA = 0b00001111; // Set port A0 till A4 as output
	PORTA = 0b00001111; // Set port A0 till A4 on
}

//Set a specific color to the leds
void setLedColor(unsigned char r, unsigned char g, unsigned char b)
{
	OCR1A = r;
	OCR1B = g;
	OCR1C = b;
}

// Set a specific led on
void setLedOn(unsigned char ledValue)
{
	PORTA &= ~(1<<ledValue);
}

// Set a specific led off
void setLedOff(unsigned char ledValue)
{
	PORTA |= (1<<ledValue);
}

// Blink a single led for a specific time
void blinkLed(unsigned char ledValue, int time)
{
	PORTA &= ~(1<<ledValue);
	rgbWait(time);
	PORTA |= (1<<ledValue);
	rgbWait(time);
}

// Set all the leds on
void setAllLedOn (void)
{
	PORTA = 0x00;
}

// Set all the leds off
void setAllLedOff (void)
{
	PORTA = 0x0F;
}

// Blink all leds for a specific time
void blinkAllLed(int time)
{
	PORTA = 0x00;
	rgbWait(time);
	PORTA = 0x0F;
	rgbWait(time);
}