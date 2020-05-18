/*#define led_pin 11
#define fsr_pin A0
int cnt=0;

void setup()
{
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);
  
}

void loop()
{
  int fsr_value = analogRead(fsr_pin); 
  int led_value = map(fsr_value, 0, 1023, 0, 255); 
  
  if (fsr_value>=800)
    cnt=1; 
  if (cnt>=50)
    Serial.println("WARNING!!!!");  
  analogWrite(led_pin, led_value); 
  Serial.println(fsr_value);
  Serial.println(led_value);
  Serial.println(cnt);
  Serial.println("-------------");
  delay(100);
}*/


#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <string.h>
//#define led_pin 11
#define fsr_pin_0 A0
#define fsr_pin_1 A1
#define fsr_pin_2 A2
#define fsr_pin_3 A3
#define fsr_pin_4 A4
#define fsr_pin_5 A5
ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher force_sensor("force_sensor",&str_msg);//chatter is a topic and msg is a function
char crash[]="000000";
char one[]="1";
char two[]="2";
char three[]="3";
char four[]="4";
char five[]="5";
char six[]="6";

unsigned int motor_pin[] = { 2,
           3,  4,
           5,  6,
           7,  8,
           9, 10,
          11, 12, 13};
unsigned int size = sizeof(motor_pin) / sizeof(motor_pin[0]);
unsigned int motor_number = 0;
  
  void setup()
  {
    nh.initNode();
    nh.advertise(force_sensor);
    for (int i = 0; i <= size; i++)
  {
    pinMode(motor_pin[2 * i - 2], OUTPUT);
    digitalWrite(motor_pin[2 * i - 1], LOW);
    digitalWrite(motor_pin[2 * i], LOW);
  }
 // pinMode(led_pin_1,OUTPUT);
 //Serial.begin(115200);
   
}

void loop()
{
  int fsr_value_0 = analogRead(fsr_pin_0); 
  
  int fsr_value_1 = analogRead(fsr_pin_1); 
  
  int fsr_value_2 = analogRead(fsr_pin_2); 
  
  int fsr_value_3 = analogRead(fsr_pin_3); 
  
  int fsr_value_4 = analogRead(fsr_pin_4); 
  
  int fsr_value_5 = analogRead(fsr_pin_5); 
  //int led_value = map(fsr_value_0, 0, 1023, 0, 255); 

  if (fsr_value_0>=500)
      crash[0] = '1';
  else
    crash[0]='0';
      //strcat(crash,one);
      //   strcpy(crash, "000000");
  if (fsr_value_1>=500)
      crash[1] = '1';
  else
    crash[1]='0';      
      //strcat(crash,two);
  if (fsr_value_2>=500)
      crash[2] = '1';
  else
    crash[2]='0';
      //strcat(crash,three);
  if (fsr_value_3>=500)
      crash[3] = '1';
  else
    crash[3]='0';
      //strcat(crash,four);
  if (fsr_value_4>=500)
      crash[4] = '1';
  else
    crash[4]='0';
      //strcat(crash,five);
  if (fsr_value_5>=500)
      crash[5] = '1';
  else
    crash[5]='0';
      //strcat(crash,six);
  
//    crash = "000000"; 

  str_msg.data = crash;
  force_sensor.publish(&str_msg);
  nh.spinOnce();
  delay(1000);
  
  motor_number = Serial.parseInt();
  if ((motor_number > 0) && (motor_number <= (size / 2))) throwing_garbages(motor_number);
  
}

void throwing_garbages(int number)
{
  int motor_pos = 2 * number - 1;
  int motor_neg = 2 * number;
  digitalWrite(motor_pin[motor_pos], HIGH);
  digitalWrite(motor_pin[motor_neg], LOW);
  Serial.print(number);
  delay(4500);
  digitalWrite(motor_pin[motor_pos], LOW);
  digitalWrite(motor_pin[motor_neg], LOW);
}
