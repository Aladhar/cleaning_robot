#include <AFMotor.h>

const uint8_t trigPin = 12;
const uint8_t echoPin = 13;

const uint8_t forwardSpeed = 160;
const uint8_t reverseSpeed = 180;
const uint8_t turnSpeed = 180;

const long obstacleDistanceCm = 20;
const long clearDistanceCm = 25;
const unsigned long echoTimeoutUs = 30000;
const unsigned long sensorReadIntervalMs = 60;
const unsigned long statusReportIntervalMs = 250;
const unsigned long stopPauseMs = 100;
const unsigned long reverseTimeMs = 500;
const unsigned long minTurnTimeMs = 350;
const unsigned long maxTurnTimeMs = 900;

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);

enum MotionState {
  DRIVING_FORWARD,
  PAUSING_BEFORE_REVERSE,
  REVERSING,
  TURNING
};

MotionState motionState = DRIVING_FORWARD;
bool turnLeftNext = true;
long lastDistanceCm = -1;
unsigned long lastSensorReadMs = 0;
unsigned long lastStatusReportMs = 0;
unsigned long stateStartedMs = 0;

long readDistanceCm();
void updateDistanceReading(unsigned long now);
void runStateMachine(unsigned long now);
void setMotionState(MotionState nextState, unsigned long now);
void driveForward();
void driveBackward();
void pivotLeft();
void pivotRight();
void stopMotors();
bool obstacleDetected();
bool pathIsClear();

void setup() {
  unsigned long now = millis();

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  lastSensorReadMs = now - sensorReadIntervalMs;
  lastStatusReportMs = now - statusReportIntervalMs;
  setMotionState(DRIVING_FORWARD, now);
}

void loop() {
  unsigned long now = millis();
  updateDistanceReading(now);
  runStateMachine(now);
}

long readDistanceCm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, echoTimeoutUs);
  if (duration == 0) {
    return -1;
  }

  return duration / 58;
}

void updateDistanceReading(unsigned long now) {
  if (now - lastSensorReadMs < sensorReadIntervalMs) {
    return;
  }

  lastSensorReadMs = now;
  lastDistanceCm = readDistanceCm();

  if (now - lastStatusReportMs >= statusReportIntervalMs) {
    lastStatusReportMs = now;
    Serial.print("Distance: ");
    if (lastDistanceCm < 0) {
      Serial.println("no echo");
    } else {
      Serial.print(lastDistanceCm);
      Serial.println(" cm");
    }
  }
}

void runStateMachine(unsigned long now) {
  unsigned long stateElapsedMs = now - stateStartedMs;

  switch (motionState) {
    case DRIVING_FORWARD:
      if (obstacleDetected()) {
        setMotionState(PAUSING_BEFORE_REVERSE, now);
      }
      break;

    case PAUSING_BEFORE_REVERSE:
      if (stateElapsedMs >= stopPauseMs) {
        setMotionState(REVERSING, now);
      }
      break;

    case REVERSING:
      if (stateElapsedMs >= reverseTimeMs) {
        setMotionState(TURNING, now);
      }
      break;

    case TURNING:
      if (stateElapsedMs >= maxTurnTimeMs ||
          (stateElapsedMs >= minTurnTimeMs && pathIsClear())) {
        turnLeftNext = !turnLeftNext;
        setMotionState(DRIVING_FORWARD, now);
      }
      break;
  }
}

void setMotionState(MotionState nextState, unsigned long now) {
  motionState = nextState;
  stateStartedMs = now;

  switch (motionState) {
    case DRIVING_FORWARD:
      Serial.println("Driving forward.");
      driveForward();
      break;

    case PAUSING_BEFORE_REVERSE:
      Serial.println("Obstacle detected, pausing.");
      stopMotors();
      break;

    case REVERSING:
      Serial.println("Reversing.");
      driveBackward();
      break;

    case TURNING:
      if (turnLeftNext) {
        Serial.println("Turning left.");
        pivotLeft();
      } else {
        Serial.println("Turning right.");
        pivotRight();
      }
      break;
  }
}

void driveForward() {
  motor1.setSpeed(forwardSpeed);
  motor2.setSpeed(forwardSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void driveBackward() {
  motor1.setSpeed(reverseSpeed);
  motor2.setSpeed(reverseSpeed);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}

void pivotLeft() {
  motor1.setSpeed(turnSpeed);
  motor2.setSpeed(turnSpeed);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}

void pivotRight() {
  motor1.setSpeed(turnSpeed);
  motor2.setSpeed(turnSpeed);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}

void stopMotors() {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

bool obstacleDetected() {
  return lastDistanceCm >= 0 && lastDistanceCm <= obstacleDistanceCm;
}

bool pathIsClear() {
  return lastDistanceCm >= clearDistanceCm;
}
