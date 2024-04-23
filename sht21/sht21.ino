/****************************************************************
*  SHT21_Demo
*
*  An example sketch that reads the sensor and prints the
*  relative humidity to the serial port
* 
***************************************************************/

#include <Wire.h>
#include "SHT21.h"

SHT21 SHT21;

void setup()
{
  Wire.begin(0,2);  //0=SDA(GPIO0)(PIN 5);; 2=SCL(GPIO2)(PIN3)
  Serial.begin(9600);
  Serial.println("Comenzando a medir");
}

void loop()
{
  Serial.print("Humidity(%RH): ");
  Serial.println(SHT21.getHumidity());
  Serial.print("Temperature(C): ");
  Serial.println(SHT21.getTemperature());
  Serial.println("=============");
  delay(1000);
}