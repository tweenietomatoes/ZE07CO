#ifndef ZE07CO_h
#define ZE07CO_h

#include "Arduino.h"

class ZE07CO {
  public:
    ZE07CO(Stream &serial);

    void setMode(int m = 0);
    void requestCO();
    float readCO();

  private:
    Stream *_serial;
    byte _response[9];
    byte _checksum(const byte *data);
};

#endif
