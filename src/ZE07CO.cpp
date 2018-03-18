#include "Arduino.h"
#include "ZE07CO.h"

ZE07CO::ZE07CO() {
_Serial = NULL;
}

ZE07CO::begin(SoftwareSerial *serialname)
{
 _Serial = serialname;
 _Serial->begin(9600);
}

void ZE07CO::setMode (int m) {

const byte Start      = 0xFF;
const byte Sensor     = 0x01;
const byte Command    = 0x78;
byte Mode;
if (m == 1) {
           Mode       = 0x41;
         } else {
           Mode       = 0x40;
         }
const byte Zero       = 0x00;
const byte Checksum   = 0x46;

   byte request[9] = {
    Start,
    Sensor,
    Command,
    Mode,
    Zero,
    Zero,
    Zero,
    Zero,
    Checksum
    };

  _Serial->write(request, 9);

  _Serial->flush();
}

void ZE07CO::requestCO()
{

const byte Start      = 0xFF;
const byte Sensor     = 0x01;
const byte Command    = 0x86;
const byte Zero       = 0x00;
const byte Checksum   = 0x79;

   byte request[9] = {
    Start,
    Sensor,
    Command,
    Zero,
    Zero,
    Zero,
    Zero,
    Zero,
    Checksum
    };

  _Serial->write(request, 9);

  _Serial->flush();

}

float ZE07CO::readCO()
{

  while (_Serial->available() > 0 && _Serial->peek() != 0xFF) {
    _Serial->read();
    delay(1);
  }

  _Serial->readBytes(response, 9);

  if (response[0] != 0xFF && (response[1] != 0x86 || response[1] != 0x04))
    {
      return -1;
    }

  byte checksum = 0;
  for (int i = 1; i < 8; i++) {
    checksum += response[i];
  }
  checksum = 0xFF - checksum;
  checksum++;

   if (response[8] != checksum) {
     return -2;
   }

    int low  = (int)response[4];
    int high = (int)response[5];
    float ppm = (high * 256 + low) * 0.1;
    return ppm;
}
