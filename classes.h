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
    Serial.println(PotFixedData);
    PotFixedData = map(PotReading, 0, 1023, -1, (Maximum_Mills / 10) + 1);
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

  String StartText = "Press a Button";

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
    lcd.print(StartText);
  }
};

class PushButtonsClass {
public:

  int ButtonRead1 = 0;
  int ButtonRead2 = 0;
  int ButtonRead3 = 0;
  int StartPushButtonRead = 0;

  void begin() {
    pinMode(Push_Button1, INPUT);
    pinMode(Push_Button2, INPUT);
    pinMode(Push_Button3, INPUT);
  }

  int CheckButton1() {
    ButtonRead1 = digitalRead(Push_Button1);
    Serial.println(ButtonRead1);
    delay(500);
    if (ButtonRead1 == LOW) {
      return 0;
    } else if (ButtonRead1 == HIGH) {
      return 1;
    }
  }

  int CheckButton2() {
    ButtonRead2 = digitalRead(Push_Button2);
    if (ButtonRead2 == LOW) {
      return 0;
    } else if (ButtonRead2 == HIGH) {
      return 1;
    }
  }

  int CheckButton3() {
    ButtonRead3 = digitalRead(Push_Button3);
    if (ButtonRead3 == LOW) {
      return 0;
    } else if (ButtonRead3 == HIGH) {
      return 1;
    }
  }

  int CheckStartButton() {
    if (StartPushButtonRead == LOW) {
      return 0;
    } else if (StartPushButtonRead == HIGH) {
      return 1;
    }
  }
};