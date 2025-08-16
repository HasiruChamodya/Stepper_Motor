#include <AccelStepper.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// HALF4WIRE mode, correct coil order for 28BYJ-48
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

const long stepsPerRevolution = 4076;  // half-step mode for 28BYJ-48

// Button variables
int btnPin = 2;
int motorDir = 1;         // 1 = forward, -1 = backward
int btnValNew;
int btnValOld = HIGH;
bool motorRunning = false;

void setup() {
  Serial.begin(9600);
  stepper.setMaxSpeed(700);      // max speed in steps/sec
  stepper.setAcceleration(100);  // acceleration in steps/sec^2
  pinMode(btnPin, INPUT_PULLUP); // button with internal pull-up
}

void loop() {
  btnValNew = digitalRead(btnPin);

  // Detect button press (falling edge)
  if (btnValOld == HIGH && btnValNew == LOW && !motorRunning) {
    motorDir *= -1;  // change direction
    stepper.moveTo(stepper.currentPosition() + stepsPerRevolution * motorDir);
    motorRunning = true;
  }
  btnValOld = btnValNew;

  // Run motor if it has steps to go
  if (motorRunning) {
    if (stepper.distanceToGo() != 0) {
      stepper.run();
    } else {
      motorRunning = false; // stop motor after one full revolution
      Serial.println("Completed 360° rotation.");
    }
  }
}
