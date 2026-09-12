#pragma once
#include <Arduino.h>

struct LeituraMQ {
  int raw;
  float percentual;
  const char* qualidade;
};

class MQ135Sensor {
public:
  MQ135Sensor(int pino);
  void iniciar();
  LeituraMQ ler();
private:
  int _pino;
};
