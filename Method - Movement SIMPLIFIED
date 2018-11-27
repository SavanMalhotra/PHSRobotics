// here's an easier way to control the moving of the two motors

void setup() {
  Robot.begin();
}

// METHODS:

void moveForward() {
  Robot.motorsWrite(255,255); // 255 is max speed - adjust during testing phase
}

void moveBackward() {
  Robot.motorsWrite(-255,-255);
}

void brake() {
  Robot.motorsWrite(0,0);
}

void turnLeft() {
  Robot.motorsWrite(-255,255);
}

void turnRight() {
  Robot.motorsWrite(255,-255);
}
