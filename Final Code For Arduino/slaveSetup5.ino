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
  
  if(x == 'L' || x == 'R') {
    Serial.println("detected variable");
    objectAttempt();
  }

  else {
    // forwards
    digitalWrite (enable, HIGH);
    digitalWrite (MotorA, HIGH);
    digitalWrite (MotorB, LOW);
    Serial.println("Running");
  }
  
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
  delay(4000);

  movingAway();
  x = 'c'; // what does this mean 
  sendEvent('G', 9); // sends message back to master saying its picked up the object to re-enable proximity sensor
}

void movingAway() {

  // backwards
  digitalWrite (enable, HIGH);
  digitalWrite (MotorA, LOW);
  digitalWrite (MotorB, HIGH);
  delay (5000);
  dropObject();//drops object
  delay (2000);//then contiues to move back in an effort to avodi hitting the block when turning
  digitalWrite (enable, LOW);
  // IF statement here on if the distance between third proximity at top and object is still the same, then knows object is captured
  // if so, then use dropObject();
  // IF NOT - no object captured, turn and try again >>> *** make turns suited to specific layout
}

void dropObject() {
  digitalWrite (clawDirection, LOW); // this should be opening
}

void sendEvent(char val, int id) {
  Wire.beginTransmission(id);
  Wire.write(val);
  Wire.endTransmission(id);
  Serial.println(val);
}
