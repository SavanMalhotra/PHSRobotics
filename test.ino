//this program turns a motor on for 5 seconds and then turns it off for 1 second anc continues in a loop

int motorOne = 9;

void setup() {
 pinMode(motorOne, OUTPUT);
}
void loop() {
 on(5000, motorOne);
 off(1000, motorOne);
}

void on(int duration, int pin){
 digitalWrite(pin, LOW);
 delay(duration);
}
 
void off(int duration, int pin){
 digitalWrite(pin, HIGH);
 delay(duration);
}
