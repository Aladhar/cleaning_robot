int led = 13;
void setup() {
  pinMode(led, OUTPUT);
}
void loop() {
  digitalWrite(led, HIGH);  // LED on for 5 seconds
  delay(5000);
  digitalWrite(led, LOW);   // LED off for 3 seconds
  delay(3000);

  // Flashing 10 times at 1 Hz
  for (int i = 0; i < 10; i++) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
}
