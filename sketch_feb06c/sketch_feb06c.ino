const int buttonPin = A0;
const int ledPin = 13;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  analogRead(buttonPin);

 int val = analogRead(buttonPin);  // read the input pin
  Serial.println(val);          // debug value
}
