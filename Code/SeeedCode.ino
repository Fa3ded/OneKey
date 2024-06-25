const int buttonPin = 2; // the pin that the pushbutton is attached to
bool buttonState = HIGH; // the current reading from the input pin
bool lastButtonState = HIGH; // the previous reading from the input pin

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers

unsigned long buttonPressTime = 0;
unsigned long buttonReleaseTime = 0;
unsigned long lastButtonPressTime = 0;
unsigned long doublePressThreshold = 400; // time window for detecting double press

enum ButtonAction {
  NONE,
  SINGLE_PRESS,
  DOUBLE_PRESS,
  HOLD
};

ButtonAction action = NONE;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Check if the button state has changed (due to noise or actual press/release)
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // reset the debouncing timer
  }

  // If the reading is stable for a certain amount of time, consider it as a valid change
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        buttonPressTime = millis();
        action = NONE;
      } else {
        buttonReleaseTime = millis();
        unsigned long pressDuration = buttonReleaseTime - buttonPressTime;

        if (pressDuration >= 500) {
          action = HOLD;
        } else {
          if ((millis() - lastButtonPressTime) <= doublePressThreshold) {
            action = DOUBLE_PRESS;
          } else {
            action = SINGLE_PRESS;
            lastButtonPressTime = millis();
          }
        }
      }
    }
  }

  // Output action after appropriate delay for detecting double press
  if (action == SINGLE_PRESS && (millis() - lastButtonPressTime) > doublePressThreshold) {
    Serial.println("ONE");
    action = NONE; // reset action
  } else if (action == DOUBLE_PRESS) {
    Serial.println("TWO");
    action = NONE; // reset action
  } else if (action == HOLD) {
    Serial.println("HOLD");
    action = NONE; // reset action
  }

  lastButtonState = reading;
}
