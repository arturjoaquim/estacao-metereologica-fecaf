#include "RelogioNtp.h"

#include <WiFi.h>

#include "Constantes.h"

namespace {
constexpr long FUSO_HORARIO_SEGUNDOS = 0;
constexpr int HORARIO_VERAO_SEGUNDOS = 0;
constexpr char SERVIDOR_NTP_PRIMARIO[] = "pool.ntp.org";
constexpr char SERVIDOR_NTP_SECUNDARIO[] = "time.nist.gov";
constexpr time_t PRIMEIRO_TIMESTAMP_VALIDO = 1704067200;
}

void RelogioNtp::iniciar() {
  configTime(FUSO_HORARIO_SEGUNDOS, HORARIO_VERAO_SEGUNDOS,
             SERVIDOR_NTP_PRIMARIO, SERVIDOR_NTP_SECUNDARIO);
}

void RelogioNtp::atualizar(bool wifiConectado) {
  if (!wifiConectado) {
    _sincronizado = false;
    return;
  }

  const unsigned long momentoAtualMillis = millis();
  if (momentoAtualMillis - _ultimaVerificacaoMillis <
      INTERVALO_RELOGIO_NTP_MS) {
    return;
  }

  _ultimaVerificacaoMillis = momentoAtualMillis;
  _sincronizado = agoraUtc() >= PRIMEIRO_TIMESTAMP_VALIDO;
}

bool RelogioNtp::sincronizado() const {
  return _sincronizado;
}

time_t RelogioNtp::agoraUtc() const {
  return time(nullptr);
}
