#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
int Rfrequency = 0;
int Bfrequency = 0;
int Gfrequency = 0;
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}
void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  Rfrequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  //Serial.print("R= ");//printing name
  //Serial.print(Rfrequency);//printing RED color frequency
  //Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  Gfrequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  //Serial.print("G= ");//printing name
  //Serial.print(Gfrequency);//printing GREEN color frequency
  //Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  Bfrequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  //Serial.print("B= ");//printing name
  //Serial.print(Bfrequency);//printing BLUE color frequency
  //Serial.println("  ");
  delay (200);
  if (Rfrequency < 20 && Gfrequency < 20 && Bfrequency < 10) {
    Serial.println("white");
  }
  else if (Rfrequency < 50 && Gfrequency < 50 && Bfrequency < 20 && Gfrequency > Rfrequency) {
    Serial.println("yellow");
  }
  else if (Gfrequency > Rfrequency*2 && Bfrequency < 30) {
    Serial.println("red");
  }
  else if (Rfrequency >= Gfrequency*1.5 && Bfrequency < 30) {
    Serial.println("blue");
  }
  else if (Rfrequency >= 150 && Gfrequency >= 150 && Bfrequency < 100) {
    Serial.println("black");
  }
  
  delay(1000);
  
  
}
