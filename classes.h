/* classes.h file */

class GeneralControl {
private:

  int PotData = 0;

public:


  void begin(int VariableResistor, int Led1, int Led2, int IRSensorPin) {
    pinMode(VariableResistor, INPUT);
    pinMode(Led1, OUTPUT);
    pinMode(Led2, OUTPUT);
    pinMode(IRSensorPin, INPUT);
  }

  int ReadPotentiometer(int VariableResistor) {
    PotData = analogRead(VariableResistor);
    return PotData;
  }

  int PotentiometerData() {
    PotReading = analogRead(A0);
    PotFixedData = map(PotReading, 0, 1023, -1, (Maximum_Mills / 10) + 1);
    Serial.println(PotFixedData);
    if(PotFixedData == -1){
      PotFixedData = 0;
    }

    if(PotFixedData == 21){
      PotFixedData = 20;
    }

    return PotFixedData;
  }

  void TurnLeds(int Led1, int Led2, bool TurnState) {
    digitalWrite(Led1, TurnState);
    digitalWrite(Led2, TurnState);
  }

  void FlashLeds(int Led1, int Led2, int Flashes, int TimeBetweenFlashing) {
    for (int i = 0; i < Flashes; i++) {
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, LOW);
      delay(TimeBetweenFlashing);
      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, HIGH);
      delay(TimeBetweenFlashing);

    }
  }
};

class PumpsControl {

public:

  void begin(int Pump1, int Pump2, int Pump3) {
    pinMode(Pump1, OUTPUT);
    pinMode(Pump2, OUTPUT);
    pinMode(Pump3, OUTPUT);

    digitalWrite(Pump1, HIGH);
    digitalWrite(Pump2, HIGH);
    digitalWrite(Pump3, HIGH);
  }

  void open(int PumpPin, String RelayStatus) {
    if (RelayStatus == "NO") {
      digitalWrite(PumpPin, LOW);
      Serial.print("Active");   // because it is a Low Active Relay

    } else if (RelayStatus == "NC") {
      digitalWrite(PumpPin, HIGH);
    }
  }

  void close(int PumpPin, String RelayStatus) {
    if (RelayStatus == "NO") {
      digitalWrite(PumpPin, HIGH);

    } else if (RelayStatus == "NC") {
      digitalWrite(PumpPin, LOW);
    }
  }
};

class DisplayClass {

private:

  String WelcomeText1 = "Cocktail Mixer";
  String WelcomeText2 = "By Mutaz Lafi";

  String StartText1 = "Choose Mode";
  String StartText2 = "Auto/Selection";

public:

  void begin() {
    lcd.begin();

    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print(WelcomeText1);
    delay(600);
    lcd.clear();

    lcd.setCursor(1, 0);
    lcd.print(WelcomeText2);
    delay(600);
    lcd.clear();
  }

  void StartScreen() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(StartText1);
    lcd.setCursor(0, 1);
    lcd.print(StartText2);
    delay(4000);
  }
};

class PushButtonsClass {
public:

  int ConfirmPushButtonRead = 0;
  int StartPushButtonRead = 0;

  void begin() {
    pinMode(Confirm_Button, INPUT);
    pinMode(Start_Push_Button, INPUT);
  }

  int CheckConfirmButton() {
    ConfirmPushButtonRead = digitalRead(Confirm_Button);
    Serial.println(ConfirmPushButtonRead);
    delay(500);
    if (ConfirmPushButtonRead == LOW) {
      return 0;
    } else if (ConfirmPushButtonRead == HIGH) {
      return 1;
    }
  }

  int CheckStartButton() {
    StartPushButtonRead = digitalRead(Start_Push_Button);
    Serial.println(StartPushButtonRead);
    delay(500);
    if (StartPushButtonRead == LOW) {
      return 0;
    } else if (StartPushButtonRead == HIGH) {
      return 1;
    }
  }
};