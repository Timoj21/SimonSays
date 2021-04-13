/*
 * SimonSays.c
 *
 * Created: 12-4-2021 14:12:01
 * Author : timoj
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "rgb.h"

static int level = 1; //Level for the user
const int maxLevel = 3; //Max level for the user

void wait(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

// Get a new random sequence
void get_sequence(char* sequence)
{
	for(int i = 0; i < level; i++)
	{
		sequence[i] = rand() % 4;
	}
}

// Show the sequence on the leds
void show_sequence(char* sequence)
{
	setLedColor(0, 255, 0);
	for(int i = 0; i < level; i++)
	{
		blinkLed(sequence[i], 500);
	}
}

// Wait for the user to press the buttons to get a sequence
void wait_for_sequence(char* answer)
{
	int presses = 0;			//Amount of presses the user has pressed
	int previousButton = 0;		//Int to remember the previous pressed button
	bool released = true;		//Bool to check if the previous button is released
	
	// Keep checking if button is pressed until you have the same amount as the level
	while(presses < level)
	{
		if(PINA & (1<<4) && released)
		{
			answer[presses] = 0;
			presses++;
			released = false;
			previousButton = 4;
		} else if(PINA & (1<<5) && released)
		{
			answer[presses] = 1;
			presses++;
			released = false;
			previousButton = 5;
		} else if(PINA & (1<<6) && released)
		{
			answer[presses] = 2;
			presses++;
			released = false;
			previousButton = 6;
		} else if(PINA & (1<<7) && released)
		{
			answer[presses] = 3;
			presses++;
			released = false;
			previousButton = 7;
		}
		
		// If the previous button that was pressed is released, the next button can be pressed
		if(!(PINA & (1<<previousButton)))
		{
			released = true;
		}
	}
}

// Check if the user's sequence is correct
int check_sequence(char *sequence, char *answer)
{
	for(int i = 0; i < level; i++)
	{
		if(sequence[i] != answer[i])
		{
			return 0;
		}
	}
	return 1;
}


int main(void)
{
	rgbLedInit();
	
	char *sequence = malloc(maxLevel);
	char *answer = malloc(maxLevel);
	
	
	// Show green leds
	setLedColor(0, 0, 255);
	blinkAllLed(2000);
	
    while (1) 
    {
		get_sequence(sequence);
		show_sequence(sequence);
		wait_for_sequence(answer);
	
		if(check_sequence(sequence,answer))
		{
			//Show green leds to tell the answer was correct
			level++;
			setLedColor(0, 0, 255);
			blinkAllLed(2000);
			if(level > maxLevel)
			{
				//Show white leds to tell the game is finished
				setLedColor(100, 100, 100);
				blinkAllLed(2000);
				level = 1;
			}
		} else
		{
			//Show red leds to tell the answer was not correct
			level = 1;
			setLedColor(255, 0, 0);
			blinkAllLed(2000);
		}
    }
}

