#include <Wire.h>
char x;
bool allowedToExecute = true;
int trigPin = 2;    // Trigger
int LeftFrontProximity = 4;    // LeftFrontProximity Sensor echo pin
int RightFrontProximity = 3;    // RightFrontProximity Sensor echo pin
int TopFrontProximity = 5; //TopFrontProximity Sensor echo pin
long LeftFrontDuration, LeftFrontCm, RightFrontDuration, RightFrontCm,TopFrontDuration, TopFrontCm;

#define test 7

int proximityDistanceVariable = 20;
String one = "";
String two = "";

int LC;
int MC;

int blockDistance;


void setup() {
  Wire.begin(9);//Used for conenction between arduinos
  Wire.onReceive(receiveEvent);
  pinMode(trigPin, OUTPUT);
  pinMode(LeftFrontProximity, INPUT);
  pinMode(RightFrontProximity, INPUT);
  pinMode(TopFrontProximity, INPUT);
  pinMode(test, OUTPUT);
  Serial.begin(9600);
}

void receiveEvent(int bytes) {
  x = Wire.read();
  if(x == 'G') {
    allowedToExecute = true;
  }
//  if(x =='B'){
//    //Serial.print("BBB");
//    checkBlock(); 
//    digitalWrite(test, HIGH);
//  } 
}

void checkBlock() {
  //Serial.println("called");
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(TopFrontProximity, INPUT);
  TopFrontDuration = pulseIn(TopFrontProximity, HIGH);
  // Convert the time into a distance
  blockDistance = (TopFrontDuration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  //blockDistance = 5;
  delay(750);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(TopFrontProximity, INPUT);
  TopFrontDuration = pulseIn(TopFrontProximity, HIGH);
  // Convert the time into a distance
  TopFrontCm = (TopFrontDuration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  //TopFrontCm = 5;
  //Serial.println("got block test");

  Serial.print("first value: ");
  Serial.println(blockDistance);
  Serial.print("second value: ");
  Serial.println(TopFrontCm);
  if(TopFrontCm <= blockDistance+2 && blockDistance < 10){
    //Serial.println("got block");
    sendEvent('J', 9); //>????????????
  }
  else {
    Serial.println("nothing");
    sendEvent('N', 9);
  }
}

void sendEvent(char val, int id) {
  Serial.println("aaa");
  
  Wire.beginTransmission(id);
  Wire.write(val);
  Wire.endTransmission(id);
  Serial.println(val);
}

void loop() {
  proximitySensor();
  delay(300);
  if(x =='B'){
    Serial.print("BBB");
    checkBlock(); 
    digitalWrite(test, HIGH);
  } 
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
  if(LeftFrontCm <= proximityDistanceVariable && allowedToExecute && LeftFrontCm >0) {
    delay(475);
    //allowedToExecute = false;
    sendEvent('L', 9);
  }

  Serial.println(RightFrontCm);
  if(RightFrontCm <= proximityDistanceVariable && allowedToExecute && RightFrontCm>0) {
    delay(475);
    //allowedToExecute = false;
    sendEvent('R', 9);
  }
}

void checkValues() {

}
