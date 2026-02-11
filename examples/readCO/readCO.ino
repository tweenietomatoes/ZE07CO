#include <SoftwareSerial.h>
#include <ZE07CO.h>

SoftwareSerial sensorSerial(6, 7); // RX, TX

ZE07CO sensor(sensorSerial);

void setup() {
  Serial.begin(9600);
  sensorSerial.begin(9600);
}

void loop() {
  float ppm = sensor.readCO();
  if (ppm >= 0) {
    Serial.print("CO: ");
    Serial.print(ppm, 1);
    Serial.println(" ppm");
  }
  delay(1000);
}
