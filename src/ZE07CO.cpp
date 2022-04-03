#include "Arduino.h"
#include "ZE07CO.h"

ZE07CO::ZE07CO()
{
  _Serial = NULL;
}

void ZE07CO::begin(SoftwareSerial *serialname)
{
  _Serial = serialname;
  _Serial->begin(9600);
}

void ZE07CO::setMode(int m)
{
  const byte Start = 0xFF;
  const byte Sensor = 0x01;
  const byte Command = 0x78;
  byte Mode;
  byte Checksum;
  if (m == 1)
  {
    Mode = 0x41;
    Checksum = 0x46;
  }
  else
  {
    Mode = 0x40;
    Checksum = 0x47;
  }
  const byte Zero = 0x00;

  byte request[9] = {
      Start,
      Sensor,
      Command,
      Mode,
      Zero,
      Zero,
      Zero,
      Zero,
      Checksum};

  _Serial->write(request, 9);

  _Serial->flush();
}

void ZE07CO::requestCO()
{
  const byte Start = 0xFF;
  const byte Sensor = 0x01;
  const byte Command = 0x86;
  const byte Zero = 0x00;
  const byte Checksum = 0x79;

  byte request[9] = {
      Start,
      Sensor,
      Command,
      Zero,
      Zero,
      Zero,
      Zero,
      Zero,
      Checksum};

  _Serial->write(request, 9);

  _Serial->flush();
}

float ZE07CO::readCO()
{

  while (_Serial->available() > 0 && _Serial->peek() != 0xFF)
  {
    _Serial->read();
    delay(1);
  }

  byte response[9];
  _Serial->readBytes(response, 9);

  if (response[0] != 0xFF && (response[1] != 0x86 || response[1] != 0x04))
  {
    return -1;
  }

  byte checksum = 0;
  for (int i = 1; i < 8; i++)
  {
    checksum += response[i];
  }
  checksum = 0xFF - checksum;
  checksum++;

  if (response[8] != checksum)
  {
    return -2;
  }
  int lowbit;
  int highbit;

  if (response[1] == 0x04)
  {
    lowbit = 5;
    highbit = 4;
  } else 
  {
    lowbit = 3;
    highbit = 2;
  }
  float ppm = ((int)response[highbit] * 256 + (int)response[lowbit]) * 0.1;
  return ppm;
}

void ZE07CO::debugResponse()
{

  while (_Serial->available() > 0 && _Serial->peek() != 0xFF)
  {
    _Serial->read();
    delay(1);
  }

  byte response[9];
  _Serial->readBytes(response, 9);

  Serial.begin(9600);
  for (int i=0;i<9;i++)
  {
    Serial.print (response[i]);
    Serial.print (" ");
  }
  Serial.println ("");
  
}
