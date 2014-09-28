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

Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&unit0, &unit1, &unit2, &unit3, &unit4, &unit5, &unit6, &unit7);

#define NUMTRELLIS 8
#define NUMKEYS (NUMTRELLIS * 16)

/* Create a map to go from x,y to i */
int xytoi[8][16] = {
  {60, 56, 52, 48, 44, 40, 36, 32}, 
  {61, 57, 53, 49, 45, 41, 37, 33},
  {62, 58, 54, 50, 46, 42, 38, 34},
  {63, 59, 55, 51, 47, 43, 39, 35},
  {12, 8, 4, 0, 28, 24, 20, 16},
  {13, 9, 5, 1, 29, 25, 21, 17},
  {14, 10, 6, 2, 30, 26, 22, 18},
  {15, 11, 7, 3, 31, 27, 23, 19}
};

/* Create a map to g from i to x,y */




/* Uno INT.0 is on Pin 2 */
#define INTPIN 2

volatile bool updateState = 0;
byte byte0;
byte byte1;

boolean waitingCommand = true;          
int command =  0;                      



void setup() 
{
	/* Trying a high speed to reduce latency */
	Serial.begin(38400);
	Serial.println("Trellis Demo");

	/* Disable PWM timer - does this even help? */
    TCCR1B &= ~(1 << CS12);
    TCCR1B &= ~(1 << CS11);
    TCCR1B &= ~(1 << CS10);  

	/* 16K33 Interrupt pin requires pullup */
	pinMode(INTPIN, INPUT);
	digitalWrite(INTPIN, HIGH);
	
	trellis.begin(0x70, 0x72, 0x71, 0x73, 0x74, 0x76, 0x75, 0x77); 
	
	/* Turn them all on */
	for (uint8_t i = 0; i < NUMKEYS; i++) 
	{
		trellis.setLED(i);
		trellis.writeDisplay();    
		delay(10);
	}

	/* Turn them off */
	for (uint8_t i = 0; i < NUMKEYS; i++) 
	{
		trellis.clrLED(i);
		trellis.writeDisplay();
		delay(50);
	}

	//TODO: Clear all the buttons

	attachInterrupt(0, buttonPress, CHANGE);	
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
	updateState = 1;
}

void readButtons()
{
	trellis.readSwitches();

	Serial.println("readswswitches");

	for (uint8_t i = 0; i < NUMKEYS; i++) 
	{
		if (trellis.justPressed(i)) 
		{
			
            TrellisToXY(i, TileOffsets, &xVal, &yVal);      
            Serial.write((0 << 4) | (1 & 15));      // OG           Serial.write((0 << 4) | (b & 15));
            Serial.write((yVal << 4) | (xVal & 15));      // OG          Serial.write((id << 4) | (i & 15));              
			
		}
	}
 
   trellis.writeDisplay();
}

