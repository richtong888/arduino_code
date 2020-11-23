#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int16MultiArray.h>

#define led_pin 11
#define fsr_pin A0
#define sec_pin A2
// first define the pins
const int DirPin = 7;    // this pin defines direction CW or CCW
const int StepPin = 5;   // pulse this pin to move one step
//const int fsr_pin = 14;// force snesor place

const int SPR = 100;    // Steps per revolution
const int ONCE = 500;

////////////////////ros define///////////
ros::NodeHandle nh;
std_msgs::Int16 int_msg1;
std_msgs::Int16 int_msg2;
ros::Publisher fsr1("fsr1", &int_msg1);
ros::Publisher fsr2("fsr2", &int_msg2);
//std_msgs::Int16MultiArray arr_msg;
//ros::Publisher fsr("fsr", &arr_msg);
/////////////////////////////////////////


void setup()
{
  Serial.begin(57600);
  // Make pins as Outputs
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
  nh.initNode();
  nh.advertise(fsr1);
  nh.advertise(fsr2);
// nh.advertise(fsr);
 
}
void loop()
{
  int fsr_value = analogRead(fsr_pin); // 讀取FSR
  int sec_value = analogRead(sec_pin);
  int led_value = map(fsr_value, 0, 1023, 0, 255); // mapping 1023 to 255
  analogWrite(led_pin, led_value); // change ked light
  Serial.print("sensor1 is ");
  Serial.println(fsr_value);
  Serial.print("sensor2 is ");
  Serial.println(sec_value);
  //Serial.println(led_value);
  Serial.println("-------------");
  //////////////transfer function///////////////
  int o1=0, o2=0;
  if(fsr_value==0)
    o1=0;
  if(fsr_value<=100)
    o1=fsr_value*0.01*0.15;
  else if(fsr_value<=200)
    o1=(fsr_value-100)*0.01*0.02+0.15;
  else if(fsr_value<=300)
    o1=(fsr_value-200)*0.01*0.08+0.17;
  else if(fsr_value<=400)
    o1=(fsr_value-300)*0.01*0.1+0.25; 
  else if(fsr_value<=500)
    o1=(fsr_value-400)*0.01*0.15+0.35;
  else if(fsr_value<=600)
    o1=(fsr_value-500)*0.01*0.4+0.5;
  else if(fsr_value<=700)
    o1=(fsr_value-600)*0.01*0.9+0.9;
  else if(fsr_value<=800)
    o1=(fsr_value-700)*0.01*1.7+1.8;  
  else if(fsr_value<=900)
    o1=(fsr_value-800)*0.01*6.5+3.5;
  else if(fsr_value<=1000)
    o1=(fsr_value-900)*0.01*90+10;   
  else if(fsr_value<=1024)
    o1=666666;                  
  ///////////////ros output//////////
  int_msg1.data=o1;
  fsr1.publish(&int_msg1);
  int_msg2.data=sec_value;
  fsr2.publish(&int_msg2);
  nh.spinOnce();
  //arr_msg.data[0]=fsr_value;
  //arr_msg.data[1]=sec_value;
  //fsr.publish(&arr_msg);
  //nh.spinOnce();
  ///////////////////////////////////
  delay(100);
  

}
