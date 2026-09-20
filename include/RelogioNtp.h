#pragma once

#include <Arduino.h>
#include <time.h>

class RelogioNtp {
public:
  void iniciar();
  void atualizar(bool wifiConectado);
  bool sincronizado() const;
  time_t agoraUtc() const;

private:
  bool _sincronizado = false;
  unsigned long _ultimaVerificacaoMillis = 0;
};
