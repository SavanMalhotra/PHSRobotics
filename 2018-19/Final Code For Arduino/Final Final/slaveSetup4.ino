// SLAVE SET UP FOUR
#include <Wire.h>

#define enable 13
#define MotorA 11
#define MotorB 12
#define clawEnable 10
#define clawDirection 4

int counter = 1;
int RA = 1050;
int attempts = 0;
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
//  if(x == 'J') {
//    delay(500);
//    dropObject();
//  }

}

void loop() {
  while (counter == 1 && attempts < 2) {
    forward();
    if(x == 'L' || x == 'R') {
      Serial.println("detected variable");
      objectAttempt();
    }
    else if(x == 'J') {
      turnRight();
      delay(RA);
      digitalWrite (clawDirection, LOW); // this should be opening
      delay (500);
      turnRight();
      delay(RA);
      x = 'G';
      sendEvent('G', 9);
      Serial.println(x);
      Serial.println("OUT");
      counter = counter + 1;
      attempts = 0;
    }
    else if(x == 'N') {
      Serial.print("lol nothing");
      x = 'G';
      sendEvent('G', 9);
      digitalWrite (clawDirection, LOW);
      delay(500);
      attempts = attempts + 1;
    }
  }
  if (attempts == 2) {
    turnRight();
    delay(RA);
    digitalWrite (clawDirection, LOW); // this should be opening
    delay (500);
    turnRight();
    delay(RA);
    attempts = 0;
  }
  while (counter == 2 && attempts < 2) {
    forward();
    if(x == 'L' || x == 'R') {
      Serial.println("detected variable");
      objectAttempt();
    }
    else if(x == 'J') {
      dropObject();
      x = 'G';
      sendEvent('G', 9);
      Serial.println(x);
      Serial.println("OUT");
      counter = 3;
      attempts = 0;
    }
    else if(x == 'N') {
      Serial.print("lol nothing");
      x = 'G';
      sendEvent('G', 9);
      digitalWrite (clawDirection, LOW);
      delay(500);
      attempts = attempts + 1;
    }
  }
  
  while (counter == 3) {
      forward();
      if(x == 'L' || x == 'R') {
        Serial.println("detected variable"); // trying to align with first block thingy at the bottom 
        turnRight();
        delay(RA);
        counter = 4;
      }
  }

  while (counter == 4) {
    forward();
    if(x == 'L' || x == 'R') {
      Serial.println("detected variable");
      objectAttempt();
    }
    else if(x == 'J') {
      digitalWrite (clawDirection, LOW);
      delay(500);
      x = 'G';
      sendEvent('G', 9);
      Serial.println(x);
      Serial.println("OUT");
      digitalWrite (clawDirection, LOW);
      delay(500);
      turnRight();
      delay(RA);
      forward();
      delay(500);
      turnLeft();
      delay(RA);
    }
    else if(x == 'N') {
      Serial.print("lol nothing");
      x = 'G';
      sendEvent('G', 9);
      digitalWrite (clawDirection, LOW);
      delay(500);
      turnRight();
      delay(RA);
      forward();
      delay(500);
      turnLeft();
      delay(RA);
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

void dropObject() {
  // turning one way >> track WHICH way
  Serial.println("DROP");
  turnLeft();
  delay (RA);
  
  digitalWrite (clawDirection, LOW); // this should be opening
  delay (500);
  
  // turning back & other way
  turnRight();
  delay (RA);

  Serial.println("in turning");
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
