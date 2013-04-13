//i2c Slave2(MICHELANGELO)
#include <Wire.h>
unsigned long currentTime;
unsigned long loopTime;

void setup()
{
  //Sets the slave ID to 3
  Wire.begin(3);
  currentTime = millis();
  loopTime = currentTime;
  Wire.onRequest(requestEvent);
}

byte x = 0;

void loop()
{
  currentTime = millis();
  
  if(currentTime >= (loopTime + 3000))
  {  
    Wire.beginTransmission(5);
    Wire.write("Slave2 incrementer is");
    Wire.write(x);
    Wire.endTransmission();
    
    x++;
    loopTime = currentTime;
  }

}

void requestEvent()
{
  Wire.write("This is slave2");
}
