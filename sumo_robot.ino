#include "GLOBALS.h" 

void setup() {
  Serial.begin(115200);
  pinMode(ch1Pin, INPUT);
  pinMode(ch2Pin, INPUT);

  motor1.enable();  motor2.enable();                                  //Makes all enable pins go high
  // noTone(buzzpin);
}

// ch2Mapped (throttle) | ch1Mapped (steering) | Action | State
// > 0 | 0 | Forward | F
// < 0 | 0 | Backward | B
// == 0 | > 0 | Turn right in-place | R
// == 0 | < 0 | Turn left in-place | L
// > 0 | > 0 | Right forward arc | I
// > 0 | < 0 | Left forward arc | G
// < 0 | > 0 | Right backward arc | J
// < 0 | < 0 | Left backward arc | H
// == 0 | == 0 | Stop | S

int ch1Raw, ch2Raw, ch1Mapped, ch2Mapped;

void loop() {
  ch1Raw = pulseIn(ch1Pin, HIGH, 25000);
  ch2Raw = pulseIn(ch2Pin, HIGH, 25000);

  if (ch1Raw == 0 || ch2Raw == 0) {
    // Ignore bad readings
    motor1.pwm = motor2.pwm = 0;
    motor1.stop();
    motor2.stop();
    Serial.println("Signal Lost or Noise");
    return;
  }

  ch1Raw = constrain(ch1Raw, steeringMin, steeringMax);
  ch2Raw = constrain(ch2Raw, throttleMin, throttleMax);

  ch1Mapped = map(ch1Raw, steeringMin, steeringMax, -255, 255);
  ch2Mapped = 0;

  if (ch2Raw > pwmCenter) {
    ch2Mapped = map(ch2Raw, pwmCenter, throttleMax, 0, 255);
  } else if (ch2Raw < pwmCenter) {
    ch2Mapped = -map(ch2Raw, throttleMin, pwmCenter, 255, 0);
  }

  if (abs(ch1Mapped) < 25 && ch2Mapped > 10 ) {
    motor1.pwm = motor2.pwm = ch2Mapped;
    motor1.front();
    motor2.front();
    Serial.print("Front; ");
  } else if (ch1Mapped < -25 && abs(ch2Mapped) < 10 ) {
    motor1.pwm = 0;
    motor2.pwm = abs(ch1Mapped);
    motor1.stop();
    motor2.front();
    Serial.print("Left; ");
  } else if (ch1Mapped > 25 && abs(ch2Mapped) < 10 ) {
    motor1.pwm = ch1Mapped;
    motor2.pwm = 0;
    motor1.front();
    motor2.stop();
    Serial.print("Right; ");
  } else if (ch1Mapped > 25 && ch2Mapped > 10) {
    motor2.pwm = constrain(ch1Mapped, 0, 235);  // 235 to leave room for +20 in motor1
    motor1.pwm = constrain(max(ch2Mapped, motor2.pwm + 20), 0, 255);  // ensure motor1 is 20 more
    motor1.front();
    motor2.front();
    Serial.print("Right Arc; ");
  } else if (ch1Mapped < -25 && ch2Mapped > 10) {
    motor1.pwm = constrain(abs(ch1Mapped), 0, 235);  // weaker (inner) motor
    motor2.pwm = constrain(max(ch2Mapped, motor1.pwm + 20), 0, 255);  // stronger outer motor
    motor1.front();
    motor2.front();
    Serial.print("Left Arc; ");
  // } else if (abs(ch1Mapped) < 25 && ch2Mapped < -10 ) {
  } else if (ch2Mapped < -15 ) {
    motor1.pwm = motor2.pwm = abs(ch2Mapped);
    motor1.back();
    motor2.back();
    Serial.print("Back; ");
  } else {
    motor1.pwm = motor2.pwm = 0;
    motor1.stop();
    motor2.stop();
    Serial.print("Stop; ");
  }
  // else if (ch1Mapped > 25 && ch2Mapped < -5) {
  //   motor2.pwm = constrain(abs(ch2Mapped), 0, 235);  // leave room for +20
  //   motor1.pwm = constrain(max(ch1Mapped, motor2.pwm + 20), 0, 255);  // ensure motor1 > motor2
  //   motor1.back();
  //   motor2.back();
  //   Serial.print("Right Back Arc; ");
  // } else if (ch1Mapped < -25 && ch2Mapped > 5) {
  //   motor1.pwm = constrain(abs(ch1Mapped), 0, 235);  // weaker (inner) motor
  //   motor2.pwm = constrain(max(ch2Mapped, motor1.pwm + 20), 0, 255);  // stronger outer motor
  //   motor1.front();
  //   motor2.front();
  //   Serial.print("Left Arc; ");
  // } else if (ch1Mapped < -25 && ch2Mapped < -5) {
  //   motor1.pwm = constrain(abs(ch1Mapped), 0, 235);  // weaker (inner) motor
  //   motor2.pwm = constrain(max(abs(ch2Mapped), motor1.pwm + 20), 0, 255);  // stronger outer motor
  //   motor1.back();
  //   motor2.back();
  //   Serial.print("Left Back Arc; ");
  // } 

  // Serial.print("Motor1: ");
  // Serial.print(motor1.pwm);
  // Serial.print(" ;  Motor2: ");
  // Serial.print(motor2.pwm);


  // Serial.print("chRaw1: ");
  // Serial.print(ch1Raw);
  // Serial.print("  ;  ch2Raw: ");
  // Serial.print(ch2Raw);

  // Serial.print(" ;  ch1Mapped: ");
  // Serial.print(ch1Mapped);
  // Serial.print("  ;  ch2Mapped: ");
  // Serial.print(ch2Mapped);
  Serial.println();
}