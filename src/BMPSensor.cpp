#include "BMPSensor.h"
#include <Adafruit_Sensor.h>

BMPSensor::BMPSensor(int sensorId) : _bmp(sensorId) {}

bool BMPSensor::iniciar() {
  return _bmp.begin();
}

LeituraBMP BMPSensor::ler() {
  LeituraBMP l;
  sensors_event_t event;
  _bmp.getEvent(&event);
  if (event.pressure) {
    l.pressao = event.pressure;
    l.ok = true;
  } else {
    l.pressao = 0.0f;
    l.ok = false;
  }
  return l;
}
