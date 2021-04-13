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
		setLedOn(sequence[i]);
		wait(500);
		setLedOff(sequence[i]);
		wait(500);
	}
}

// Wait for the user to press the buttons to get a sequence
void wait_for_sequence(char* answer)
{
	int presses = 0;			//Amount of presses the user has pressed
	int previousButton = 0;		//Int to remember the previous pressed button
	bool released = true;		//Bool to check if the previous button is released
	
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
	
	char *sequence = malloc(10);
	char *answer = malloc(10);
	
	
	// Show green leds
	setLedColor(0, 0, 255);
	setAllLedOn();
	wait(2000);
	setAllLedOff();
	wait(2000);
	
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
			setAllLedOn();
			wait(2000);
			setAllLedOff();
			wait(2000);
			if(level > 10)
			{
				//Show white leds to tell the game is finished
				setLedColor(100, 100, 100);
				setAllLedOn();
				wait(2000);
				setAllLedOff();
				wait(2000);
				level = 1;
			}
		} else
		{
			//Show red leds to tell the answer was not correct
			level = 1;
			setLedColor(255, 0, 0);
			setAllLedOn();
			wait(2000);
			setAllLedOff();
			wait(2000);
		}
    }
}

