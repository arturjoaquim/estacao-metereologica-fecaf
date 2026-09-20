#pragma once
#include <Arduino.h>

enum class QualidadeAr {
  Indisponivel,
  Aquecendo,
  Boa,
  Moderada,
  Ruim,
  Pessima
};

struct LeituraMQ {
  int raw;
  float percentual;
  QualidadeAr qualidade;
};

const char* qualidadeArParaTexto(QualidadeAr qualidade);

class MQ135Sensor {
public:
  MQ135Sensor(int pino);
  void iniciar();
  LeituraMQ ler();
private:
  int _pino;
  unsigned long _momentoInicio;
  bool _iniciado;
};
