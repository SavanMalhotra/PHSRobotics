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
//  if(x == 'J') {
//    delay(500);
//    dropObject();
//  }

}

void loop() {
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
  }
  else if(x == 'N') {
    Serial.print("lol nothing");
    x = 'G';
    sendEvent('G', 9);
    digitalWrite (clawDirection, LOW);
  }
  else {
    // forwards
    forward();
    //Serial.println("Running");
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
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, HIGH);
  digitalWrite (MotorB, HIGH);
  delay (1050);
  
  digitalWrite (clawDirection, LOW); // this should be opening
  delay (500);
  
  // turning back & other way
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, LOW);
  delay (3100);


  forward();
  delay (500);

  // turn back
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, HIGH);
  digitalWrite (MotorB, HIGH);
  delay (1000);

  Serial.println("in turning");
  x = 'G';
}

void sendEvent(char val, int id) {
  Wire.beginTransmission(id);
  Wire.write(val);
  Wire.endTransmission(id);
  Serial.println(val);
}
