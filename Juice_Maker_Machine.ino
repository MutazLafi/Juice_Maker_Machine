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

int StartState = 0;

int AutoModeVariableResistorReading = 0;

int AutoModeSelectionState = 0;

int IRState = 0;

int IRSensorRead = 0;


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

    VariableResistorReading = map(analogRead(A0), 0, 20, 0, 1023);
    Serial.print(VariableResistorReading);
    Serial.print("h");

    if (VariableResistorReading < 512) {
      ModeState = 1;
    } else if (VariableResistorReading > 512) {
      ModeState = 2;
    }
    StartScreenState = 1;
  }



  if (ModeState == 1) {

    Serial.print("in Auto Mode");

    AutoModeVariableResistorReading = General.ReadPotentiometer(PotentiometerPin);
    AutoModeSelectionState = map(AutoModeVariableResistorReading, 0, 1023, 0, 4);
    IRSensorRead = digitalRead(IR_Pin);

AutoModeSelectionArea:

    if (AutoModeSelectionState == 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Orange");
      if (IRSensorRead == LOW) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Running...");
        Pumps.open(PumpPin1, "NO");
        IRState = 1;
      }

      if (IRSensorRead == HIGH && IRState == 1) {
        Pumps.close(PumpPin1, "NO");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DONE :)");
        IRState = 0;
      }
    }

    if (AutoModeSelectionState == 2) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mango");
      if (IRSensorRead == LOW) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Running...");
        Pumps.open(PumpPin2, "NO");
        IRState = 1;
      }

      if (IRSensorRead == HIGH && IRState == 1) {
        Pumps.close(PumpPin2, "NO");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DONE :)");
        IRState = 0;
      }
    }

    if (AutoModeSelectionState == 3) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Strawberry");
      if (IRSensorRead == LOW) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Running...");
        Pumps.open(PumpPin3, "NO");
        IRState = 1;
      }

      if (IRSensorRead == HIGH && IRState == 1) {
        Pumps.close(PumpPin3, "NO");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DONE :)");
        IRState = 0;
      }
    }

    // Auto Mode
  } else if (ModeState == 2) {
    // Selection Mode


    Serial.print("in Selection Mode");

    VariableResistorReading = General.ReadPotentiometer(PotentiometerPin);
    SelectionState = map(VariableResistorReading, 1023, 0, 4, 0);


SelectionArea:
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
      FinalSelection = map(VariableResistorReading, 1023, 0, 3.5, 0);
    }
    Serial.println("Orange Mills:");
    Serial.print(Orange_Juice_Mills);
    if (FinalSelection == 1) {
      while (!PushButtons.CheckConfirmButton() == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Orange: ");
        VariableResistorData = General.PotentiometerData();
        lcd.print(Orange_Juice_Mills);
        lcd.print(" M");
        Orange_Juice_Mills = VariableResistorData * 10;
      }
      FinalSelection = 0;
      goto SelectionArea;
    }



    if (FinalSelection == 2) {
      while (!PushButtons.CheckConfirmButton() == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mango: ");
        VariableResistorData = General.PotentiometerData();
        lcd.print(Mango_Juice_Mills);
        lcd.print(" M");
        Mango_Juice_Mills = VariableResistorData * 10;
      }
      FinalSelection = 0;
      goto SelectionArea;
    }

    if (FinalSelection == 3) {
      while (!PushButtons.CheckConfirmButton() == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Strawberry: ");
        VariableResistorData = General.PotentiometerData();
        lcd.print(Strawberry_Juice_Mills);
        lcd.print(" M");
        Strawberry_Juice_Mills = VariableResistorData * 10;
      }
      FinalSelection = 0;
      goto SelectionArea;
    }

    StartPushButtonRead = PushButtons.CheckStartButton();
    Serial.print("Start:");
    Serial.print(StartPushButtonRead);

    if (StartPushButtonRead == 1 && Start_Push_Button_State == 0) {
      Start_Push_Button_State = 1;
    }
    if (StartPushButtonRead == 1 && Start_Push_Button_State == 1) {
      Start_Push_Button_State == 2;
    }

    if (Start_Push_Button_State == 1 && StartState == 0) {
      delay(1000);
      while (!StartPushButtonRead == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Start??");
        delay(700);
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Running...");
      delay(700);
      if (Orange_Juice_Mills + Strawberry_Juice_Mills + Mango_Juice_Mills > 200) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Error:");
        delay(600);
        lcd.setCursor(0, 1);
        lcd.print("Than 200 M");
        Serial.print("Error");
        delay(1500);

        return;
      }
      Pumps.open(PumpPin1, "NO");
      delay(1);
      Pumps.close(PumpPin1, "NO");

      Pumps.open(PumpPin2, "NO");
      delay(1);
      Pumps.close(PumpPin2, "NO");

      Pumps.open(PumpPin3, "NO");
      delay(1);
      Pumps.close(PumpPin3, "NO");
      delay(600);

      Start_Push_Button_State = 0;
      ModeState = 0;
    }
  }
}
