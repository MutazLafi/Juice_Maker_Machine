#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pins //

#define IR_Pin 2

#define LED_1 3
#define LED_2 4

#define Push_Button1 5
#define Push_Button2 6
#define Push_Button3 7
#define Start_Push_Button  8

#define PotentiometerPin A0

#define PumpPin1 8
#define PumpPin2 9
#define PumpPin3 10

// Variables//

const int Maximum_Mills = 200;  // Change it as the Cup is


int VariableResistorData = 0;

int pushButtonsState = 0;  // for pushButtons 1,2 ,3 or 4 for start PushButton

int Start_Push_Button_State = 0;

int Orange_Juice_Mills = 0;
int Mango_Juice_Mills = 0;
int Strawberry_Juice_Mills = 0;

int StartScreenState = 0;


int PotReading = 0;

int PotFixedData = 0;

//Objects//

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DEBUG  // Undefine it to hide Serial Debuggging

// classes.h file for classes
#include "classes.h"

GeneralControl General;
PumpsControl Pumps;
DisplayClass Display;
PushButtonsClass PushButtons;

void setup() {

#ifdef DEBUG
  Serial.begin(9600);
#endif

  General.begin(PotentiometerPin, LED_1, LED_2);

  Pumps.begin(PumpPin1, PumpPin2, PumpPin3);

  PushButtons.begin();

  Display.begin();
}


void loop() {

  VariableResistorData = General.PotentiometerData();
  if (StartScreenState == 0 || pushButtonsState == 0) {
    Display.StartScreen();
    StartScreenState = 1;
  }


  if (PushButtons.CheckButton1() == 1) {
    pushButtonsState = 1;
    Serial.print("1");
  }

  if (PushButtons.CheckButton2() == 1) {
    pushButtonsState = 2;
  }

  if (PushButtons.CheckButton3() == 1) {
  }

  if (pushButtonsState == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Orange: ");
    VariableResistorData = General.PotentiometerData();
    Orange_Juice_Mills = VariableResistorData;
    lcd.print(Orange_Juice_Mills * 10);
  }

  if (pushButtonsState == 2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mango: ");
    VariableResistorData = General.PotentiometerData();
    Mango_Juice_Mills = VariableResistorData;
    lcd.print(Mango_Juice_Mills * 10);
  }

  if (pushButtonsState == 3) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Strawberry: ");
    VariableResistorData = General.PotentiometerData();
    Strawberry_Juice_Mills = VariableResistorData;
    lcd.print(Strawberry_Juice_Mills * 10);
  }

  if(pushButtonsState == 4 && Start_Push_Button_State == 0){
    Start_Push_Button_State = 1;
  }else if(pushButtonsState == 4 && Start_Push_Button_State == 1){
    Start_Push_Button_State == 2;
  }

  if(Start_Push_Button_State == 1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Start??");
  }else if(Start_Push_Button == 2){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Running...");
    Pumps.open(PumpPin1,"NO");
    delay(1);
    Pumps.open(PumpPin2,"NO");
    delay(1);
    Pumps.open(PumpPin3,"NO");
    delay(1);
    Start_Push_Button_State = 0;
    pushButtonsState = 0;
  }

  

}
