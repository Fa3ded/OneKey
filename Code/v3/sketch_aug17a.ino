#include <Mouse.h>
#include <Keyboard.h>

const int buttonPin = 1;
bool buttonState = false;
bool lastButtonState = HIGH;
unsigned long buttonPressStart = 0;
unsigned long buttonReleaseTime = 0;
String morseCode = "";

const unsigned long dotDuration = 300;  // Max duration for a dot
const unsigned long debounceDuration = 50;  // Debounce time
const unsigned long dashDuration = 1000;  // Time to wait for the next character

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Button press detected
  if (buttonState == LOW && lastButtonState == HIGH && (millis() - buttonReleaseTime) > debounceDuration) {
    buttonPressStart = millis();
  }

  // Button release detected
  if (buttonState == HIGH && lastButtonState == LOW && (millis() - buttonPressStart) > debounceDuration) {
    unsigned long pressDuration = millis() - buttonPressStart;

    if (pressDuration < dotDuration) {
      morseCode += ".";  // Short press = dot
    } else {
      morseCode += "-";  // Long press = dash
    }

    buttonReleaseTime = millis();  // Record when the button was released
  }

  // If a second has passed since the last button release, process the Morse code
  if (morseCode.length() > 0 && (millis() - buttonReleaseTime) > dashDuration) {
    typeMorseCharacter(morseCode);
    morseCode = "";  // Clear the code after processing
  }

  lastButtonState = buttonState;
}

void typeMorseCharacter(String code) {
  if (code == ".-") Keyboard.press('A');
  else if (code == "-...") Keyboard.press('B');
  else if (code == "-.-.") Keyboard.press('C');
  else if (code == "-..") Keyboard.press('D');
  else if (code == ".") Keyboard.press('E');
  else if (code == "..-.") Keyboard.press('F');
  else if (code == "--.") Keyboard.press('G');
  else if (code == "....") Keyboard.press('H');
  else if (code == "..") Keyboard.press('I');
  else if (code == ".---") Keyboard.press('J');
  else if (code == "-.-") Keyboard.press('K');
  else if (code == ".-..") Keyboard.press('L');
  else if (code == "--") Keyboard.press('M');
  else if (code == "-.") Keyboard.press('N');
  else if (code == "---") Keyboard.press('O');
  else if (code == ".--.") Keyboard.press('P');
  else if (code == "--.-") Keyboard.press('Q');
  else if (code == ".-.") Keyboard.press('R');
  else if (code == "...") Keyboard.press('S');
  else if (code == "-") Keyboard.press('T');
  else if (code == "..-") Keyboard.press('U');
  else if (code == "...-") Keyboard.press('V');
  else if (code == ".--") Keyboard.press('W');
  else if (code == "-..-") Keyboard.press('X');
  else if (code == "-.--") Keyboard.press('Y');
  else if (code == "--..") Keyboard.press('Z');

  delay(100);  // Short delay to ensure the key press is registered
  Keyboard.releaseAll();  // Release all keys
}