#include "PublicadorThingSpeak.h"

#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

#include "Constantes.h"

#if __has_include("ConfiguracaoLocal.h")
#include "ConfiguracaoLocal.h"
#else
constexpr unsigned long THINGSPEAK_CANAL_ID = 0;
constexpr char THINGSPEAK_CHAVE_ESCRITA[] = "";
constexpr char THINGSPEAK_CERTIFICADO_CA[] = "";
#endif

namespace {
constexpr char ENDPOINT_THINGSPEAK[] = "https://api.thingspeak.com/update";
constexpr unsigned long TEMPO_LIMITE_HTTP_MS = 3000;

int qualidadeParaCodigo(const LeituraMQ& leitura) {
  switch (leitura.qualidade) {
    case QualidadeAr::Boa:
      return 1;
    case QualidadeAr::Moderada:
      return 2;
    case QualidadeAr::Ruim:
      return 3;
    case QualidadeAr::Pessima:
      return 4;
    case QualidadeAr::Indisponivel:
    case QualidadeAr::Aquecendo:
    default:
      return 0;
  }
}

int mascaraSaude(const LeituraEstacao& leitura) {
  int mascara = 0;
  if (leitura.dht.ok) {
    mascara |= 1;
  }
  if (leitura.bmp.ok) {
    mascara |= 2;
  }
  if (qualidadeParaCodigo(leitura.mq135) != 0) {
    mascara |= 4;
  }
  return mascara;
}
}

bool PublicadorThingSpeak::configurado() const {
  return configuracaoValida();
}

bool PublicadorThingSpeak::configuracaoValida() const {
  return THINGSPEAK_CANAL_ID != 0 && THINGSPEAK_CHAVE_ESCRITA[0] != '\0' &&
         THINGSPEAK_CERTIFICADO_CA[0] != '\0';
}

bool PublicadorThingSpeak::publicar(const LeituraEstacao& leitura,
                                    int rssiDbm) {
  if (!configuracaoValida() || !leitura.wifiConectado) {
    return false;
  }

  WiFiClientSecure cliente;
  cliente.setCACert(THINGSPEAK_CERTIFICADO_CA);

  HTTPClient http;
  http.setConnectTimeout(TEMPO_LIMITE_HTTP_MS);
  http.setTimeout(TEMPO_LIMITE_HTTP_MS);
  if (!http.begin(cliente, ENDPOINT_THINGSPEAK)) {
    Serial.println("Nao foi possivel iniciar HTTPS do ThingSpeak.");
    return false;
  }

  String corpo = "api_key=";
  corpo += THINGSPEAK_CHAVE_ESCRITA;
  corpo += "&field1=";
  corpo += leitura.dht.ok ? String(leitura.dht.temperatura, 2) : "";
  corpo += "&field2=";
  corpo += leitura.dht.ok ? String(leitura.dht.umidade, 2) : "";
  corpo += "&field3=";
  corpo += leitura.bmp.ok ? String(leitura.bmp.pressao, 2) : "";
  corpo += "&field4=";
  corpo += qualidadeParaCodigo(leitura.mq135) == 0
               ? ""
               : String(leitura.mq135.raw);
  corpo += "&field5=";
  corpo += qualidadeParaCodigo(leitura.mq135) == 0
               ? ""
               : String(leitura.mq135.percentual, 2);
  corpo += "&field6=";
  corpo += qualidadeParaCodigo(leitura.mq135);
  corpo += "&field7=";
  corpo += mascaraSaude(leitura);
  corpo += "&field8=";
  corpo += rssiDbm;

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  const int codigoHttp = http.POST(corpo);
  http.end();

  if (codigoHttp < 200 || codigoHttp >= 300) {
    Serial.print("Falha ao publicar no ThingSpeak. HTTP: ");
    Serial.println(codigoHttp);
    return false;
  }

  Serial.print("ThingSpeak atualizado. HTTP: ");
  Serial.println(codigoHttp);
  return true;
}
