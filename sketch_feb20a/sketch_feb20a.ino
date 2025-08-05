#include <Servo.h>

Servo servo1;

const int motionSensor = 2;
const int greenLED = 3;
const int redLED = 4;
const int buzzer = 5;
bool dancing = false;

// Define Jingle Bells melody and rhythm
int melody[] = { 
    262, 262, 262, 262, 262, 262, 262, 392, 262, 349, 330, 294, 
    523, 523, 523, 523, 523, 392, 392, 392, 392, 349, 330, 294 
};
int noteDurations[] = { 
    300, 300, 600, 300, 300, 600, 300, 300, 300, 300, 300, 600, 
    300, 300, 600, 300, 300, 600, 300, 300, 300, 300, 300, 600 
};

void setup() {
    pinMode(motionSensor, INPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(redLED, OUTPUT);
    pinMode(buzzer, OUTPUT);
    
    servo1.attach(9);
}

void loop() {
    if (digitalRead(motionSensor) == HIGH) {  
        digitalWrite(greenLED, HIGH);
        digitalWrite(redLED, LOW);
        playAndDance();
    } else {
        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, HIGH);
    }
}

void playAndDance() {
    for (int i = 0; i < 24; i++) {
        // Play the note
        tone(buzzer, melody[i], noteDurations[i]);
        
        // Make the servo dance to the rhythm
        int angle = (i % 2 == 0) ? random(0, 40) : random(80, 0); 
        servo1.write(angle);
        
        // Blink LED with music
        digitalWrite(greenLED, (i % 2 == 0) ? HIGH : LOW);

        // Wait for the duration of the note
        delay(noteDurations[i] * 1.3);
        
        // Stop the buzzer sound
        noTone(buzzer);
    }

    // Return to neutral position after dancing
    servo1.write(90);
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
}
