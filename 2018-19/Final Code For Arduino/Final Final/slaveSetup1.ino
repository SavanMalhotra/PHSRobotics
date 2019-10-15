// SET UP ONE
#include <Wire.h>

#define enable 13
#define MotorA 11
#define MotorB 12
#define clawEnable 10
#define clawDirection 4

int counter = 1;
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
  delay(1050);
  
}
void receiveEvent(int bytes) {
  x = Wire.read();
  Serial.println(x);

}

void loop() {
  while(counter == 1) {
    forward();
    if(x == 'L' || x == 'R') {
      Serial.println("detected variable");
      objectAttempt();
      movingAway();
      delay(3600);
      digitalWrite (clawDirection, LOW); // this should be opening
      delay (500);
      counter = 2;
    }
  }
  while(counter == 2) {
    turnLeft();
    delay(RA);
    forward();
    delay(1800);
    turnRight();
    delay(RA);
    forward();
    delay(3600);
    turnLeft();
    delay(RA);
    counter = 3;
  }
  while (counter == 3) {
    forward();
    if(x == 'L' || x == 'R') {
      Serial.println("detected variable");
      objectAttempt();
      movingAway();
      delay(1800);
      digitalWrite (clawDirection, LOW); // this should be opening
      delay (500);
    }
    counter = 4;
  }
  while (counter == 4) {
    turnRight();
    delay(RA);
    forward();
    delay(1800);
    turnRight();
    delay(RA);
    forward();
    delay(1800);
    turnLeft();
    delay(RA);
    counter = 5;
  }
  while (counter == 5) {
    forward();
    if(x == 'L' || x == 'R') {
      Serial.println("detected variable");
      objectAttempt();
      movingAway();
      delay(1600);
      digitalWrite (clawDirection, LOW); // this should be opening
      delay (500);
    }
    counter = 6;
  }
  while (counter == 6) {
    turnRight();
    delay(RA);
    counter = 7;
  }
  while(counter==7) {
    forward();
    if(x == 'L' || x == 'R') {
      Serial.println("detected variable");
      objectAttempt();
      movingAway();
      delay(3000);
    }
    else if(x == 'J') {
      turnLeft(); // finding yellow square to drop on
      delay(RA);
      forward();
      delay(3400);
      digitalWrite (clawDirection, LOW);
      delay (500);
      dropObject();
      
      x = 'G';
      sendEvent('G', 9);
      Serial.println(x);
      Serial.println("OUT");
      counter = 8;
    }
    else if(x == 'N') {
      Serial.print("lol nothing");
      x = 'G';
      sendEvent('G', 9);
      digitalWrite (clawDirection, LOW);
      delay (500);
      turnRight();
      delay(RA);
      forward();
      delay(200);
      turnLeft();
      delay(RA);
    }
  }
  while (counter == 8) { // just for fun after to just run around the court idk
    forward();
     if(x == 'L' || x == 'R') {
      Serial.println("detected variable");
      objectAttempt();
      movingAway();
      delay(3000);
      digitalWrite (clawDirection, LOW);
      delay (500);
      turnLeft();
      delay(200);
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
  
}

void movingAway() {

  // backwards
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, HIGH);
}
//
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
