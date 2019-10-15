#include "Wire.h"
char x;
bool allowedToExecute = true;
int trigPin = 2;    // Trigger
int LeftFrontProximity = 4;    // LeftFrontProximity Sensor echo pin
int RightFrontProximity = 3;    // RightFrontProximity Sensor echo pin
long LeftFrontDuration, LeftFrontCm, RightFrontDuration, RightFrontCm;
#define S0 13
#define S1 12
#define S2 11
#define S3 10
#define sensorOut1 9
#define sensorOut2 8
int Rfrequency[2];
int Bfrequency[2];
int Gfrequency[2];

String one = "";
String two = "";

int LC;
int MC;


void setup() {
  Wire.begin(9);//Used for conenction between arduinos
  Wire.onReceive(receiveEvent);
  pinMode(trigPin, OUTPUT);
  pinMode(LeftFrontProximity, INPUT);
  pinMode(RightFrontProximity, INPUT);


  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut1, INPUT);
  pinMode(sensorOut2, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
  
}

void receiveEvent(int bytes) {
  Serial.print("HERERERERERERERERERERER: ");
  Serial.println(bytes);
  x = Wire.read();
  Serial.println(x);
  Serial.println(x);
  Serial.println(x);Serial.println(x);Serial.println(x);Serial.println(x);Serial.println(x);Serial.println(x);Serial.println(x);Serial.println(x);Serial.println(x);Serial.println(x);Serial.println(x);Serial.println(x);Serial.println(x);Serial.println(x);
  if(x == 'G') {
    allowedToExecute = true;
  }
}

void sendEvent(char val, int id) {
  allowedToExecute = false;
  Wire.beginTransmission(id);
  Wire.write(val);
  Wire.endTransmission(id);
  Serial.println(val);
}

void loop() {
  
  detectColor();
  proximitySensor();
  delay(300);
}

void detectColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  Rfrequency[0] = pulseIn(sensorOut1, LOW);
  Rfrequency[1] = pulseIn(sensorOut2, LOW);
  // Printing the value on the serial monitor
//  Serial.print("R1= ");//printing name
//  Serial.print(Rfrequency[0]);//printing RED color frequency
  //Serial.println("");
  //Serial.print("R2= ");//printing name
  //Serial.print(Rfrequency[1]);//printing RED color frequency
  //Serial.println("");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  Gfrequency[0] = pulseIn(sensorOut1, LOW);
  Gfrequency[1] = pulseIn(sensorOut2, LOW);
  // Printing the value on the serial monitor
//  Serial.print("G1= ");//printing name
//  Serial.print(Gfrequency[0]);//printing RED color frequency
  //Serial.println("");
  //Serial.print("G2= ");//printing name
  //Serial.print(Gfrequency[1]);//printing RED color frequency
  //Serial.println("");
  //Serial.print("G= ");//printing name
  //Serial.print(Gfrequency);//printing GREEN color frequency
  //Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  Bfrequency[0] = pulseIn(sensorOut1, LOW);
  Bfrequency[1] = pulseIn(sensorOut2, LOW);
  // Printing the value on the serial monitor
//  Serial.print("B1= ");//printing name
//  Serial.print(Bfrequency[0]);//printing RED color frequency
//  Serial.println("");
  //Serial.print("B2= ");//printing name
  //Serial.print(Bfrequency[1]);//printing RED color frequency
  Serial.println("");
  
  //Serial.print("B= ");//printing name
  //Serial.print(Bfrequency);//printing BLUE color frequency
  //Serial.println("  ");
  delay (200);
  for (int i = 0; i < 2; i++) {
      if (Bfrequency[i] > Gfrequency[i] && Bfrequency[i] > Rfrequency[i]) {
        Serial.println("yellow");
        if(i == 0) {
          LC = 3;
        }
        else{
          MC = 3;
        }
      }
      else if (Gfrequency[i] > Rfrequency[i] && Gfrequency[i] > Bfrequency[i] && Gfrequency[i] < 100 && Rfrequency[i] > Bfrequency[i]) {
        Serial.println("blue");
        if(i == 0) {
          LC = 2;
        }
        else{
          MC = 2;
        }
      }
      else if (Gfrequency[i] > Rfrequency[i] && Gfrequency[i] > Bfrequency[i] && Gfrequency[i] < 100 && Rfrequency[i] < Bfrequency[i]) {
        Serial.println("red");
        if(i == 0) {
          LC = 3;
        }
        else{
          MC = 3;
        }
        
      }
      else if (Gfrequency[i] > Rfrequency[i] && Gfrequency[i] > Bfrequency[i] && Gfrequency[i] > 100) {
        Serial.println("black");
        if(i == 0) {
          LC = 0;
        }
        else{
          MC = 0;
        }
      }
      else {
        Serial.println("ground");
        if(i == 0) {
          LC = 1;
        }
        else{
          MC = 1;
        }
     }
  }

  if(LC > 1 && MC == 0) {
    Serial.println("Going Straight");
    
    sendEvent('P', 9);
  }
  if(LC == 0 && MC == 0) {
    Serial.println("MAT!");
  }
  if(LC == 0 && MC == 1) {
    Serial.println("TURN");
  }
  

}

void proximitySensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(LeftFrontProximity, INPUT);
  LeftFrontDuration = pulseIn(LeftFrontProximity, HIGH);
  // Convert the time into a distance
  LeftFrontCm = (LeftFrontDuration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  pinMode(RightFrontProximity, INPUT);
  RightFrontDuration = pulseIn(RightFrontProximity, HIGH);
  RightFrontCm = (RightFrontDuration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
 
  Serial.println(LeftFrontCm);
  if(LeftFrontCm <= 10 && allowedToExecute && LeftFrontCm >0) {
    sendEvent('L', 9);
  }

  Serial.println(RightFrontCm);
  if(RightFrontCm <= 10 && allowedToExecute && RightFrontCm>0) {
    sendEvent('R', 9);
  }
}

void checkValues() {

}
