#pragma once

#include <Arduino.h>

#include "LeituraEstacao.h"

class PublicadorThingSpeak {
public:
  bool configurado() const;
  bool publicar(const LeituraEstacao& leitura, int rssiDbm);

private:
  bool configuracaoValida() const;
};
