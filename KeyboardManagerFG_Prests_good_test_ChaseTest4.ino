/**
 * This example shows how to use the matrix keyboard support that's built into IoAbstraction,
 * it can be used out the box with either a 3x4 or 4x4 keypad, but you can modify it to use
 * any matrix keyboard quite easily.
 * It just sends the characters that are typed on the keyboard to Serial. The keyboard in This
 * example is connected directly to Arduino pins, but could just as easily be connected over
 * a PCF8574, MCP23017 or other IoAbstraction.
 */

#include <Wire.h>
#include <IoAbstraction.h>
#include<TaskManagerIO.h>
#include <KeyboardManagerFG.h>

#include "FastLED.h"
#define DATA_PIN 2
#define LED_TYPE WS2813
#define COLOR_ORDER GRB
#define NUM_LEDS 79
#define BRIGHTNESS 30
#define UPDATES_PER_SECOND 5 
#define FRAMES_PER_SECOND  120

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


//
// We need to make a keyboard layout that the manager can use. choose one of the below.
// The parameter in brackets is the variable name.
//
//MAKE_KEYBOARD_LAYOUT_3X4(keyLayout)
//MAKE_KEYBOARD_LAYOUT_4X4(keyLayout)
MAKE_KEYBOARD_LAYOUT_3X8(keyLayout)


//
// We need a keyboard manager class too
//
MatrixKeyboardManager keyboard;

// this examples connects the pins directly to an arduino but you could use
// IoExpanders or shift registers instead.
IoAbstractionRef arduinoIo = ioUsingArduino();

//  Functions for LEDS  Fastlight and Neopixel

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
//  Loads color palette(?)    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
        


//  Start key press funcions

void RedFunctionFor1() {
   // take action when 1 typed on keypad
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
}    


void OrangeFunctionFor2() {
   // take action when 2 typed on keypad
   fill_solid( leds, NUM_LEDS, CRGB::Orange);
   FastLED.show();
}
void YellowFunctionFor3() {
   // take action when 3 typed on keypad
   fill_solid( leds, NUM_LEDS, CRGB::Yellow);
   FastLED.show();   
}
void GreenFunctionFor4() {
   // take action when 4 typed on keypad
   fill_solid( leds, NUM_LEDS, CRGB::Green);
   FastLED.show();
}
void CyanFunctionFor5() {
   // take action when 3 typed on keypad
   fill_solid( leds, NUM_LEDS, CRGB::Cyan);
   FastLED.show();      
}
void BlueFunctionFor6() {
   // take action when 6 typed on keypad
   fill_solid( leds, NUM_LEDS, CRGB::Blue);
   FastLED.show();      
}
void PurpleFunctionFor7() {
   // take action when 7 typed on keypad
   fill_solid( leds, NUM_LEDS, CRGB::Purple);
   FastLED.show();
}
void MagentaFunctionFor8() {
   // take action when 8 typed on keypad
   fill_solid( leds, NUM_LEDS, CRGB::Magenta);
   FastLED.show();      
}
void WhiteFunctionFor9() {
   // take action when 9 typed on keypad
   fill_solid( leds, NUM_LEDS, CRGB::White);
   FastLED.show();      
}
void Pre1FunctionForX() {
   // take action when X typed on keypad
   fill_solid( leds, NUM_LEDS, CRGB::Pink);
   FastLED.show();
}
void Pre2FunctionFor0() {
   // take action when 0 typed on keypad
   fill_solid( leds, NUM_LEDS, CRGB::Aqua);
   FastLED.show();      
}
void Pre3FunctionForY() {
   // take action when Y typed on keypad
   fill_solid( leds, NUM_LEDS, CRGB::Red);
   FastLED.show();      
}
//
// We need a class that extends from KeyboardListener. this gets notified when
// there are changes in the keyboard state.
//
class MyKeyboardListener : public KeyboardListener {
public:
    void keyPressed(char key, bool held) override {
//  Testing key presses       
        Serial.print("Key ");
        Serial.print(key);
        
        Serial.print(" is pressed, held = ");
        Serial.println(held);


//Start switch case for key press
    switch(key) {
        case '1':
            RedFunctionFor1();
        Serial.print("Red ");      
   taskManager.cancelTask(RedFunctionFor1);        
            break;
            
        case '2':
             OrangeFunctionFor2();
        Serial.print("Orange ");
      
             break;
        case '3':
             YellowFunctionFor3();
        Serial.print("Yellow ");
             
             break;       

        case '4':
             GreenFunctionFor4();
        Serial.print("Green ");
             
             break;
        case '5':
             CyanFunctionFor5();
        Serial.print("Cyan ");
             
             break;
        case '6':
             BlueFunctionFor6();
        Serial.print("Blue ");
             
             break;
        case '7':
             PurpleFunctionFor7();
        Serial.print("Purple ");
             
             break;
        case '8':
             MagentaFunctionFor8();
        Serial.print("Magenta ");
             
             break;
        case '9':
             WhiteFunctionFor9();
        Serial.print("White ");
             
             break;
        case 'X':
             Pre1FunctionForX();
        Serial.print("Preset 1 ");
             
             break;
        case '0':
             Pre2FunctionFor0();
        Serial.print("Preset 2 ");
             
             break;
        case 'Y':
             Pre3FunctionForY();
        Serial.print("Preset 3 ");
             
             break;

//  Start Key press for Chases           
        }
    }

    void keyReleased(char key) override {   } 

    
} myListener;

void setup() {
    while(!Serial);
    Serial.begin(115200);

    keyLayout.setRowPin(0, 10);
    keyLayout.setRowPin(1, 9);
    keyLayout.setRowPin(2, 8);
    keyLayout.setRowPin(3, 7);
    keyLayout.setRowPin(4, 6);
    keyLayout.setRowPin(5, 5);
    keyLayout.setRowPin(6, 4);
    keyLayout.setRowPin(7, 3);
    
    keyLayout.setColPin(0, 13);
    keyLayout.setColPin(1, 12);
    keyLayout.setColPin(2, 11);

    // create the keyboard mapped to arduino pins and with the layout chosen above.
    // it will callback our listener
    keyboard.initialise(arduinoIo, &keyLayout, &myListener);

    // start repeating at 850 millis then repeat every 350ms
    keyboard.setRepeatKeyMillis(850, 350);

    Serial.println("Keyboard is initialised!");
   
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
   
    currentPalette = currentPalette = myRedWhiteBluePalette_p;
    currentBlending = LINEARBLEND;
    
uint8_t taskId = taskManager.scheduleFixedRate(100, RedFunctionFor1);;
uint8_t taskId = taskManager.scheduleFixedRate(100, OrangeFunctionFor2);;

}

void loop() {
    // as this indirectly uses taskmanager, we must include this in loop.
    taskManager.runLoop();

  
}

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Blue,
    CRGB::Red, // 'white' is too bright compared to red and blue
    CRGB::White,
    CRGB::Blue,
    
    CRGB::Blue,
    CRGB::White,
    CRGB::Red,
    CRGB::Red,
    
    CRGB::White,
    CRGB::White,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Red,
    CRGB::Red,
    CRGB::Red,
    CRGB::Blue,
};
