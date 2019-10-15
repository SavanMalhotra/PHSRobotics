// WIP - still need to create turnRight/Left methods
// ----- maybe should put move backwards x amount in the turning methods to ensure the turns never hit anything ??
// this code creates the methods for moving forwards, backwards, turning left, and turning right

const int pwm = 2 ;	// connect enable 1 (pin 6) of the IC to pin 2 of the Arduino; set as the PWM (pulse-width modulated signal to control the motor speed)
const int IN1 = 8 ; // connect input 1 (pin 5) of the IC to pin 8 of Arduino
const int IN2 = 9 ; // connect input 2 (pin 6) of the IC to pin 9 of Arduino

void setup()
{
pinMode(pwm,OUTPUT) ;  	//set pins as outputs
pinMode(IN1,OUTPUT) ; 	//
pinMode(IN2,OUTPUT) ;
}

// moves forward, motor goes in clockwise motion
void moveForward() { 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(pwm, 255);
}

// moves backward, motor goes in counter-clockwise motion
void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(pwm, 255);  
}

// motor stops
void brake() {
  digitalWrite(IN1, LOW); // or both could be high
  digitalWrite(IN2, LOW);
}

// we want our turns to turn via a centred pivot point, so one motor will turn forward and one will turn backward 
void turnRight() {
  
}
