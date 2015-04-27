/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "U8glib.h"

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

///////////////////////////////////////////////////////////////////
//----- OLED instance
// IMPORTANT NOTE: The complete list of supported devices 
// with all constructor calls is here: http://code.google.com/p/u8glib/wiki/device
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 
///////////////////////////////////////////////////////////////////

// Remember received data
#define INPUT_BUFFER_LEN 3
char inputBuffer[INPUT_BUFFER_LEN];
// Remember temperature
int iRememberedTemp = 0;


void setup() {
  Serial.begin(9600);
  mlx.begin();
  for(int i=0; i<INPUT_BUFFER_LEN; i++)
    inputBuffer[i] = 0x00;
}

void loop() {
  boolean isRemember = false;
  
  // Check received data
  if(Serial.available()) {
    // Get a byte from Serial
    char tempChar = Serial.read();
    // Push to buffer
    for(int i=0; i<INPUT_BUFFER_LEN - 1; i++)
      inputBuffer[i] = inputBuffer[i+1];
    inputBuffer[INPUT_BUFFER_LEN - 1] = tempChar;
    
    // Check command from remote
    if(inputBuffer[0] == 'b') {
      if(inputBuffer[1] == '1' 
          || inputBuffer[1] == '2'
          || inputBuffer[1] == '3'
          || inputBuffer[1] == '4') {
        isRemember = true;
      }
    }
  }
  
  // Get temperature
  float currentCTemp = (int)(mlx.readObjectTempC());
  float currentFTemp = (int)(mlx.readObjectTempF());
  if(isRemember) {
    iRememberedTemp = (int)currentCTemp;
  }
  
  // For debug
  Serial.print("Ambient = "); Serial.print(currentCTemp); 
  Serial.print("*C\tObject = "); Serial.print(currentCTemp); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(currentFTemp); 
  Serial.print("*F\tObject = "); Serial.print(currentFTemp); Serial.println("*F");
  Serial.println();
  // display temperature on remote screen
  Serial.print("a");
  Serial.print(currentCTemp, 5);
  Serial.print("z");
  Serial.println();
  
  // display temperature on OLED
  String strTemp = String("");
  strTemp += (int)currentCTemp;
  char buff[10];
  strTemp.toCharArray(buff, 5);
  buff[2] = 0x27;
  buff[3] = 'C';
  buff[4] = 0x00;
  
  drawTemp(buff);
  
  delay(500);
}

void drawTemp(char* strTemp) {
  // picture loop  
  u8g.firstPage();  
  do {
    // show text
    u8g.setFont(u8g_font_courB14);
    u8g.setFontRefHeightExtendedText();
    u8g.setDefaultForegroundColor();
    u8g.setFontPosTop();
    u8g.drawStr(3, 0, "Temperature");
    u8g.drawStr(45, 20, strTemp);
    
    // show remembered temperature
    if(iRememberedTemp > 0) {
      String strTemp2 = String("");
      strTemp2 += iRememberedTemp;
      char buff[5];
      strTemp2.toCharArray(buff, 5);
      buff[2] = 0x27;
      buff[3] = 'C';
      buff[4] = 0x00;
      
      u8g.drawStr(3, 40, "Prev: ");
      u8g.drawStr(55, 40, buff);
    }
  } while( u8g.nextPage() );
}

