#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pins //

#define IR_Pin 2

#define LED_1 3
#define LED_2 4

#define Confirm_Button 5

#define Start_Push_Button 6

#define PotentiometerPin A0

#define PumpPin1 8
#define PumpPin2 9
#define PumpPin3 10

// Variables//

const int Maximum_Mills = 200;  // Change it as the Cup is


int VariableResistorData = 0;

int VariableResistorReading = 0;

int ModeState = 0;

int Confirm_Push_Button_State = 0;

int Start_Push_Button_State = 0;

int Orange_Juice_Mills = 0;
int Mango_Juice_Mills = 0;
int Strawberry_Juice_Mills = 0;

int StartScreenState = 0;

int SelectionState = 0;

int FinalSelection = 0;

int PotReading = 0;

int PotFixedData = 0;

int StartPushButtonRead = 0;

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

  if (StartScreenState == 0 || ModeState == 0) {
    Display.StartScreen();

    VariableResistorReading = General.ReadPotentiometer(PotentiometerPin);

    if (VariableResistorReading < 512) {
      ModeState = 1;
    } else if (VariableResistorReading > 512) {
      ModeState = 2;
    }
    StartScreenState = 1;
  }



  if (ModeState == 1) {
  
    // Auto Mode
  } else if (ModeState == 2) {
    // Selection Mode




    VariableResistorReading = General.ReadPotentiometer(PotentiometerPin);
    SelectionState = map(VariableResistorReading, 1023, 0, 4, 0);

    StartPushButtonRead = PushButtons.CheckStartButton();

    if (SelectionState == 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Orange");
    }

    if (SelectionState == 2) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mango");
    }

    if (SelectionState == 3) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Strawberry");
    }

    if (PushButtons.CheckConfirmButton() == 1) {
      VariableResistorReading = General.ReadPotentiometer(PotentiometerPin);
      FinalSelection = map(VariableResistorReading, 1023, 0, 4, 0);
      
    }


    if (FinalSelection == 1) {
      while(! PushButtons.CheckConfirmButton() == 1){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Orange: ");
      VariableResistorData = General.PotentiometerData();
      Orange_Juice_Mills = VariableResistorData;
      lcd.print(Orange_Juice_Mills);
      }
    }

    if (FinalSelection == 2) {
      while(! PushButtons.CheckConfirmButton() == 1){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mango: ");
      VariableResistorData = General.PotentiometerData();
      Mango_Juice_Mills = VariableResistorData;
      lcd.print(Mango_Juice_Mills);
      }
    }

    if (FinalSelection == 3) {
      while(! PushButtons.CheckConfirmButton() == 1){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Strawberry: ");
      VariableResistorData = General.PotentiometerData();
      Strawberry_Juice_Mills = VariableResistorData;
      lcd.print(Strawberry_Juice_Mills);
      }
    }

    if (StartPushButtonRead == 1 && Start_Push_Button_State == 0) {
      Start_Push_Button_State = 1;
    } else if (StartPushButtonRead == 1 && Start_Push_Button_State == 1) {
      Start_Push_Button_State == 2;
    }

    if (Start_Push_Button_State == 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Start??");
    } else if (Start_Push_Button == 2) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Running...");
      Pumps.open(PumpPin1, "NO");
      delay(1);
      Pumps.open(PumpPin2, "NO");
      delay(1);
      Pumps.open(PumpPin3, "NO");
      delay(1);
      Start_Push_Button_State = 0;
      ModeState = 0;
    }
  }
 
}

