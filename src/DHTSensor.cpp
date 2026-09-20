#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t pino, uint8_t tipo) : _dht(pino, tipo), _iniciado(false) {}

void DHTSensor::iniciar() {
  _dht.begin();
  _iniciado = true;
}

LeituraDHT DHTSensor::ler() {
  LeituraDHT l;
  if (!_iniciado) {
    l.temperatura = 0.0f;
    l.umidade = 0.0f;
    l.ok = false;
    return l;
  }

  l.umidade = _dht.readHumidity();
  l.temperatura = _dht.readTemperature();
  l.ok = !(isnan(l.umidade) || isnan(l.temperatura));
  return l;
}
