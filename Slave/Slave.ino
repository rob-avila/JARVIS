//i2c Slave(LEONARDO)
#include <Wire.h>
int photoPin = 0;
byte photoValue;
int led = 13;

unsigned long currentTime;
unsigned long loopTime;

void setup()
{
  //Sets the slave ID to 4
  Wire.begin(4);
  pinMode(led,OUTPUT);
  Wire.onReceive(receiveEvent);
  Serial
}

void loop()
{


}

void receiveEvent(int howMany)
{
  char c;
 while(1 < Wire.available())
  {
    c = Wire.read();
  }
  if(c=='1')
  {
    digitalWrite(led, HIGH);
  }else
  {
    digitalWrite(led, LOW);
  }
}
