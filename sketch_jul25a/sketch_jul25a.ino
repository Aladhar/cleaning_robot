int Reading;
String message = "Reading =";
float dec = 1.5;
boolean tf = true;

void setup() {
  // put your setup code here, to run once:
  pinMode (A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Reading = analogRead(A1); 
  Serial.print(message); Serial.println(Reading);
 
}
