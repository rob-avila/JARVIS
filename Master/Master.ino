//i2c Master(UNO)
#include <Wire.h>

unsigned long currentTime;
unsigned long loopTime;

unsigned long currentTime2;
unsigned long loopTime2;

void setup()
{
  //Sets the master ID as value 5
  Wire.begin(5);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop()
{
  currentTime = millis();
  currentTime2 = millis();
  
  //Loop happens every 5 seconds
  if(currentTime >= (loopTime + 5000))
  {
    Wire.requestFrom(4,10);
    
    while(Wire.available())
    {
      char c = Wire.read();
      Serial.print(c);
    }
    Serial.println();
    
    loopTime=currentTime;
  }
  
  //Loop happens every 10 seconds
  if(currentTime2 >= (loopTime2 + 10000))
  {
    Wire.requestFrom(3,14);
    
    while(Wire.available())
    {
      char c = Wire.read();
      Serial.print(c);
    }
    Serial.println();
    
    loopTime2=currentTime2;
  }
  
}

void receiveEvent(int howMany)
{
  while(1 < Wire.available())
  {
    char c = Wire.read();
    Serial.print(c);
  }
  byte x = Wire.read();
  Serial.println(x);
}
