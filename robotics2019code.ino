int trigPin = 2;    // Trigger
int frontProximity = 3;    // FrontProximity Sensor echo pin
int leftProximity = 4;    // LeftProximity Sensor echo pin
int rightProximity = 5; // RightProximity Sensor echo pin
long frontDuration, frontCm, leftDuration, leftCm, rightDuration, rightCm;

bool front, left, right = true; // means there is no blockage in that direction

int proximityDistanceVariable = 10; // CHANGE THIS 

#define enable 13
#define sideMotorA 9 // control output 1 of the side motors
#define sideMotorB 10 // control output 2 of the side motors
#define frontMotorA 11 // control output 1 of the front and back motors
#define frontMotorB 12 // control output 2 of the front and back motors


void setup() {  
  pinMode(trigPin, OUTPUT);
  pinMode(frontProximity, INPUT);
  pinMode(leftProximity, INPUT);
  pinMode(rightProximity, INPUT);

  pinMode (enable, OUTPUT);
  pinMode (sideMotorA, OUTPUT);
  pinMode (sideMotorB, OUTPUT); 
  pinMode (frontMotorA, OUTPUT);
  pinMode (frontMotorB, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  if (front == true) {
    forward();
  }
  else if (front == false) {
    if (left == true) {
      left();
    }
    else if (right == true) {
      right();
    }
    else {
      backward();
    }
  }
  
}

void proximitySensors() {
  
  // FRONT PROXIMITY
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(frontProximity, INPUT);
  frontDuration = pulseIn(frontProximity, HIGH);
  // Convert the time into a distance
  frontCm = (frontDuration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  
  // LEFT PROXIMITY
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(leftProximity, INPUT);
  leftDuration = pulseIn(leftProximity, HIGH);
  leftCm = (leftDuration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  // RIGHT PROXIMITY
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(rightProximity, INPUT);
  rightDuration = pulseIn(rightProximity, HIGH);
  rightCm = (rightDuration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  Serial.println(frontCm);
  if(frontCm <= proximityDistanceVariable && allowedToExecute && frontCm >0) {
    front = false;
  }

  Serial.println(leftCm);
  if(leftCm <= proximityDistanceVariable && allowedToExecute && leftCm >0) {
    left = false;
  }

  Serial.println(rightCm);
  if(rightCm <= proximityDistanceVariable && allowedToExecute && rightCm >0) {
    right = false;
  }
  
}

void forward() {
  digitalWrite (enable, HIGH);
  digitalWrite (sideMotorA, HIGH);
  digitalWrite (sideMotorB, LOW);
}

void backward() {
  digitalWrite (enable, HIGH);
  digitalWrite (sideMotorA, LOW);
  digitalWrite (sideMotorB, HIGH);
}

void left() {
  digitalWrite (enable, HIGH);
  digitalWrite (frontMotorA, HIGH);
  digitalWrite (frontMotorB, LOW);
}

void right() {
  digitalWrite (enable, HIGH);
  digitalWrite (frontMotorA, LOW);
  digitalWrite (frontMotorB, HIGH);
}

void stop() {
  digitalWrite (enable, LOW);
}
