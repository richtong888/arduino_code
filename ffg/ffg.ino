#define led_pin 11
#define fsr_pin A0
#define sec_pin A2
// first define the pins
const int DirPin = 7;    // this pin defines direction CW or CCW
const int StepPin = 5;   // pulse this pin to move one step
//const int fsr_pin = 14;// force snesor place

const int SPR = 100;    // Steps per revolution
const int ONCE = 500;

void setup()
{
  Serial.begin(57600);
  // Make pins as Outputs
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
}
void loop()
{
  int fsr_value = analogRead(fsr_pin); // 讀取FSR
  int sec_value = analogRead(sec_pin);
  int led_value = map(fsr_value, 0, 1023, 0, 255); // 從0~1023映射到0~255
  analogWrite(led_pin, led_value); // 改變LED亮度
  Serial.print("sensor1 is ");
  Serial.println(fsr_value);
  Serial.print("sensor2 is ");
  Serial.println(sec_value);
  //Serial.println(led_value);
  Serial.println("-------------");
  delay(100);
  
  if(Serial.available())
  {
    char ch=Serial.read();
    if(ch=='c'||ch=='C')
    {
      // First let us rotate shaft clockwise
      digitalWrite(DirPin, HIGH);   // defines the direction to clockwise
      Serial.println("clockwise");
      // Pulse the step pin
      for(int x = 0; x < SPR; x++)
      {
        digitalWrite(StepPin, HIGH);
        delayMicroseconds(1200);
        digitalWrite(StepPin, LOW);
        delayMicroseconds(1200);
      }
      delay(1000); // Short delay of one second
    }
    
    if(ch=='o'||ch=='O')
    {
      // Now rotate shaft counterclockwise
      digitalWrite(DirPin, LOW);
      Serial.println("counterclockwise");
      // Again pulse the step pin
      for(int x = 0; x < SPR; x++)
      {
        digitalWrite(StepPin, HIGH);
        delayMicroseconds(1200);
        digitalWrite(StepPin, LOW);
        delayMicroseconds(1200);
      }
      delay(1000); // Short delay of one second            
    }
    
        if(ch=='m'||ch=='M')
    {
      // Now rotate shaft counterclockwise
      digitalWrite(DirPin, HIGH);
      Serial.println("Do Once");
      // Again pulse the step pin
      for(int x = 0; x < ONCE; x++)
      {
        digitalWrite(StepPin, HIGH);
        delayMicroseconds(1200);
        digitalWrite(StepPin, LOW);
        delayMicroseconds(1200);
      }
      delay(3000); // Short delay of one second  
      digitalWrite(DirPin, LOW); 
      for(int x = 0; x < ONCE; x++)
      {
        digitalWrite(StepPin, HIGH);
        delayMicroseconds(1200);
        digitalWrite(StepPin, LOW);
        delayMicroseconds(1200);
      }
      delay(1000); // Short delay of one second          
    }

  } 
}
