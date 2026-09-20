#include "GerenciadorWiFi.h"

#include <WiFi.h>

#if __has_include("ConfiguracaoLocal.h")
#include "ConfiguracaoLocal.h"
#else
constexpr char WIFI_SSID[] = "";
constexpr char WIFI_SENHA[] = "";
#endif

namespace {
constexpr unsigned long INTERVALO_TENTATIVA_WIFI_MS = 15000;
}

void GerenciadorWiFi::iniciar() {
  _configurado = WIFI_SSID[0] != '\0';
  WiFi.mode(WIFI_STA);

  if (!_configurado) {
    Serial.println("Wi-Fi sem configuracao local; operacao somente local.");
    return;
  }

  WiFi.begin(WIFI_SSID, WIFI_SENHA);
  _ultimaTentativaMillis = millis();
  Serial.println("Conexao Wi-Fi iniciada.");
}

void GerenciadorWiFi::atualizar() {
  if (!_configurado || conectado()) {
    return;
  }

  const unsigned long momentoAtualMillis = millis();
  if (momentoAtualMillis - _ultimaTentativaMillis <
      INTERVALO_TENTATIVA_WIFI_MS) {
    return;
  }

  WiFi.disconnect();
  WiFi.begin(WIFI_SSID, WIFI_SENHA);
  _ultimaTentativaMillis = momentoAtualMillis;
  Serial.println("Nova tentativa de conexao Wi-Fi.");
}

bool GerenciadorWiFi::conectado() const {
  return _configurado && WiFi.status() == WL_CONNECTED;
}

bool GerenciadorWiFi::configurado() const {
  return _configurado;
}
