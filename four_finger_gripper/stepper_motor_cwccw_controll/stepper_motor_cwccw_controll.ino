// Drive Stepper motor using A4988 stepper motor driver
// for more info visit iknowvations.in

// first define the pins
const int DirPin = 2;    // this pin defines direction CW or CCW
const int StepPin = 3;   // pulse this pin to move one step
const int SPR = 200;    // Steps per revolution
const int ONCE = 600;

void setup()
{
  Serial.begin(57600);
  // Make pins as Outputs
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
}
void loop()
{
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
      delay(1000); // Short delay of one second  
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
