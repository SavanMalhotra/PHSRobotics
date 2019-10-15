//This method will be used to detect if there is a object located infront of the robot
//If there is an object detected, it will check to see if that object has a color associated with it
int pin = 0;   //initializes the analog pin number as an integer             
int distance = 0;  //initializes the variable, distance. value WILL BE CHANGED, just an initlaization. It could be set to anything.             

void setup()
{
 Serial.begin(9600);  //sets data rate to 9600 bps (bits per second)           
}

void loop()
{
 distance = analogRead(pin);  //gets the distance from the sensor to the object - need to test to identify the precision and the percentage off 
 Serial.println(distance); // Prints distance value in console           
 delay(100);   //delays for 0.1 seconds and then repeats the process.                
}
