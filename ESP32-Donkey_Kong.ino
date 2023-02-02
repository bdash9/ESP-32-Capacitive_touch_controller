// Downloaded orginal code from https://www.brettb.com/coding-tutorials/arduino-tft-display-game-sprites/

// Edited by Ben Dash 


//#include <HID.h>

/**************************************************************************
This is a library for several Adafruit displays based on ST77* drivers.
Works with the Adafruit 1.8" TFT Breakout w/SD card
----> http://www.adafruit.com/products/358
The 1.8" TFT shield
----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
----> https://www.adafruit.com/product/2088
The 1.14" TFT breakout
----> https://www.adafruit.com/product/4383
The 1.3" TFT breakout
----> https://www.adafruit.com/product/4313
The 1.54" TFT breakout
----> https://www.adafruit.com/product/3787
The 1.69" TFT breakout
----> https://www.adafruit.com/product/5206
The 2.0" TFT breakout
----> https://www.adafruit.com/product/4311
as well as Adafruit raw 1.8" TFT display
----> http://www.adafruit.com/products/618

Check out the links above for our tutorials and wiring diagrams.
These displays use SPI to communicate, 4 or 5 pins are required to
interface (RST is optional).

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
MIT license, all text above must be included in any redistribution
**************************************************************************/

#include <Adafruit_GFX.h> // Core graphics library
//#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
/*
#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
#define TFT_CS 14
#define TFT_RST 15
#define TFT_DC 32

#elif defined(ESP8266)
#define TFT_CS 4
#define TFT_RST 16 
#define TFT_DC 5

#else
// For the breakout board, you can use any 2 or 3 pins.
// These pins will also work for the 1.8" TFT shield.
#define TFT_CS 10
#define TFT_RST 8 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 9
#endif
*/


// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.

// For 1.44" and 1.8" TFT with ST7735 use:
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// For [1.14"], 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


// OPTION 2 lets you interface the display using ANY TWO or THREE PINS,
// tradeoff being that performance is not as fast as hardware SPI above.
//#define TFT_MOSI 11 // Data out
//#define TFT_SCLK 13 // Clock out

//If you buy your TFT from eBay don't be surprised if the colours are messed up.
//I found this code sorted my colours out. The library's colours (e.g. ST77XX_CYAN)
//were all wrong on my particular TFT screen
//Credit for sorting this:
//https://forum.arduino.cc/t/colour-confusion-issue-with-unbranded-160x80-tft-and-adafruit-library/604752/12
//#define BLACK 0xFFFF
#define BLACK 0x0000
//#define BLUE 0x07FF
#define BLUE 0x1F
//#define RED 0xFFE0
#define RED 0xF800
#define GREEN 0x7E0
//#define GREEN 0xF81F
//#define CYAN 0x001F
#define CYAN 0x7FF
//#define MAGENTA 0x07E0
#define MAGENTA 0xF81F
//#define YELLOW 0xF800
#define YELLOW 0xFFE0
//#define WHITE 0x0000
#define WHITE 0xFFFF
//#define DGRAY 0x528A
#define DGRAY 0x7BEF
//#define LGRAY 0x2945
#define LGRAY 0xBDF7
//#define ORANGE 0xFC02
#define ORANGE 0xFBE0


//Define a vertical start position which makes it easy to move everything for specific displays
#define START_POS 2

// For ST7735-based displays, we will use this call
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// OR for the ST7789-based displays, we will use this call
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

//These static monochrome bitmaps were generated from .PNG's
//using image2cpp: http://javl.github.io/image2cpp/
//I'll cover these in a different tutorial...

const unsigned char epd_bitmap_Girder_8x8 [] PROGMEM = {
0xf3, 0xdb, 0xcf, 0xc7, 0xcf, 0xdb, 0xf3, 0xe3
};

const unsigned char epd_bitmap_Ladder_8x8 [] PROGMEM = {
0xff, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xff
};

const unsigned char epd_bitmap_OilDrum_12x12 [] PROGMEM = {
0xf7, 0xd0, 0xf4, 0x50, 0xf5, 0x50, 0xf4, 0x50, 0xf7, 0xd0, 0xf4, 0x50, 0xf4, 0x50, 0xf7, 0xd0, 
0xf4, 0x50, 0xf4, 0x50, 0xf5, 0xd0, 0xf7, 0xd0
};

const unsigned char epd_bitmap_Fire_12x7 [] PROGMEM = {
0x40, 0x90, 0xe0, 0x08, 0x10, 0xe0, 0xd0, 0xf4, 0x20, 0x48, 0xd8, 0xf2
};

const unsigned char epd_bitmap_Fireball_Right [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x3f, 
0x80, 0x00, 0x7f, 0xc4, 0x00, 0x73, 0xc0, 0x00, 0x7f, 0xa0, 0x00, 0x7f, 0x80, 0x00, 0x33, 0x40, 
0x00, 0x3f, 0x00, 0x00, 0x1e, 0x08, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char epd_bitmap_Fireball_Left [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x1e, 0x08, 0x00, 0x3f, 0x00, 0x00, 0x33, 
0x40, 0x00, 0x7f, 0x80, 0x00, 0x7f, 0xa0, 0x00, 0x73, 0xc0, 0x00, 0x7f, 0xc4, 0x00, 0x3f, 0x80, 
0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00
};

//chars should be one character longer than the actual string to account for the 0
static char marioFacingLeft[272] = "00000022220000000L00022222222000000L00000661111000000L00666166166100000L06661661166100000L00111166661110000L00066666660000000L66600121111100000L66661111111100000L06661111112200000L00002222222222110L00002222222222110L00000222002222110L00000011100000010L00000111100000000";
static char marioFacingRight[264] = "00000002222000000L00000022222222000L00000011116600000L00000166166166600L000000166116616660L00001116666111100L00000006666666000L000001111121006660L000001111111166660L00000221111116660L01122222222220L01122222222220L0112222002220L01000000111000000L00000000111100000";
static char princess[294] = "08888880L88888888L07777888800000L77077878800088L07777788000880L0077777888800L00007773388888L00037733388880L00033333300808L00003333300000L77333333000000L07333000L0003333333L077333333333L07333333333773L00333333377733L00333337773337L0033377733333L00777733373888L0033333770088L007777700088L088808";
static char barrel[117] = "00008888L0088222288L08222222228L822222112228L822221122228L822211222228L822112212228L08222222228L0088222288L00008888";

//Noob mistake... it's best to avoid String...
//Soon you'll get strange memory errors and stuff going on
//static String princess = "08888880L88888888L07777888800000L77077878800088L07777788000880L0077777888800L00007773388888L00037733388880L00033333300808L00003333300000L77333333000000L07333000L0003333333L077333333333L07333333333773L00333333377733L00333337773337L0033377733333L00777733373888L0033333770088L007777700088L088808";

void setup(void) {
//If you've not set up your screen before you may have to play around with these...

// Use this initializer if using a 1.8" TFT screen:
//tft.initR(INITR_BLACKTAB); // Init ST7735S chip, black tab

// OR use this initializer if using a 1.8" TFT screen with offset such as WaveShare:
// tft.initR(INITR_GREENTAB); // Init ST7735S chip, green tab

// OR use this initializer (uncomment) if using a 1.44" TFT:
//tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab

// OR use this initializer (uncomment) if using a 0.96" 160x80 TFT:
//tft.initR(INITR_MINI160x80); // Init ST7735S mini display

// tft.initR(INITR_GREENTAB);
//tft.setRotation(ST7735_MADCTL_BGR);

  
  //Initialize the ST7789 - Ben
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);
  tft.init(135, 240); // Init ST7789 YxX
  tft.setRotation(2);


// SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
// Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
// may end up with a black screen some times, or all the time.
//tft.setSPISpeed(40000000);




//I played around with these functions which invert the colours. They may (or may not) work well for your TFT
//tft.fillScreen(BLACK);
tft.fillScreen(ST77XX_BLACK);
//tft.invertDisplay(1);

//Of fundamental importance in this tutorial... how to place an individual coloured pixel
//tft.drawPixel(xPos, yPos, ORANGE); 
//Remember I'm using the TFT in a landscape direction (I'm still confused by this...)

//Call functions to place the static sprites
setUpGirders();
placeLadders();
placeOilDrum();

//Uncomment this if you need to print debugging text on the TFT
//tft.setCursor(10, 10);
//tft.setTextColor(WHITE);
//tft.print("Hello World");

placeSprite(START_POS + 75, 142, princess);
placeSprite(START_POS + 22, 144, barrel);
placeSprite(START_POS + 50, 20, barrel);

}


uint16_t fireColor = ORANGE;
uint16_t fireball1Color = RED;
uint16_t fireball2Color = RED;

uint16_t marioYPos = START_POS + 26;
uint16_t marioXPos = 46;
uint16_t marioCycleCounter = 0;
uint16_t fireCycleCounter = 0;
uint16_t fireball1CycleCounter = 0;
uint16_t fireball2CycleCounter = 0;
char marioDirection = 'R';
uint16_t marioMaxXPos = 78;
uint16_t marioMinXPos = 46;

char fireball1Direction = 'R';
uint16_t fireball1YPos = START_POS + 38;
uint16_t fireball1XPos = 70;

char fireball2Direction = 'R';
uint16_t fireball2YPos = START_POS + 37;
uint16_t fireball2XPos = 96;

//Main program loop. Note I use different counters which prevent the colours of the various sprites
//cycling at the same time
void loop() {

if (fireCycleCounter == 0) {
tft.drawBitmap(START_POS + 22, 6, epd_bitmap_Fire_12x7, 7, 12, fireColor);
if (fireColor == ORANGE) {fireColor = YELLOW; } else {fireColor = ORANGE;}
}

if (fireball1CycleCounter == 0) {

if (fireball1Direction == 'R') {
tft.drawBitmap(fireball1YPos, fireball1XPos, epd_bitmap_Fireball_Right, 17, 16, fireball1Color);
fireball1Direction = 'L';
}

if (fireball1Direction == 'L') {
tft.drawBitmap(fireball1YPos, fireball1XPos, epd_bitmap_Fireball_Left, 17, 16, fireball1Color);
fireball1Direction = 'R';
}

if (fireball1Color == ORANGE) {fireball1Color = RED; } else {fireball1Color = ORANGE;}
}

if (fireball2CycleCounter == 0) {

if (fireball2Direction == 'R') {
tft.drawBitmap(fireball2YPos, fireball2XPos, epd_bitmap_Fireball_Right, 17, 16, fireball2Color);
fireball2Direction = 'L';
}

if (fireball2Direction == 'L') {
tft.drawBitmap(fireball2YPos, fireball2XPos, epd_bitmap_Fireball_Left, 17, 16, fireball2Color);
fireball2Direction = 'R';
}

if (fireball2Color == ORANGE) {fireball2Color = RED; } else {fireball2Color = ORANGE;}
}

if (marioCycleCounter == 0) {

if (marioDirection == 'R') {
placeSprite(marioYPos, marioXPos, marioFacingRight);

if (marioXPos > marioMaxXPos) {
placeSprite(marioYPos, marioXPos, marioFacingLeft);
marioDirection = 'L';
} else {
marioXPos = marioXPos + 1;
}
}

if (marioDirection == 'L') {
placeSprite(marioYPos, marioXPos, marioFacingLeft);
if (marioXPos < marioMinXPos) {
placeSprite(marioYPos, marioXPos, marioFacingRight);
marioDirection = 'R';
} else {
marioXPos = marioXPos - 1;
}
}


}

marioCycleCounter = marioCycleCounter + 1;
fireCycleCounter = fireCycleCounter + 1;
fireball1CycleCounter = fireball1CycleCounter + 1;

if (marioCycleCounter = 30) {marioCycleCounter = 0;}
if (fireCycleCounter = 20) {fireCycleCounter = 0;}
if (fireball1CycleCounter = 64) {fireball1CycleCounter = 0;}
if (fireball2CycleCounter = 72) {fireball2CycleCounter = 0;}

delay(50);
}

//Places a particular sprite on the TFT display
//If you want to use more colours then alter the getColorCode function
//Note that L is a special character and denotes the end of the line of pixels
//If your sprite has a lot of whitespace (or black - same as background) to save precious memory
//you don't need to put them all in, but this may corrupt the display when the sprite is moved
void placeSprite(uint16_t yPos, uint16_t xPos, String characterData) {

uint16_t lineLength = 0;
for (int16_t x=0; x < characterData.length(); x+=1) {

char i = characterData.charAt(x);
if (i == 'L') {
xPos = xPos - lineLength;
lineLength = 0;
yPos = yPos - 1;
} else {
tft.drawPixel(yPos, xPos, getColorCode(i));
lineLength = lineLength + 1;
xPos = xPos + 1;
}

}

}

//I have based the colours on the ZX Spectrum's colour codes (but added orange)
//Feel free to add your own colour codes here. You will need to set up constants
//for the other colours (see top of this code).
int16_t getColorCode(char code) {

switch(code) {
case '1':
return BLUE;
case '2':
return RED;
case '3':
return MAGENTA;
case '4':
return GREEN;
case '5':
return CYAN;
case '6':
return YELLOW;
case '7':
return WHITE;
case '8':
return ORANGE; 
default:
return BLACK;
}

}

void placeOilDrum() {
tft.drawBitmap(START_POS + 10, 6, epd_bitmap_OilDrum_12x12, 12, 12, BLUE);
}

//This places 3 different ladders on the screen. placeLadder is called a number of times as it just
//displays a single 8x8 piece of ladder
void placeLadders() {
placeLadder(10, 32);    //(Y, X)
placeLadder(18, 32);
placeLadder(26, 32);

placeLadder(21, 120);
placeLadder(13, 120);

placeLadder(42, 48);
placeLadder(50, 48);
}

void placeLadder(int16_t yPos, int16_t xPos) {
tft.drawBitmap(yPos, xPos, epd_bitmap_Ladder_8x8, 8, 8, CYAN);
}

//Girders are a little more complex to place. They are made slanted like in the original video game
//by adjusting the Y axis every few sprite placements.
void setUpGirders() {

//Bottom girder #1
//Y, X (0,0 is bottom left) ^,>
int16_t y = START_POS;
//Length of Girder
//for (int16_t x=0; x < 20; x+=1) {
  for (int16_t x=0; x < 29; x+=1) {
tft.drawBitmap(y, x * 8, epd_bitmap_Girder_8x8, 8, 8, RED);
//if (x == 8 || x == 11 || x == 14 || x == 17) {y = y + 1;}
if (x == 8 || x == 12 || x == 16 || x == 20 || x == 24 || x == 28) {y = y + 1 ;}
}

//Next girder #2
y = 34;
for (int16_t x=1; x < 19; x+=1) {
tft.drawBitmap(y, x * 8, epd_bitmap_Girder_8x8, 8, 8, RED);
//if (x == 5 || x == 8 || x == 14 || x == 17 || x == 24 ) {y = y - 1;}
if (x == 5 || x == 8 || x == 12 || x == 16 || x == 20 || x == 24 || x == 28) {y = y - 1;}
}

//Next girder #3
y = 60;
for (int16_t x=1; x < 29; x+=1) {
tft.drawBitmap(y, x * 8, epd_bitmap_Girder_8x8, 8, 8, RED);
if (x == 8 || x == 12 || x == 16 || x == 20 || x == 24 || x == 28) {y = y + 1;}
}

//Next girder #4
y = 90;
for (int16_t x=1; x < 14; x+=1) {
tft.drawBitmap(y, x * 8, epd_bitmap_Girder_8x8, 8, 8, RED);
//if (x == 8 || x == 11 || x == 14 || x == 17 || x == 21 || x == 24) {y = y - 1;}
if (x == 8 || x == 12 || x == 16 || x == 20 || x == 24 || x == 28) {y = y - 1;}
}

//Princess platform
tft.drawBitmap(START_POS + 47, 140, epd_bitmap_Girder_8x8, 8, 8, RED);
tft.drawBitmap(START_POS + 47, 148, epd_bitmap_Girder_8x8, 8, 8, RED);

}