int buzzerPin = 9;    // Buzzer connected to pin 9
int ledPin = 13;      // LED connected to pin 13

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Countdown from 10 to 1
  for (int i = 10; i >= 1; i--) {
    Serial.println(i);         // Print countdown to the Serial Monitor
    digitalWrite(ledPin, HIGH);  // Turn on LED for a visual cue
    delay(500);                // LED stays on for 500 ms
    digitalWrite(ledPin, LOW);  // Turn off LED
    delay(500);                // 500 ms off
  }
  
  // Sound the buzzer when countdown finishes
  tone(buzzerPin, 1000, 1000);  // Play a 1000 Hz tone for 1 second
  delay(2000);  // Pause before restarting countdown
}
