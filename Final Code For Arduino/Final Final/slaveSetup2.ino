// SLAVE SET UP TWO
#include <Wire.h>

#define enable 13
#define MotorA 11
#define MotorB 12
#define clawEnable 10
#define clawDirection 4

int counter = 0;
int attempts = 0;
int RA = 1050;
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

  forward();
  delay(600);
  
  turnRight();
  delay(RA);
  
}
void receiveEvent(int bytes) {
  x = Wire.read();
  Serial.println(x);
//  if(x == 'J') {
//    delay(500);
//    dropObject();
//  }

}

void loop() {
  forward();
  if(x == 'L' || x == 'R') {
    Serial.println("detected variable");
    objectAttempt();
    movingAway();
    delay(3600);
  }
  else if(x == 'J') {
    dropObject();
    x = 'G';
    sendEvent('G', 9);
    Serial.println(x);
    Serial.println("OUT");
    turnLeft();
    delay(RA);
    forward();
    delay(300);
    turnRight();
    delay(RA);
    counter = counter + 1;
  }
  else if(x == 'N') {
    Serial.print("lol nothing");
    x = 'G';
    sendEvent('G', 9);
    digitalWrite (clawDirection, LOW);
    delay(500);
    turnLeft();
    delay(RA);
    forward();
    delay(300);
    turnRight();
    delay(RA);
    attempts = attempts + 1;
  }
  if (counter >= 3 || attempts >=6) {
    turnLeft();
    delay(RA);
    forward();
    delay(2000);
    turnRight();
    delay(RA);
    forward();
    delay(4000);
    turnRight();
    delay(RA);
    forward()
    delay(2000);
    turnRight();
    delay(RA);
    counter = 0;
    attempts = 0;
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

  x = 'B';
  //Serial.println("test");
  sendEvent('B', 9);
  

}

void movingAway() {

  // backwards
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, HIGH);
}

void dropObject() {
  // turning one way >> track WHICH way
  Serial.println("DROP");
  
  digitalWrite (clawDirection, LOW); // this should be opening
  delay (500);
  
  x = 'G';
}

void turnRight() {
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, HIGH);
  digitalWrite (MotorB, HIGH);
}

void turnLeft() {
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, LOW);
}

void sendEvent(char val, int id) {
  Wire.beginTransmission(id);
  Wire.write(val);
  Wire.endTransmission(id);
  Serial.println(val);
}
