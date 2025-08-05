
const int trigPin = 2;
const int echoPin = 3;

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


int motor1pin1 = 11;
int motor1pin2 = 10;

int motor2pin1 = 9;
int motor2pin2 = 8;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);

forward();

}





void forward() {
  Serial.print("Forward");
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

//Make a forward, stop, backwards, left, right, and if statement with those things. add delays in the if statement. 

void stopmove() {
  Serial.print("Stopmove");
  //stop all functions
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}



void backwards() {
  Serial.print("Backwards");
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void left() {
  Serial.print("Left");
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}


void right() {
  Serial.print("Right");
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}
