#include <AccelStepper.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// HALF4WIRE mode, correct coil order for 28BYJ-48
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

const long stepsPerRevolution = 4076;  // half-step mode

void setup() {
  stepper.setMaxSpeed(500);      // max speed in steps/sec
  stepper.setAcceleration(50);  // acceleration in steps/sec^2
}

void loop() {
  // Move forward one revolution
  stepper.moveTo(stepsPerRevolution);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  delay(1000);

  // Move backward one revolution
  stepper.moveTo(0);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  delay(1000);
}
