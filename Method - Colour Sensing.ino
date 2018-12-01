// This code creates methods for sensing each colour 


void setup() {
  int color = 0;
}

// sets the output frequency
void frequencyScaling() {
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW); // I set the output frequency to be at 20% (idk if you want to change)
}

// read the RGB components
void readRGB() {
  double red = 0;
  double grn = 0;
  double = 0;
  int n = 10; // the amount of times to test the colour >> can change whenever
  for (int i = 0; i < n; ++i) {
    //read red component
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    red = red + pulseIn(outPin, LOW);
  
   //read green component
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
    grn = grn + pulseIn(outPin, LOW);
    
   //read blue component
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    blu = blu + pulseIn(outPin, LOW);
  }
  red = red/n; // divides total read by 10 to find average to ensure accuracy 
  grn = grn/n;
  blu = blu/n;
}

// gets the actual colour
int getColor() {  
  readRGB();
  
  // these values are probably not correct, i just found this online and put it here for future referencing for format
  // this code is programmed for the output frequency scaling to be at 100% (S0 & S1 = H) - I was reading through it and 
  // it says that usually the frequency is at 20% (S0 H, S1 0)
  // to find the actual boundaries, we'll have to test it out I think
  
  // also the numbers in this code confuse me because in RGB parameters, red is detected when R is the max value 
  // (same applies for blue and green... but this is not the case here???? help)
  
  if (red > 8 && red < 18 && grn > 9 && grn < 19 && blu > 8 && blu < 16) color = 1; // white
  else if (red > 80 && red < 125 && grn > 90 && grn < 125 && blu > 80 && blu < 125) color = 2; // black
  else if (red > 12 && red < 30 && grn > 40 && grn < 70 && blu > 33 && blu < 70) color = 3; // red
  else if (red > 10 && red < 20 && grn > 10 && grn < 25 && blu > 20 && blu < 38) color = 4; // yellow
  else if (red > 65 && red < 125 && grn > 65 && grn < 115 && blu > 32 && blu < 65) color = 5; // blue
  else  color = 6; // structure
}
