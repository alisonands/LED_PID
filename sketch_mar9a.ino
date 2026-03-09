#include <Servo.h>

Servo servoX;  // left/right
Servo servoY;  // up/down

float posX = 90;
float posY = 90;

// PID constants
float Kp = 0.02;
float Ki = 0.0001;
float Kd = 0.01;

// PID state
float lastErrorX = 0;
float lastErrorY = 0;
float integralX = 0;
float integralY = 0;

void setup() {

  servoX.attach(9);
  servoY.attach(10);

  Serial.begin(9600);
  delay(1000);
}

void loop() {

  // read sensors
  int s1 = analogRead(A0);  // top-left
  int s2 = analogRead(A1);  // top-right
  int s3 = analogRead(A2);  // bottom

  // compute errors
  // flipped signs
  float errorX = s3 - s2;               // now positive = LED is left
  float errorY = s1 - (s2 + s3) / 2.0;  // now positive = LED is below, servo moves up

  // integral
  integralX += errorX;
  integralY += errorY;

  // derivative
  float derivativeX = errorX - lastErrorX;
  float derivativeY = errorY - lastErrorY;

  // PID output
  float outputX = Kp * errorX + Ki * integralX + Kd * derivativeX;
  float outputY = Kp * errorY + Ki * integralY + Kd * derivativeY;

  // update servo positions
  posX += outputX;
  posY += outputY;

  posX = constrain(posX, 0, 180);
  posY = constrain(posY, 0, 180);

  servoX.write(posX);
  servoY.write(posY);

  lastErrorX = errorX;
  lastErrorY = errorY;

  // print sensor values
  // Serial.print("S1:");
  // Serial.print(s1);
  // Serial.print("  S2:");
  // Serial.print(s2);
  // Serial.print("  S3:");
  // Serial.print(s3);
  Serial.print(millis()); Serial.print(",");

  // Serial.print("   errX:");
  Serial.print(errorX);
  Serial.print(",");
  
  Serial.println(errorY);
  // Serial.print(",");

  delay(20);
}