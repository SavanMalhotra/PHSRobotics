
#include <Wire.h>

#define enable 5
#define MotorA 7
#define MotorB 10

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
    stopForward();
  }
  else {
    //Serial.println ("Motion Forward"); // counterclockwise
    digitalWrite (enable, LOW);
    digitalWrite (MotorA, LOW);
    digitalWrite (MotorB, HIGH); 
  }
}

void stopForward() {
  
  Serial.println("yes");
  digitalWrite (enable, LOW);
  digitalWrite (MotorA, HIGH);
  digitalWrite (MotorB, LOW);
  delay (500);
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, HIGH);
  digitalWrite (MotorB, LOW);
  delay (2000);
  digitalWrite (MotorA, HIGH);
  digitalWrite (MotorB, HIGH);
  delay (1500);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, HIGH);
  delay (1500);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, LOW);
  delay (1500);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, HIGH);
  x = 'c';
  sendEvent('R', 9);
}

void sendEvent(char val, int id) {
  Wire.beginTransmission(id);
  Wire.write(val);
  Wire.endTransmission(id);
  Serial.println(val);
}
