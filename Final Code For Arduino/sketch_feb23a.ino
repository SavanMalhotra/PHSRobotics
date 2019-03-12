#define S0 13
#define S1 12
#define S2 11
#define S3 10
#define sensorOut1 9
#define sensorOut2 8
int Rfrequency[2];
int Bfrequency[2];
int Gfrequency[2];

void setup() {
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
void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  Rfrequency[0] = pulseIn(sensorOut1, LOW);
  Rfrequency[1] = pulseIn(sensorOut2, LOW);
  // Printing the value on the serial monitor
  Serial.print("R1= ");//printing name
  Serial.print(Rfrequency[0]);//printing RED color frequency
  Serial.println("");
  Serial.print("R2= ");//printing name
  Serial.print(Rfrequency[1]);//printing RED color frequency
  Serial.println("");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  Gfrequency[0] = pulseIn(sensorOut1, LOW);
  Gfrequency[1] = pulseIn(sensorOut2, LOW);
  // Printing the value on the serial monitor
  Serial.print("G1= ");//printing name
  Serial.print(Gfrequency[0]);//printing RED color frequency
  Serial.println("");
  Serial.print("G2= ");//printing name
  Serial.print(Gfrequency[1]);//printing RED color frequency
  Serial.println("");
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
  Serial.print("B1= ");//printing name
  Serial.print(Bfrequency[0]);//printing RED color frequency
  Serial.println("");
  Serial.print("B2= ");//printing name
  Serial.print(Bfrequency[1]);//printing RED color frequency
  Serial.println("");
  
  //Serial.print("B= ");//printing name
  //Serial.print(Bfrequency);//printing BLUE color frequency
  //Serial.println("  ");
  delay (200);
  for (int i = 0; i < 2; i++) {
    if (Rfrequency[i] < 20 && Gfrequency[i] < 20 && Bfrequency[i] < 10) {
      Serial.println(i + ": white");
    }
    else if (Rfrequency[i] < 50 && Gfrequency[i] < 50 && Bfrequency[i] < 20 && Gfrequency[i] > Rfrequency[i]) {
      Serial.println(i + ": yellow");
    }
    else if (Gfrequency[i] > Rfrequency[i]*2 && Bfrequency[i] < 30) {
      Serial.println(i + ": red");
    }
    else if (Rfrequency[i] >= Gfrequency[i]*1.5 && Bfrequency[i] < 30) {
      Serial.println(i + ": blue");
    }
    else if (Rfrequency[i] >= 150 && Gfrequency[i] >= 150) {
      Serial.println(i + ": black");
    }
  }
  
  
  delay(1000);
  
  
}
