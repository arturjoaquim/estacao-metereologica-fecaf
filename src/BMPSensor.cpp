#include "BMPSensor.h"
#include <Adafruit_Sensor.h>

BMPSensor::BMPSensor(int sensorId) : _bmp(sensorId), _disponivel(false) {}

bool BMPSensor::iniciar() {
  _disponivel = _bmp.begin();
  return _disponivel;
}

LeituraBMP BMPSensor::ler() {
  LeituraBMP l;
  if (!_disponivel) {
    l.pressao = 0.0f;
    l.ok = false;
    return l;
  }

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
