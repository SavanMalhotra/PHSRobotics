#include <Wire.h>
char x;//holds character that will be sent to other arduino
bool allowedToExecute = true;//used to determine if an object has already been detected or not

int trigPin = 9;//trigger pin for all sensors

int echoPin1 = 12;//front left proximity sensor
int echoPin2 = 13;//front right proximity sensor
int echoPin3 = 5;//claw proximity sensor

void setup() {
  Serial.begin (9600);
  
  Wire.begin();//Used for conenction between arduinos
  Wire.onReceive(receiveEvent);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
}

void loop() {
  long duration1, distance1;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;
  Serial.print ("Sensor1  ");
  Serial.print (distance1);
  Serial.println("cm");
  if(distance1 <= 20 && allowedToExecute) {
    Serial.println("a was sent??");
    sendEvent('A', 9);
    Serial.println("a was sent??");  
  }
  delay(20);//delay added to allow code to process and reset
  
  long duration2, distance2;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2= (duration2/2) / 29.1;
  Serial.print("Sensor2  ");
  Serial.print(distance2);
  Serial.println("cm");
  if(distance2 <= 20 && allowedToExecute) {
    Serial.println("a was sent??");
    sendEvent('A', 9);
    Serial.println("a was sent??");  
  }
  delay(20);//delay added to allow code to process and reset
}

void receiveEvent(int bytes) {
  x = Wire.read();
  Serial.println(x);
  if(x == 'R') {
    allowedToExecute = true;
  }
}

void sendEvent(char val, int id) {
  Serial.println(val);
  allowedToExecute = false;
  Wire.beginTransmission(id);
  Wire.write(val);
  Wire.endTransmission(id);
  Serial.println(val);
}
