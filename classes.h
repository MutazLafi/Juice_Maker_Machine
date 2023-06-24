/* classes.h file */

class GeneralControl {
private:

  int PotData = 0;

public:


  void begin(int VariableResistor, int Led1, int Led2) {
    pinMode(VariableResistor, INPUT);
    pinMode(Led1, OUTPUT);
    pinMode(Led2, OUTPUT);
  }

  int ReadPotentiometer(int VariableResistor) {
    PotData = analogRead(VariableResistor);
    return PotData;
  }

  int PotentiometerData() {
    PotReading = analogRead(A0);
    Serial.println(PotFixedData);
    PotFixedData = map(PotReading, 0, 1023, -1, (Maximum_Mills) + 1);
    Serial.println(PotFixedData);
    return PotFixedData;
  }
};

class PumpsControl {

public:

  void begin(int Pump1, int Pump2, int Pump3) {
    pinMode(Pump1, OUTPUT);
    pinMode(Pump2, OUTPUT);
    pinMode(Pump3, OUTPUT);
  }

  void open(int PumpPin, String RelayStatus) {
    if (RelayStatus == "NO") {
      digitalWrite(PumpPin, HIGH);

    } else if (RelayStatus == "NC") {
      digitalWrite(PumpPin, LOW);
    }
  }

  void close(int PumpPin, String RelayStatus) {
    if (RelayStatus == "NO") {
      digitalWrite(PumpPin, LOW);

    } else if (RelayStatus == "NC") {
      digitalWrite(PumpPin, HIGH);
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
    pinMode(ConfirmPushButtonRead, INPUT);
    pinMode(StartPushButtonRead, INPUT);
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
    if (Start_Push_Button == LOW) {
      return 0;
    } else if (StartPushButtonRead == HIGH) {
      return 1;
    }
  }
};