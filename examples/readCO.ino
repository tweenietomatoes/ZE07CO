#include <ZE07CO.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial2(6,7);

ZE07CO ze07co;

void setup()
{
ze07co.begin(&Serial2);
Serial.begin(9600);
}

void loop()
{
Serial.println(ze07co.readCO());
              //Default mode is active, if you want to switch mode
              //ze07co.setMode(1) ,then you need to request first
              //ze07co.requestCO() and then readCO();
              //
delay(1000);
}
