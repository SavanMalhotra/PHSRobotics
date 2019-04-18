#include <Wire.h>

#define enable 13
#define MotorA 11
#define MotorB 12
#define clawEnable 10
#define clawDirection 4

char x;
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  
  //Define inputs and outputs
  pinMode (enable, OUTPUT);
  pinMode (MotorA, OUTPUT);
  pinMode (MotorB, OUTPUT); 
  pinMode (clawEnable, OUTPUT);
  pinMode (clawDirection, OUTPUT);   
  
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  
  Serial.print("Has begun");
}
void receiveEvent(int bytes) {
  x = Wire.read();
  Serial.println(x);
  if(x == 'J') {
    delay(500);
    dropObject();
  }
  else {
    digitalWrite(clawDirection, LOW); // claw opens up anyway
  }
}

void loop() {
  if(x == 'L' || x == 'R') {
    Serial.println("detected variable");
    objectAttempt();
  }

  else if(x == 'B') {
    digitalWrite (enable, HIGH);
    digitalWrite (MotorA, LOW);
    digitalWrite (MotorB, HIGH);
  }

  else {
    // forwards
    forward();
    Serial.println("Running");
  } 
}

void forward() {
    digitalWrite (enable, HIGH);
    digitalWrite (MotorA, HIGH);
    digitalWrite (MotorB, LOW);
}
void stopF() {
  digitalWrite (enable, LOW);
  delay(2000);
}

void objectAttempt() {

  digitalWrite (enable, LOW);
  digitalWrite (clawEnable, HIGH);
  digitalWrite (clawDirection, HIGH); // this should be closing, not sure
  // put here the distance third proximity at top detects
  delay(2000);
  
  movingAway();
 
}

void movingAway() {

  // backwards
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, HIGH);
  Serial.println("test");
  x = 'B';
  sendEvent('B', 9);
 
}

void dropObject() {
  // turning one way >> track WHICH way
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, HIGH);
  digitalWrite (MotorB, HIGH);
  delay (1100);
  
  digitalWrite (clawDirection, LOW); // this should be opening
  delay (500);
  
  // turning back 
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, LOW);
  delay (1100);

  // turn again
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, LOW);
  delay (1100);

  forward();
  delay (2000);

  // turn back
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, HIGH);
  digitalWrite (MotorB, HIGH);
  delay (1100);
}

void sendEvent(char val, int id) {
  Wire.beginTransmission(id);
  Wire.write(val);
  Wire.endTransmission(id);
  Serial.println(val);
}
