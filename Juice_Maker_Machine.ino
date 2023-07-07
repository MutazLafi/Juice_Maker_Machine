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

int Pineapple_Juice_Mills = 0;
int Mango_Juice_Mills = 0;
int Apple_Juice_Mills = 0;

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

int FlashState = 0;


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

  General.begin(PotentiometerPin, LED_1, LED_2, IR_Pin);

  Pumps.begin(PumpPin1, PumpPin2, PumpPin3);

  PushButtons.begin();

  Display.begin();

  General.TurnLeds(LED_1, LED_2, true);
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
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("in Auto Mode");
      delay(1000);
    } else if (VariableResistorReading > 512) {
      ModeState = 2;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Selection Mode");
      delay(1000);
    }
    StartScreenState = 1;
  }



  if (ModeState == 1) {

    Serial.print("in Auto Mode");


    AutoModeVariableResistorReading = General.ReadPotentiometer(PotentiometerPin);
    AutoModeSelectionState = map(AutoModeVariableResistorReading, 0, 1023, 0, 4);
    IRSensorRead = digitalRead(IR_Pin);

    if (AutoModeSelectionState == 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pineapple");
      delay(200);
      if (IRSensorRead == LOW) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Running...");
        if (FlashState == 0) {
          General.FlashLeds(LED_1, LED_2, 4, 500);
          FlashState = 1;
        }

        Pumps.open(PumpPin1, "NO");
        IRState = 1;
      }

      if (IRSensorRead == HIGH && IRState == 1) {
        Pumps.close(PumpPin1, "NO");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DONE :)");
        delay(1700);
        IRState = 0;
      }
    }

    if (AutoModeSelectionState == 2) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mango");
      delay(200);
      if (IRSensorRead == LOW) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Running...");
        if (FlashState == 0) {
          General.FlashLeds(LED_1, LED_2, 4, 500);
          FlashState = 1;
        }

        Pumps.open(PumpPin2, "NO");
        IRState = 1;
      }

      if (IRSensorRead == HIGH && IRState == 1) {
        Pumps.close(PumpPin2, "NO");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DONE :)");
        delay(1700);
        IRState = 0;
      }
    }

    if (AutoModeSelectionState == 3) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Apple");
      delay(200);
      if (IRSensorRead == LOW) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Running...");
        if (FlashState == 0) {
          General.FlashLeds(LED_1, LED_2, 4, 500);
          FlashState = 1;
        }
        Pumps.open(PumpPin3, "NO");
        IRState = 1;
      }

      if (IRSensorRead == HIGH && IRState == 1) {
        Pumps.close(PumpPin3, "NO");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DONE :)");
        delay(1700);
        IRState = 0;
      }
    }

    // Auto Mode
  } else if (ModeState == 2) {
    // Selection Mode

    Serial.print("Confirm: ");
    Serial.print(PushButtons.CheckConfirmButton());
    Serial.print("in Selection Mode");


    VariableResistorReading = General.ReadPotentiometer(PotentiometerPin);
    SelectionState = map(VariableResistorReading, 1023, 1, 3, 0);


SelectionArea:
    switch (SelectionState) {

      case 1:

        if (PushButtons.CheckConfirmButton() == 1) {
          VariableResistorReading = General.ReadPotentiometer(PotentiometerPin);
          FinalSelection = map(VariableResistorReading, 1023, 0, 3, 0);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pineapple");

        break;
      case 2:

        if (PushButtons.CheckConfirmButton() == 1) {
          VariableResistorReading = General.ReadPotentiometer(PotentiometerPin);
          FinalSelection = map(VariableResistorReading, 1023, 0, 3, 0);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mango");

        break;
      case 3:

        if (PushButtons.CheckConfirmButton() == 1) {
          VariableResistorReading = General.ReadPotentiometer(PotentiometerPin);
          FinalSelection = map(VariableResistorReading, 1023, 0, 3, 0);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Apple");

        break;
    }


    if (PushButtons.CheckConfirmButton() == 1) {
      VariableResistorReading = General.ReadPotentiometer(PotentiometerPin);
      FinalSelection = map(VariableResistorReading, 1023, 0, 3, 0);
    }

    switch (FinalSelection) {

      case 1:
        while (!PushButtons.CheckConfirmButton() == 1) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Pineapple: ");
          VariableResistorData = General.PotentiometerData();
          lcd.print(Pineapple_Juice_Mills);
          lcd.print(" M");
          Pineapple_Juice_Mills = VariableResistorData * 10;
        }
        FinalSelection = 0;
        goto SelectionArea;

        break;

      case 2:
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

        break;

      case 3:

        while (!PushButtons.CheckConfirmButton() == 1) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Apple: ");
          VariableResistorData = General.PotentiometerData();
          lcd.print(Apple_Juice_Mills);
          lcd.print(" M");
          Apple_Juice_Mills = VariableResistorData * 10;
        }
        FinalSelection = 0;
        goto SelectionArea;

        break;
    }

    if (PushButtons.CheckConfirmButton() == 1) {
      VariableResistorReading = General.ReadPotentiometer(PotentiometerPin);
      FinalSelection = map(VariableResistorReading, 1023, 0, 3, 0);
    }

    StartPushButtonRead = PushButtons.CheckStartButton();

    Serial.print("Start:");
    Serial.print(StartPushButtonRead);

    if (StartPushButtonRead == 1 && Start_Push_Button_State == 0) {
      Start_Push_Button_State = 1;
    }

    if (Start_Push_Button_State == 1) {
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Running...");
      General.FlashLeds(LED_1, LED_2, 4, 500);
      if (Pineapple_Juice_Mills + Apple_Juice_Mills + Mango_Juice_Mills > 200) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Error:");
        delay(600);
        lcd.setCursor(0, 1);
        lcd.print("Than 200 M");
        Serial.print("Error");
        delay(1500);

        Start_Push_Button_State = 0;
        FlashState = 0;

        Pineapple_Juice_Mills = 0;
        Mango_Juice_Mills = 0;
        Apple_Juice_Mills = 0;

        goto SelectionArea;
      }
      Pumps.open(PumpPin1, "NO");
      delay((Pineapple_Juice_Mills * 0.025) * 1000);
      Pumps.close(PumpPin1, "NO");

      Pumps.open(PumpPin2, "NO");
      delay((Mango_Juice_Mills * 0.050) * 1000);
      Pumps.close(PumpPin2, "NO");

      Pumps.open(PumpPin3, "NO");
      delay((Apple_Juice_Mills * 0.025) * 1000);
      Pumps.close(PumpPin3, "NO");
      delay(600);

      Start_Push_Button_State = 0;
      ModeState = 0;

      Pineapple_Juice_Mills = 0;
      Mango_Juice_Mills = 0;
      Apple_Juice_Mills = 0;
    }
    FlashState = 0;
  }
}
