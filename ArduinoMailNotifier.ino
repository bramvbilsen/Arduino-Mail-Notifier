// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String topText = "";
String bottomText = "";
bool done = false;
bool quit = false;
int endLineCount = 0;

void setup() {
  Serial.begin(9600);
  Serial.write(1);
  lcd.begin(16, 2);
  lcd.print("...Connecting...");
  lcd.setCursor(0, 1);
  lcd.print("----------------");
  delay(1000);
}
 
void loop() {
  if (done) {
    while (Serial.read() > -1) {}
    endLineCount = 0;
    done = false;
    quit = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(topText);
    lcd.setCursor(0, 1);
    lcd.print(bottomText);
    topText = ""; bottomText = "";
    Serial.write(1);
    delay(1000);
  } else if (quit == true) {
    while (Serial.read() > -1) {}
    endLineCount = 0;
    done = false;
    quit = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("...Connecting...");
    lcd.setCursor(0, 1);
    lcd.print("----------------");
    topText = ""; bottomText = "";
    Serial.write(1);
    delay(1000);
  }
}

void serialEvent() {
  Serial.write(0); //PYTHON DONT GIVE ME ANYTHING NEW
  while (Serial.available()) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c == '\n') {
        endLineCount++;
        if (topText == "-1") {
          quit = true;
        }
      }
      if (endLineCount == 0 && c != '\n') {
        topText += c;
      } else if (endLineCount == 1 && c != '\n') {
        bottomText += c;
      }
      if (endLineCount == 2) {
        done = true;
      }
    }
  }
}

