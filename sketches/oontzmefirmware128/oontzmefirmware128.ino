/*************************************************** 
  This is a test example for the Adafruit Trellis w/HT16K33
  Designed specifically to work with the Adafruit Trellis 
  ----> https://www.adafruit.com/products/1616
  ----> https://www.adafruit.com/products/1611

  Based on code originally written by Limor Fried/Ladyada for Adafruit Industries.  
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "Adafruit_Trellis.h"

/* Allocate some storage space */
Adafruit_Trellis unit0 = Adafruit_Trellis();
Adafruit_Trellis unit1 = Adafruit_Trellis();
Adafruit_Trellis unit2 = Adafruit_Trellis();
Adafruit_Trellis unit3 = Adafruit_Trellis();
Adafruit_Trellis unit4 = Adafruit_Trellis();
Adafruit_Trellis unit5 = Adafruit_Trellis();
Adafruit_Trellis unit6 = Adafruit_Trellis();
Adafruit_Trellis unit7 = Adafruit_Trellis();

//Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&unit0);
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&unit0, &unit1, &unit2, &unit3, &unit4, &unit5, &unit6, &unit7);

#define NUMTRELLIS 8
#define NUMKEYS (NUMTRELLIS * 16)
#define XSIZE 16
#define YSIZE 8

/* Create a map to go from x,y to i */
static uint8_t XYTOI[XSIZE][YSIZE] = {
    {12, 8, 4, 0, 76, 72, 68, 64}, 
    {13, 9, 5, 1, 77, 73, 69, 65},
    {14, 10, 6, 2, 78, 74, 70, 66},
    {15, 11, 7, 3, 79, 75, 71, 67},
    {28, 24, 20, 16, 92, 88, 84, 80},
    {29, 25, 21, 17, 93, 89, 85, 81},
    {30, 26, 22, 18, 94, 90, 86, 82},
    {31, 27, 23, 19, 95, 91, 87, 83},
    {44, 40, 36, 32, 108, 104, 100, 96}, 
    {45, 41, 37, 33, 109, 105, 101, 97},
    {46, 42, 38, 34, 110, 106, 102, 98},
    {47, 43, 39, 35, 111, 107, 103, 99},
    {60, 56, 52, 48, 124, 120, 116, 112},
    {61, 57, 53, 49, 125, 121, 117, 113},
    {62, 58, 54, 50, 126, 122, 118, 114},
    {63, 59, 55, 51, 127, 123, 119, 115}
};

static uint8_t ITOXY[NUMKEYS][2] = {
	{ 0, 3 },
	{ 1, 3 },
	{ 2, 3 },
	{ 3, 3 },
	
	{ 0, 2 },
	{ 1, 2 },
	{ 2, 2 },
	{ 3, 2 },
	
	{ 0, 1 },
	{ 1, 1 },
	{ 2, 1 },
	{ 3, 1 },
	
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 0 },
	{ 3, 0 },
	
	{ 4, 3 },
	{ 5, 3 },
	{ 6, 3 },
	{ 7, 3 },
	
	{ 4, 2 },
	{ 5, 2 },
	{ 6, 2 },
	{ 7, 2 },
	
	{ 4, 1 },
	{ 5, 1 },
	{ 6, 1 },
	{ 7, 1 },
	
	{ 4, 0 },
	{ 5, 0 },
	{ 6, 0 },
	{ 7, 0 },
	
	{ 8, 3 },
	{ 9, 3 },
	{ 10, 3 },
	{ 11, 3 },
	
	{ 8, 2 },
	{ 9, 2 },
	{ 10, 2 },
	{ 11, 2 },
	
	{ 8, 1 },
	{ 9, 1 },
	{ 10, 1 },
	{ 11, 1 },
	
	{ 8, 0 },
	{ 9, 0 },
	{ 10, 0 },
	{ 11, 0 },	
	
	{ 12, 3 },
	{ 13, 3 },
	{ 14, 3 },
	{ 15, 3 },
	
	{ 12, 2 },
	{ 13, 2 },
	{ 14, 2 },
	{ 15, 2 },
	
	{ 12, 1 },
	{ 13, 1 },
	{ 14, 1 },
	{ 15, 1 },
	
	{ 12, 0 },
	{ 13, 0 },
	{ 14, 0 },
	{ 15, 0 },
	
	{ 0, 7 },
	{ 1, 7 },
	{ 2, 7 },
	{ 3, 7 },
	
	{ 0, 6 },
	{ 1, 6 },
	{ 2, 6 },
	{ 3, 6 },
	
	{ 0, 5 },
	{ 1, 5 },
	{ 2, 5 },
	{ 3, 5 },
	
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 4 },
	{ 3, 4 },

	{ 4, 7 },
	{ 5, 7 },
	{ 6, 7 },
	{ 7, 7 },
	
	{ 4, 6 },
	{ 5, 6 },
	{ 6, 6 },
	{ 7, 6 },
	
	{ 4, 5 },
	{ 5, 5 },
	{ 6, 5 },
	{ 7, 5 },
	
	{ 4, 4 },
	{ 5, 4 },
	{ 6, 4 },
	{ 7, 4 },

	{ 8, 7 },
	{ 9, 7 },
	{ 10, 7 },
	{ 11, 7 },
	
	{ 8, 6 },
	{ 9, 6 },
	{ 10, 6 },
	{ 11, 6 },
	
	{ 8, 5 },
	{ 9, 5 },
	{ 10, 5 },
	{ 11, 5 },
	
	{ 8, 4 },
	{ 9, 4 },
	{ 10, 4 },
	{ 11, 4 },	

	{ 12, 7 },
	{ 13, 7 },
	{ 14, 7 },
	{ 15, 7 },
	
	{ 12, 6 },
	{ 13, 6 },
	{ 14, 6 },
	{ 15, 6 },
	
	{ 12, 5 },
	{ 13, 5 },
	{ 14, 5 },
	{ 15, 5 },
	
	{ 12, 4 },
	{ 13, 4 },
	{ 14, 4 },
	{ 15, 4 }
		
};

#define INTPIN 7

volatile bool updateState = 0;


void setup() 
{

	Serial.begin(38400);

	/* interrupt pin requires pullup */
	pinMode(INTPIN, INPUT);
	digitalWrite(INTPIN, HIGH);
	
	trellis.begin(0x70, 0x72, 0x71, 0x73, 0x74, 0x76, 0x75, 0x77);

	trellis.clear();
	trellis.writeDisplay();
	
	attachInterrupt(4, buttonPress, CHANGE);
}


void loop() 
{
	unsigned long t = millis();
	
  	if (t % 50 == 0)
	{
		if (updateState)
		{
			updateState = 0;
			readButtons();
		}
	}	
}

void buttonPress()
{
	/* Flag that we need to re-read the buttons */
	updateState = 1;
}

void readButtons()
{
	trellis.readSwitches();

	for (uint8_t i = 0; i < NUMKEYS; i++) 
	{
		if (trellis.justPressed(i)) 
		{
            Serial.write((0 << 4) | (1 & 15));
            Serial.write((ITOXY[i][1] << 4) | (ITOXY[i][0] & 15));
		}
		if (trellis.justReleased(i))
		{
			uint8_t cmd = (0 << 4) | (0 & 15);
            Serial.write(cmd);
            Serial.write((ITOXY[i][1] << 4) | (ITOXY[i][0] & 15));
		}
	} 
}

