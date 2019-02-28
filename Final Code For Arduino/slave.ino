
#include <Wire.h>

#define enable 13
#define MotorA 11
#define MotorB 12

char x;
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
 
  
  pinMode (enable, OUTPUT);
  pinMode (MotorA, OUTPUT);
  pinMode (MotorB, OUTPUT);    
  
  Wire.begin(9);

  Wire.onReceive(receiveEvent);
  Serial.print("Has begun");

}
void receiveEvent(int bytes) {
  x = Wire.read();
  Serial.println(x);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Serial.println("Checking");
  
  if(x == 'A' || x == 'B') {
    Serial.println("detected variable");
    stopForward();
  }
  else {
    //Serial.println ("Motion Forward"); // counterclockwise
    digitalWrite (enable, HIGH);
    digitalWrite (MotorA, HIGH);
    digitalWrite (MotorB, LOW);
    Serial.println("Running");
  }
}

void stopForward() {
  
  Serial.println("yes");
  digitalWrite (enable, LOW);
  delay(2000);
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, HIGH);
  delay (2000);
//  digitalWrite (enable, HIGH);
//  digitalWrite (MotorA, HIGH);
//  digitalWrite (MotorB, LOW);
//  delay (2000);
//  digitalWrite (MotorA, HIGH);
//  digitalWrite (MotorB, HIGH);
//  delay (1500);
//  digitalWrite (MotorA, LOW);
//  digitalWrite (MotorB, HIGH);
//  delay (1500);
//  digitalWrite (MotorA, LOW);
//  digitalWrite (MotorB, LOW);
//  delay (1500);
//  digitalWrite (MotorA, LOW);
//  digitalWrite (MotorB, HIGH);
  x = 'c';
  sendEvent('R', 9);
}

void sendEvent(char val, int id) {
  Wire.beginTransmission(id);
  Wire.write(val);
  Wire.endTransmission(id);
  Serial.println(val);
}
