void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(2) == LOW) {
    Serial.println("CLICK");
    delay(100); // debounce delay
  }
}

