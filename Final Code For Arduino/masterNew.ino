#include "Wire.h"
char x;
bool allowedToExecute = true;
int trigPin = 2;    // Trigger
int LeftFrontProximity = 4;    // LeftFrontProximity Sensor echo pin
int RightFrontProximity = 3;    // RightFrontProximity Sensor echo pin
long LeftFrontDuration, LeftFrontCm, RightFrontDuration, RightFrontCm;


String one = "";
String two = "";

int LC;
int MC;


void setup() {
  Wire.begin(9);//Used for conenction between arduinos
  Wire.onReceive(receiveEvent);
  pinMode(trigPin, OUTPUT);
  pinMode(LeftFrontProximity, INPUT);
  pinMode(RightFrontProximity, INPUT);

  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
  
}

void receiveEvent(int bytes) {
  Serial.print("HERERERERERERERERERERER: ");
  Serial.println(bytes);
  x = Wire.read();
  if(x == 'G') {
    allowedToExecute = true;
  }
}

void sendEvent(char val, int id) {
  allowedToExecute = false;
  Wire.beginTransmission(id);
  Wire.write(val);
  Wire.endTransmission(id);
  Serial.println(val);
}

void loop() {
  proximitySensor();
  delay(300);
}


void proximitySensor() {
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
  
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  pinMode(RightFrontProximity, INPUT);
  RightFrontDuration = pulseIn(RightFrontProximity, HIGH);
  RightFrontCm = (RightFrontDuration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
 
  Serial.println(LeftFrontCm);
  if(LeftFrontCm <= 10 && allowedToExecute && LeftFrontCm >0) {
    sendEvent('L', 9);
  }

  Serial.println(RightFrontCm);
  if(RightFrontCm <= 10 && allowedToExecute && RightFrontCm>0) {
    sendEvent('R', 9);
  }
}

void checkValues() {

}
