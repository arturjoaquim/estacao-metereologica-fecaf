#pragma once

#include <Arduino.h>

class GerenciadorWiFi {
public:
  void iniciar();
  void atualizar();
  bool conectado() const;
  bool configurado() const;

private:
  bool _configurado = false;
  unsigned long _ultimaTentativaMillis = 0;
};
