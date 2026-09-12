#pragma once
#include <Arduino.h>
#include <Adafruit_BMP085_U.h>

struct LeituraBMP {
  float pressao;
  bool ok;
};

class BMPSensor {
public:
  BMPSensor(int sensorId);
  bool iniciar();
  LeituraBMP ler();
private:
  Adafruit_BMP085_Unified _bmp;
};
