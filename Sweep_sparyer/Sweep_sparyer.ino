/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include <ros.h>
#include <std_msgs/String.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(57600);
}

void loop() {
  if (Serial.available())
  {
    char ch=Serial.read();
    if (ch=='c'||ch=='C')
    {
      Serial.println("close");
      for (pos = 0; pos <= 90; pos += 1)
      { 
        myservo.write(pos);
        delay(5);    
      }  
    }

    if (ch=='o'||ch=='O')
    {
      Serial.println("open");
      for (pos = 90; pos >=0; pos -= 1)
      {
        myservo.write(pos);
        delay(5);
      }
    }

  }
  

  
 
}
