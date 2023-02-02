// Original code by Sara Santos https://randomnerdtutorials.com/esp32-touch-pins-arduino-ide/
//
// Changed to work with the Adafruit Feather ESP32-S2 TFT by ben Dash

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// set pin numbers

const int touchPin_UP = 10;   //UP
//const int ledPin = 13;

const int touchPin_DOWN = 9;   //DOWN
//const int led2Pin = 13;

const int touchPin_LEFT = 6;    //LEFT
//const int led2Pin = 13;

const int touchPin_RIGHT = 5;   //RIGHT
//const int led2Pin = 13;

// change with your threshold value
//const int threshold = 9500;
// Change Threshold for when it is connected to a controller
const int threshold = 25000;
// variable for storing the touch pin value 
int touchValue_UP;
int touchValue_DOWN;
int touchValue_LEFT;
int touchValue_RIGHT;

void setup(){
  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

    // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  tft.init(135, 240); // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(4);
 }

void loop() {
    loop_UP();
    loop_DOWN();
    loop_LEFT();
    loop_RIGHT();
}

void loop_UP(){
  // read the state of the pushbutton value:
  touchValue_UP = touchRead(touchPin_UP);
  if(touchValue_UP < threshold){
  
  }
  else{
   
    tft.setCursor(100, 10);     // (x,y)
    tft.setTextColor(ST77XX_BLUE);
    tft.print("UP");
    tft.fillScreen(ST77XX_BLACK);      
  }
}

void loop_DOWN(){
  // read the state of the pushbutton value:
  touchValue_DOWN = touchRead(touchPin_DOWN);
  if(touchValue_DOWN < threshold){
   
  }
  else{
    tft.setCursor(85, 105);
    tft.setTextColor(ST77XX_GREEN);
    tft.print("DOWN");
    tft.fillScreen(ST77XX_BLACK);
    
  }
}

void loop_LEFT(){
  // read the state of the pushbutton value:
  touchValue_LEFT = touchRead(touchPin_LEFT);
  if(touchValue_LEFT < threshold){
  }
  else{
    tft.setCursor(10, 60);
    tft.setTextColor(ST77XX_RED);
    tft.print("LEFT");
    tft.fillScreen(ST77XX_BLACK);  
  }
}

void loop_RIGHT(){
  // read the state of the pushbutton value:
  touchValue_RIGHT = touchRead(touchPin_RIGHT);
  if(touchValue_RIGHT < threshold){
  }
  else{
    tft.setCursor(120, 60);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("RIGHT");
    tft.fillScreen(ST77XX_BLACK);     
  }
}


  
