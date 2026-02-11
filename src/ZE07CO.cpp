#include "ZE07CO.h"

ZE07CO::ZE07CO(Stream &serial) : _serial(&serial) {}

byte ZE07CO::_checksum(const byte *data) {
  byte sum = 0;
  for (int i = 1; i < 8; i++) {
    sum += data[i];
  }
  return (~sum) + 1;
}

void ZE07CO::setMode(int m) {
  byte request[9] = {
    0xFF, 0x01, 0x78,
    (byte)(m == 1 ? 0x41 : 0x40),
    0x00, 0x00, 0x00, 0x00, 0x00
  };
  request[8] = _checksum(request);
  _serial->write(request, 9);
  _serial->flush();
}

void ZE07CO::requestCO() {
  byte request[9] = {
    0xFF, 0x01, 0x86,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x79
  };
  _serial->write(request, 9);
  _serial->flush();
}

float ZE07CO::readCO() {
  while (_serial->available() > 0 && _serial->peek() != 0xFF) {
    _serial->read();
  }

  if (_serial->readBytes(_response, 9) != 9) {
    return -1;
  }

  if (_response[0] != 0xFF) {
    return -1;
  }

  if (_response[8] != _checksum(_response)) {
    return -2;
  }

  int high, low;
  if (_response[1] == 0x04) {
    // Active upload: concentration at bytes 4-5
    high = _response[4];
    low = _response[5];
  } else if (_response[1] == 0x86) {
    // Q&A response: concentration at bytes 2-3
    high = _response[2];
    low = _response[3];
  } else {
    return -1;
  }

  return (high * 256 + low) * 0.1;
}
