#pragma once
#include <Arduino.h>
#include <DHT.h>

struct LeituraDHT {
  float temperatura;
  float umidade;
  bool ok;
};

class DHTSensor {
public:
  DHTSensor(uint8_t pino, uint8_t tipo);
  void iniciar();
  LeituraDHT ler();
private:
  DHT _dht;
  bool _iniciado;
};
