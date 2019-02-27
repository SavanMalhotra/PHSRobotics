<h1>Arduino Code And Pin Declaration </h1>
<h4><b>The code in this folder is the code that will go on the arduinos. </b></h4>

Master Arduino - The Arduino connected to the proximity sensors 
  - Digital Pins
    - Pin 2: Trigger for all proximity sensors
    - Pin 3: Echo for Right proximity sensor
    - Pin 4: Echo for Left proximity sensor
  - Analog Pins
    - Pin 5: I2C Netowork Pin (Connects arduinos together, making them talk to one another and send information back and forth)
    - Pin 4: I2C Netowork Pin (Connects arduinos together, making them talk to one another and send information back and forth) 
    
Slave Arduino - The Arduino connected to the motors

The slave.ino file is designed to be uploaded to the slave arduino.
The master.ino file is designed to be uploaded to the master arduino.
