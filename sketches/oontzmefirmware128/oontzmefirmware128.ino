/* 

nw2s::b - A microcontroller-based modular synth control framework 
Copyright (C) 2013 Scott Wilson (thomas.scott.wilson@gmail.com) 

This program is free software: you can redistribute it and/or modify 
it under the terms of the GNU General Public License as published by 
the Free Software Foundation, either version 3 of the License, or 
(at your option) any later version. 

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
GNU General Public License for more details. 

You should have received a copy of the GNU General Public License 
along with this program. If not, see <http://www.gnu.org/licenses/>. 


This code borrows from (and ahem fixes) a number of sources including:

* Code originally written by Limor Fried/Ladyada for Adafruit Industries for the Adafruit Trellis w/HT16K33
* The Arduinome clone originally by Owen Vallis & Jordan Hochenbaum: http://flipmu.com/work/arduinome/
* Robin Stubbs https://github.com/rbnstubbs/trellis-monome

*/ 

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
	
	{64, 68, 72, 76, 0, 4, 8, 12},
	{65, 69, 73, 77, 1, 5, 9, 13},
	{66, 70, 74, 78, 2, 6, 10, 14},
	{67, 71, 75, 79, 3, 7, 11, 15},
	{80, 84, 88, 92, 16, 20, 24, 28},
	{81, 85, 89, 93, 17, 21, 25, 29},
	{82, 86, 90, 94, 18, 22, 26, 30},
	{83, 87, 91, 95, 19, 23, 27, 31},
	{96, 100, 104, 108, 32, 36, 40, 44},
	{97, 101, 105, 109, 33, 37, 41, 45},
	{98, 102, 106, 110, 34, 38, 42, 46},
	{99, 103, 107, 111, 35, 39, 43, 47},
	{112, 116, 120, 124, 48, 52, 56, 60},
	{113, 117, 121, 125, 49, 53, 57, 61},
	{114, 118, 122, 126, 50, 54, 58, 62},
	{115, 119, 123, 127, 51, 55, 59, 63}
		
};

static uint8_t ITOXY[NUMKEYS][2] = {
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 4 },
	{ 3, 4 },
	
	{ 0, 5 },
	{ 1, 5 },
	{ 2, 5 },
	{ 3, 5 },
	
	{ 0, 6 },
	{ 1, 6 },
	{ 2, 6 },
	{ 3, 6 },
	
	{ 0, 7 },
	{ 1, 7 },
	{ 2, 7 },
	{ 3, 7 },
	
	{ 4, 4 },
	{ 5, 4 },
	{ 6, 4 },
	{ 7, 4 },
	
	{ 4, 5 },
	{ 5, 5 },
	{ 6, 5 },
	{ 7, 5 },
	
	{ 4, 6 },
	{ 5, 6 },
	{ 6, 6 },
	{ 7, 6 },
	
	{ 4, 7 },
	{ 5, 7 },
	{ 6, 7 },
	{ 7, 7 },
	
	{ 8, 4 },
	{ 9, 4 },
	{ 10, 4 },
	{ 11, 4 },
	
	{ 8, 5 },
	{ 9, 5 },
	{ 10, 5 },
	{ 11, 5 },
	
	{ 8, 6 },
	{ 9, 6 },
	{ 10, 6 },
	{ 11, 6 },
	
	{ 8, 7 },
	{ 9, 7 },
	{ 10, 7 },
	{ 11, 7 },	
	
	{ 12, 4 },
	{ 13, 4 },
	{ 14, 4 },
	{ 15, 4 },
	
	{ 12, 5 },
	{ 13, 5 },
	{ 14, 5 },
	{ 15, 5 },
	
	{ 12, 6 },
	{ 13, 6 },
	{ 14, 6 },
	{ 15, 6 },
	
	{ 12, 7 },
	{ 13, 7 },
	{ 14, 7 },
	{ 15, 7 },
	
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 0 },
	{ 3, 0 },
	
	{ 0, 1 },
	{ 1, 1 },
	{ 2, 1 },
	{ 3, 1 },
	
	{ 0, 2 },
	{ 1, 2 },
	{ 2, 2 },
	{ 3, 2 },
	
	{ 0, 3 },
	{ 1, 3 },
	{ 2, 3 },
	{ 3, 3 },

	{ 4, 0 },
	{ 5, 0 },
	{ 6, 0 },
	{ 7, 0 },
	
	{ 4, 1 },
	{ 5, 1 },
	{ 6, 1 },
	{ 7, 1 },
	
	{ 4, 2 },
	{ 5, 2 },
	{ 6, 2 },
	{ 7, 2 },
	
	{ 4, 3 },
	{ 5, 3 },
	{ 6, 3 },
	{ 7, 3 },

	{ 8, 0 },
	{ 9, 0 },
	{ 10, 0 },
	{ 11, 0 },
	
	{ 8, 1 },
	{ 9, 1 },
	{ 10, 1 },
	{ 11, 1 },
	
	{ 8, 2 },
	{ 9, 2 },
	{ 10, 2 },
	{ 11, 2 },
	
	{ 8, 3 },
	{ 9, 3 },
	{ 10, 3 },
	{ 11, 3 },	

	{ 12, 0 },
	{ 13, 0 },
	{ 14, 0 },
	{ 15, 0 },
	
	{ 12, 1 },
	{ 13, 1 },
	{ 14, 1 },
	{ 15, 1 },
	
	{ 12, 2 },
	{ 13, 2 },
	{ 14, 2 },
	{ 15, 2 },
	
	{ 12, 3 },
	{ 13, 3 },
	{ 14, 3 },
	{ 15, 3 }
		
};

#define INTPIN 7

/* State variables for command processing */
volatile bool updateState = 0;
unsigned long lastchecktime = 0;
bool waitingCommand = true;  
uint8_t command =  0;  
uint8_t state = 0;
uint8_t byte0 = 0;
uint8_t byte1 = 0;
uint8_t x = 0;
uint8_t y = 0;


void setup() 
{

	Serial.begin(115200);

	/* interrupt pin requires pullup */
	pinMode(INTPIN, INPUT);
	digitalWrite(INTPIN, HIGH);
	
	trellis.begin(0x70, 0x72, 0x71, 0x73, 0x74, 0x76, 0x75, 0x77);

	trellis.clear();
	trellis.writeDisplay();
}


void loop() 
{
	unsigned long t = millis();
	
	checkSerial();
	
  	if (t > 50 + lastchecktime)
	{
		lastchecktime = t;
		readButtons();
	}	
}

void readButtons()
{
	trellis.readSwitches();

	for (uint8_t i = 0; i < NUMKEYS; i++) 
	{
		if (trellis.justPressed(i)) 
		{
            Serial.write((0 << 4) | (1 & 15));
            Serial.write((ITOXY[i][0] << 4) | (ITOXY[i][1] & 15));
		}
		if (trellis.justReleased(i))
		{
			uint8_t cmd = (0 << 4) | (0 & 15);
            Serial.write(cmd);
            Serial.write((ITOXY[i][0] << 4) | (ITOXY[i][1] & 15));
		}
	} 
}

void checkSerial() 
{    
	while (Serial.available()) 
	{
    	if (waitingCommand) 
		{          
			byte0 = Serial.read();
			command = byte0 >> 4;
			waitingCommand = false;
    	}

		if (Serial.available()) 
		{ 
			/* Data for the command is stored in second byte */
			byte1 = Serial.read(); 
			waitingCommand = true; 

			switch(command) 
			{

				/* LED Command */
            	case 2: 
				
					/* LED On or Off? */
					state = byte0 & 0x0F; 
					x = (byte1 >> 4); 
					y = (byte1 & 15);

					if (!state) 
					{
						trellis.clrLED(XYTOI[x][y]);
					}
               	 	else 
					{
						trellis.setLED(XYTOI[x][y]); 
               	 	}
              
			  	  	break;

				/* LED Intensity */
				case 3: 
					
					/* We ignore for now. Don't support it */
					//curInt = (byte1 & 0x0f);
					break;
					
				/* LED Test Command */
				case 4: 
				
					/* What does this even do? do we care? */
					if ((byte1 & 1) == 0) 
					{
						
                	}
              	  	else 
					{
						trellis.clear();
					}
				   	
					break;

				/* Tilt Command */
				case 5: 
              
					/* No accellerometers, let's ignore for now */
			  		state = byte1 & 0x0F;
            		break;

				/* Shutdown: another one we get to blissfully ignore */
            	case 6: 
            
					break;
				
				/* LED Row command */	
				case 7:

					/* There's not enough bytes - what's that mean? */
					/* For now, we'll only do the first half of the display */
					y = 0x0F & byte0;
				    x = 0;

					/* No matter the size of the unit, only 8 bits are stored in this command */
				    for (int i = 0; i < 8; i++)
					{
						if (byte1 & (1 << (7 - i)))
						{
							trellis.setLED(XYTOI[i][y]);
						}
						else
						{
							trellis.clrLED(XYTOI[i][y]);
						}
					}

					break;
			
				/* LED Column Command */
				case 8:
					 
					/* Let's assume this will get the most use on a 64 and 128 */
					x = 0x0F & byte0;
					y = 0;

					/* No matter the size of the unit, only 8 bits are stored in this command */
				    for (int i = 0; i < 8; i++)
					{
						if (byte1 & (1 << (7 - i)))
						{
							trellis.setLED(XYTOI[x][i]);
						}
						else
						{
							trellis.clrLED(XYTOI[x][i]);
						}
					}

            		break;
			}
		}
	}
		
	/* Don't update the display until the serial queue is empty */
	trellis.writeDisplay();
}			
				
