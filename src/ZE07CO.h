#ifndef ZE07CO_h
#define ZE07CO_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class ZE07CO {
  public:
    ZE07CO();

    void begin(SoftwareSerial *serialname);
    void setMode(int m = 0);
    void requestCO();
    float readCO();

  private:
    SoftwareSerial *_Serial;
};

#endif
#ifndef ZE07CO_h
#define ZE07CO_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class ZE07CO {
  public:
    ZE07CO(HardwareSerial *Serial);
    ZE07CO(SoftwareSerial *Serial);
    
    void setMode(int m = 0);
    void requestCO();
    float readCO();

  private:
    Stream *_Serial;
};

#endif
