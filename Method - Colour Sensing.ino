// This code creates methods for sensing each colour 
// websites used: https://howtomechatronics.com/tutorials/arduino/arduino-color-sensing-tutorial-tcs230-tcs3200-color-sensor/
// https://www.instructables.com/id/Arduino-Color-Detection/
// https://randomnerdtutorials.com/arduino-color-sensor-tcs230-tcs3200/ (use this one to build actual circuit)

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define outPin 8

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  int color = 0;
  double red = 0;
  double grn = 0;
  double blue = 0;
  
// sets the output frequency
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW); // I set the output frequency to be at 20% (idk if you want to change)
}

// actual tester
void loop() {
  Serial.println(getColor); // should print out an integer 1-6
  delay (5000)
}


// read red 
double readRd() {
   int n = 10; // the amount of times to test the colour >> can change whenever
  for (int i = 0; i < n; ++i) {
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    red = red + pulseIn(outPin, LOW);
  }
  red = red/n;
  return red;
}

// read green
double readGrn() {
   int n = 10; // the amount of times to test the colour >> can change whenever
  for (int i = 0; i < n; ++i) {
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
    grn = grn + pulseIn(outPin, LOW);
  }
  grn = grn/n;
  return grn;
}

// read blue
double readBlu() {
   int n = 10; // the amount of times to test the colour >> can change whenever
  for (int i = 0; i < n; ++i) {
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    blu = blu + pulseIn(outPin, LOW);
  }
  blu = blu/n;
  return blu;
}

// gets the actual colour
int getColor() {  
  readRd();
  readGrn();
  readBlu();
  
  // these values are probably not correct, i just found this online and put it here for future referencing for format
  // this code is programmed for the output frequency scaling to be at 100% (S0 & S1 = H) - I was reading through it and 
  // it says that usually the frequency is at 20% (S0 H, S1 0)
  // to find the actual boundaries, we'll have to test it out I think
  
  if (red > 8 && red < 18 && grn > 9 && grn < 19 && blu > 8 && blu < 16) color = 1; // white
  else if (red > 80 && red < 125 && grn > 90 && grn < 125 && blu > 80 && blu < 125) color = 2; // black
  else if (red > 12 && red < 30 && grn > 40 && grn < 70 && blu > 33 && blu < 70) color = 3; // red
  else if (red > 10 && red < 20 && grn > 10 && grn < 25 && blu > 20 && blu < 38) color = 4; // yellow
  else if (red > 65 && red < 125 && grn > 65 && grn < 115 && blu > 32 && blu < 65) color = 5; // blue
  else  color = 6; // structure
  
  return color;
}
