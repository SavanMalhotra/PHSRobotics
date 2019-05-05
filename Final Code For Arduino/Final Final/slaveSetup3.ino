// SLAVE SET UP THREE
#include <Wire.h>

#define enable 13
#define MotorA 11
#define MotorB 12
#define clawEnable 10
#define clawDirection 4

int counter = 1;
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
  delay(3600);
  
  turnRight();
  delay(RA);
  forward();
  delay (3600);
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
  while (counter == 1) {
    forward();
    if(x == 'L' || x == 'R') {
      Serial.println("detected variable");
      objectAttempt();
    }
    else if(x == 'J') {
      // finding yellow drop off zone
      turnLeft();
      delay(RA);
      forward();
      delay(3600);
      turnRight();
      delay(RA);
      forward();
      delay(3100);
      digitalWrite (clawDirection, LOW);
      delay(500);
      x = 'G';
      sendEvent('G', 9);
      Serial.println(x);
      Serial.println("OUT");
      forward();
      delay(3000);
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
      delay(200);
      turnRight();
      delay(RA);
      attempts = attempts + 1;
      if (attempts >= 4) {
        turnLeft();
        delay(RA);
        forward();
        delay(3600);
        turnRight();
        delay(RA);
        forward();
        delay(6000);
        counter = counter + 1;
      }
    }
  }
  while (counter == 2) { // setting up to get second yellow block
    turnRight();
    delay(RA);
    forward();
    delay (3400);
    turnRight();
    delay(RA);
    counter = 3;
  }
  while (counter == 3) {
    forward();
    if(x == 'L' || x == 'R') {
      Serial.println("detected variable");
      objectAttempt();
    }
    else if(x == 'J') {
      // finding yellow drop off zone
      turnRight();
      delay(RA);
      forward();
      delay(3600);
      turnLeft();
      delay(RA);
      forward();
      delay(3100);
      digitalWrite (clawDirection, LOW);
      delay(500);
      x = 'G';
      sendEvent('G', 9);
      Serial.println(x);
      Serial.println("OUT");
      forward();
      delay(3000);
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
      delay(200);
      turnRight();
      delay(RA);
      attempts = attempts + 1;
      if (attempts >= 4) {
        turnLeft();
        delay(RA);
        forward();
        delay(3600);
        turnRight();
        delay(RA);
        forward();
        delay(6000);
        counter = counter + 1;
      }
    }
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
  
  movingAway();
  delay(3000);
}

void movingAway() {

  // backwards
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, HIGH);
}

//void dropObject() {
//  // turning one way >> track WHICH way
//  Serial.println("DROP");
//  turnRight();
//  delay (1050);
//  
//  digitalWrite (clawDirection, LOW); // this should be opening
//  delay (500);
//  
//  // turning back & other way
//  turnLeft();
//  delay (1050);
//
//  // turn back
//  turnLeft();
//  delay (700);
//
//  Serial.println("in turning");
//  x = 'G';
//}

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
