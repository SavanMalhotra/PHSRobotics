
#include <Wire.h>
char x;
bool allowedToExecute = true;
int trigPin = 8;    // Trigger
int LeftFrontProximity = 12;    // LeftFrontProximity Sensor echo pin
int RightFrontProximity = 13;    // RightFrontProximity Sensor echo pin
long LeftFrontDuration, LeftFrontCm, RightFrontDuration, RightFrontCm;

void setup() {
  Serial.begin(9600);
  Wire.begin();//Used for conenction between arduinos
  Wire.onReceive(receiveEvent);
  pinMode(trigPin, OUTPUT);
  pinMode(LeftFrontProximity, INPUT);
  pinMode(RightFrontProximity, INPUT);
}

void receiveEvent(int bytes) {
  x = Wire.read();
  Serial.println(x);
  if(x == 'R') {
    allowedToExecute = true;
  }
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(LeftFrontProximity, INPUT);
  LeftFrontDuration = pulseIn(LeftFrontProximity, HIGH);
  // Convert the time into a distance
  LeftFrontCm = (LeftFrontDuration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
 
  pinMode(RightFrontProximity, INPUT);
  RightFrontDuration = pulseIn(LeftFrontProximity, HIGH);
  RightFrontCm = (LeftFrontDuration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  
  Serial.println(LeftFrontCm);
  if(LeftFrontCm <= 20 && allowedToExecute) {
    sendEvent('A', 9);
  }

  Serial.println(RightFrontCm);
  if(RightFrontCm <= 20 && allowedToExecute) {
    sendEvent('B', 9);
  }
}

void sendEvent(char val, int id) {
  allowedToExecute = false;
  Wire.beginTransmission(id);
  Wire.write(val);
  Wire.endTransmission(id);
  Serial.println(val);
}
