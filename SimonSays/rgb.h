/*
 * rgb.h
 *
 * Created: 12-4-2021 15:56:22
 *  Author: timoj
 */ 


#ifndef RGB_H_
#define RGB_H_

#define LED_1 0
#define LED_2 1
#define LED_3 2
#define LED_4 3

//Init the rgb leds
void rgbLedInit(void);

//Set a specific color to the leds
void setLedColor(unsigned char r, unsigned char g, unsigned char b);

// Set a specific led on
void setLedOn(unsigned char ledValue);

// Set specific led off
void setLedOff(unsigned char ledValue);

// Blink a single led for a specific time
void blinkLed(unsigned char ledValue, int time);

// Set all the leds on
void setAllLedOn (void);

// Set all the leds off
void setAllLedOff (void);

// Blink all leds for a specific time
void blinkAllLed(int time);

#endif /* RGB_H_ */