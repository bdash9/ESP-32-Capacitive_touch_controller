// Original code by Sara Santos https://randomnerdtutorials.com/esp32-touch-pins-arduino-ide/
//
// Changed to worh with the Adafruit Feather ESP32-S2 TFT by ben Dash

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// set pin numbers
const int touchPin = 10; 
const int ledPin = 13;

const int touch2Pin = 5;
const int led2Pin = 13;

// change with your threshold value
const int threshold = 9500;
// variable for storing the touch pin value 
int touchValue;
int touch2Value;

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
  tft.setTextSize(1);
  //Serial.begin(115200);
  //delay(1000); // give me time to bring up serial monitor
  // initialize the LED pin as an output:
  pinMode (ledPin, OUTPUT);
  pinMode (led2Pin, OUTPUT);
}

void loop() {
    loop1();
    loop2();
}

void loop1(){
  // read the state of the pushbutton value:
  touchValue = touchRead(touchPin);
  tft.print(touchValue);
  // check if the touchValue is below the threshold
  // if it is, set ledPin to HIGH
  if(touchValue < threshold){
    // turn LED on
    digitalWrite(ledPin, HIGH);
    tft.print("  - LED PIN 10 ");
    tft.setTextColor(ST77XX_RED);
    tft.println(" ON");
    tft.setTextColor(ST77XX_WHITE);    
  }
  else{
    // turn LED off
    digitalWrite(ledPin, LOW);
    //digitalWrite(ledPin, HIGH);
    tft.print(" - LED PIN 10 ");
    tft.setTextColor(ST77XX_GREEN);
    tft.println("OFF");
    tft.setTextColor(ST77XX_WHITE);        
  }
  delay(1500);
}

void loop2(){
  touch2Value = touchRead(touch2Pin);
  tft.print(touch2Value);
  // check if the touch2Value is below the threshold
  // if it is, set ledPin to HIGH
  if(touch2Value < threshold){
    // turn LED on
    digitalWrite(ledPin, HIGH);
    tft.print("  - LED PIN  5 ");
    tft.setTextColor(ST77XX_RED);
    tft.println(" ON");
    tft.setTextColor(ST77XX_WHITE);   
  }
  else{
    // turn LED off
    digitalWrite(ledPin, LOW);
    //digitalWrite(ledPin, HIGH);
    tft.print(" - LED PIN  5 ");
    tft.setTextColor(ST77XX_GREEN);
    tft.println("OFF");
    tft.setTextColor(ST77XX_WHITE);    
  }
  delay(1500);
}
  
