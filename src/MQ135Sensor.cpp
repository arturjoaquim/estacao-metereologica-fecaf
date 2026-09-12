#include "MQ135Sensor.h"
#include "Constantes.h"

MQ135Sensor::MQ135Sensor(int pino) : _pino(pino) {}

void MQ135Sensor::iniciar() {
  delay(20000); // tempo para sensor aquecer
}

LeituraMQ MQ135Sensor::ler() {
  LeituraMQ l;
  l.raw = analogRead(_pino);
  l.percentual = (l.raw / 4095.0f) * 100.0f;

  if (l.percentual < MQ_LIMIAR_BOA) {
    l.qualidade = "Boa";
  } else if (l.percentual < MQ_LIMIAR_MODERADA) {
    l.qualidade = "Moderada";
  } else if (l.percentual < MQ_LIMIAR_RUIM) {
    l.qualidade = "Ruim";
  } else {
    l.qualidade = "Pessima";
  }

  return l;
}
