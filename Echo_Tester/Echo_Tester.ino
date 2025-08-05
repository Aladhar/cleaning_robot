const int trigPin = 4;
const int echoPin = 2;

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

int motor1Ena = 11;
int motor1pin1 = 10;
int motor1pin2 = 9;


int motor2pin1 = 6;
int motor2pin2 = 5;
int motor2Ena = 3;

template <typename T>
Print& operator<<(Print& printer, T value)
{
    printer.print(value);
    return printer;
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor1Ena, OUTPUT);  
  pinMode(motor2Ena, OUTPUT);
  //Initialize all to be low.
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void loop() {
  // Clears the trigPin condition
  //Pulse with Echo. 10 microsecond pulse with trigPin.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = (duration * 0.0343) / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial << "Distance is: " << distance << "cm.\n";

  //if the distance is <=5 go backwards
  if  (distance <= 5){
    backwards();
    delay(2000);
  }
  else if (distance > 5 && distance < 20){
    left();
    delay(5000);
  }
  else{
    forward();
    delay(5000);
  }
}

void forward() {
  Serial.println("Going Forward");
  analogWrite(motor1Ena, 255);
  analogWrite(motor2Ena, 255);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

//Make a forward, stop, backwards, left, right, and if statement with those things. add delays in the if statement. 

void StopMotors() {
  Serial.println("Stopping Motors...");
  //stop all functions
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void backwards() {
  Serial.println("Driving Backwards....");
  analogWrite(motor1Ena, 255);
  analogWrite(motor2Ena, 255);
  
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void left() {
  Serial.println("Turning Left....");
  analogWrite(motor1Ena, 255);
  analogWrite(motor2Ena, 255);
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}


void right() {
  Serial.println("Turning Right....");
  analogWrite(motor1Ena, 255);
  analogWrite(motor2Ena, 255);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}
