#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t pino, uint8_t tipo) : _dht(pino, tipo) {}

void DHTSensor::iniciar() {
  _dht.begin();
}

LeituraDHT DHTSensor::ler() {
  LeituraDHT l;
  l.umidade = _dht.readHumidity();
  l.temperatura = _dht.readTemperature();
  l.ok = !(isnan(l.umidade) || isnan(l.temperatura));
  return l;
}
