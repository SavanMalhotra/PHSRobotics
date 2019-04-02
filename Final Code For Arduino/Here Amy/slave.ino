
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
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Serial.println("Checking");
  
  if(x == 'L' || x == 'R') {
    Serial.println("detected variable");
    stopForward();
  }

  if(x == 'P') {
    Serial.println("detected variable");
    stopF();
  }
  else {
    //Serial.println ("Motion Forward"); // counterclockwise
    digitalWrite (enable, HIGH);
    digitalWrite (MotorA, HIGH);
    digitalWrite (MotorB, LOW);
    Serial.println("Running");
    digitalWrite (clawEnable, HIGH);
  digitalWrite (clawDirection, LOW);
  delay(2000);
  digitalWrite (clawEnable, LOW);
  digitalWrite (clawDirection, HIGH);
  delay(2000);
  digitalWrite (clawEnable, HIGH);
  digitalWrite (clawDirection, HIGH);
  Serial.println("claw");
  }
  
}

void stopF() {
  digitalWrite (enable, LOW);
  delay(2000);
}

void stopForward() {
  
  Serial.println("yes");
  digitalWrite (enable, LOW);
  delay(2000);
  //clockwise
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, LOW);
  delay (2000);
  //counter clockwise
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, HIGH);
  digitalWrite (MotorB, HIGH);
  delay (2000);
  //Forward
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, HIGH);
  digitalWrite (MotorB, LOW);
  delay (2000);
  //backward
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
  sendEvent('G', 9);
}

void sendEvent(char val, int id) {
  Wire.beginTransmission(id);
  Wire.write(val);
  Wire.endTransmission(id);
  Serial.println(val);
}
