#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <string.h>
#define StepPin 5
#define DirPin 8
const int SPR = 200;    // Steps per revolution


void chatterCallback(const std_msgs::String& msg)
{
    // First let us rotate shaft clockwise
     // defines the direction to clockwise
  Serial.println("out1");
  if(msg.data=="open")
  {
    //ROS_INFO("out2");
    Serial.println("out2");
    digitalWrite(DirPin, HIGH);
    for(int x = 0; x < SPR; x++)
    {
      digitalWrite(StepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(StepPin, LOW);
      delayMicroseconds(1000);
    }
    delay(1000); // Short delay of one second
  }
  


  if(msg.data=="close")
  {
    //ROS_INFO("out3");
      Serial.println("out3");
    digitalWrite(DirPin, LOW);
     // Again pulse the step pin
    for(int x = 0; x < SPR; x++)
    {
      digitalWrite(StepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(StepPin, LOW);
      delayMicroseconds(1000);
    }
    delay(1000); // Short delay of one second
  }
  // Now rotate shaft counterclockwise
  
}

ros::NodeHandle nh;
//std_msgs::String str_msg;
//ros::Subscriber sub = nh.subscribe("pick_command", 1000, chatterCallback);
ros::Subscriber<std_msgs::String>sub("pick_command",&chatterCallback);

void setup()
{
  nh.initNode();
  nh.subscribe(sub);
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
}
void loop()
{
  nh.spinOnce();
  delay(1000);

}
