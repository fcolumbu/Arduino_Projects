/*****************************************************************************************
/* Digital Thermometer
// by Frank Columbus, a digital thermometer using a Maxim DS75LV
// Created on 05 AUG 2018.
// This code runs on and Arduino Leonardo and should be portable to other models.
//
// Adapted from Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>
// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Original "Master Reader Created 29 March 2006
 
// This code also merges in the Seeed Studio code for the Grove LCD display.
// This example code is in the public domain.

// Related web links:
//
// Maxim DS75LVdatasheet
// https://datasheets.maximintegrated.com/en/ds/DS75LV.pdf
//
// Suggested prototyping aids from SchmartBoard
// http://schmartboard.com/schmartboard-through-hole-prototyping-shield-for-arduino-uno-with-components-and-free-breadboard/
// Check your chip's package type. - Yes, you can work with SMD's!
// http://schmartboard.com/schmartboard-ez-1-27mm-pitch-soic-to-dip-adapter-204-0004-01/
//
// Arduino Master Reader Tutorial
// https://www.arduino.cc/en/Tutorial/MasterReader
//
// Arduino documentation for the Wire Library
// https://www.arduino.cc/en/Reference/Wire
//
// Seeed Studio Tutorial for LCD RGB Backlight
// http://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
//
// Github Repository where this code is posted
// https://github.com/fcolumbu/Arduino_Projects
//
*****************************************************************************************/

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 255;
const int colorB = 255;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output  
  
// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
}

void loop() 
{
  Wire.requestFrom(0x48, 2);    // request 2 bytes from slave device 0x48 
// All address leads (A2, A1, A0) are connected to ground, i.e. all 0.
// Since the accuracy of the Maxim DS75LV is +/- 2 degrees from -25 to 
// +100 degrees C, we will keep the code simple and
// print only whole integers. Hence, we accept power up defaults. 
// No additional setup or parsing of the fractional values is required.
  
  int i=0;

  while (Wire.available()) {  // slave may send less than requested
    char c = Wire.read();     // receive a byte as character
    i++;                      // Since the loop starts with i=0 and 
                              // we only want the whole number of degrees Celsius,
                              // we will print only on odd values of i, i.e. the MSB
    if (i % 2 == 1)
    {                             
        Serial.println(c, DEC);        // Print the decimal value to the serial port.
        lcd.setCursor(0, 0);           // Column 0, line 0 -- top line
        lcd.print("                "); // Clear any left over characters.
        lcd.setCursor(0, 0);           // Column 0, line 0 -- top line
        lcd.print(c, DEC);             // Print the decimal value on the LCD.
        lcd.print(" degrees C");       // Print the units and return to the first column.

    }
  }
  delay(500); // Sample every 1/2 second. 
}
