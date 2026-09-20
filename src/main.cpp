#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include "Constantes.h"
#include "DHTSensor.h"
#include "BMPSensor.h"
#include "MQ135Sensor.h"
#include "GerenciadorWiFi.h"
#include "PublicadorThingSpeak.h"
#include "RelogioNtp.h"
#include "LeituraEstacao.h"

// Instâncias dos módulos de sensor
DHTSensor sensorDHT(PIN_DHT, DHT22);
BMPSensor sensorBMP(BMP_SENSOR_ID);
int localizarDispositivosI2C() {
  int quantidadeDispositivos = 0;

  Serial.println("Procurando dispositivos I2C...");
  for (int endereco = I2C_ENDERECO_INICIAL_SCAN;
       endereco <= I2C_ENDERECO_FINAL_SCAN;
       endereco++) {
    Wire.beginTransmission(endereco);
    const byte erro = Wire.endTransmission();

    if (erro == 0) {
      Serial.print("Dispositivo I2C encontrado no endereco 0x");
      if (endereco < 0x10) {
        Serial.print("0");
      }
      Serial.println(endereco, HEX);
      quantidadeDispositivos++;
    }
  }

  if (quantidadeDispositivos == 0) {
    Serial.println("Nenhum dispositivo I2C respondeu.");
  }

  return quantidadeDispositivos;
}

MQ135Sensor sensorMQ(PIN_MQ135);
GerenciadorWiFi gerenciadorWiFi;
RelogioNtp relogioNtp;
PublicadorThingSpeak publicadorThingSpeak;

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);

  Serial.println(MENSAGEM_INICIAL);
  Serial.println("Inicializando sensores...");

  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  Serial.print("I2C iniciado: SDA GPIO ");
  Serial.print(PIN_I2C_SDA);
  Serial.print(" | SCL GPIO ");
  Serial.println(PIN_I2C_SCL);
  localizarDispositivosI2C();

  sensorDHT.iniciar();
  if (!sensorBMP.iniciar()) {
    Serial.println("BMP180/BMP085 indisponivel. Os demais sensores continuarão ativos.");
  }
  sensorMQ.iniciar();

  analogReadResolution(12);
  gerenciadorWiFi.iniciar();
  relogioNtp.iniciar();
  if (!publicadorThingSpeak.configurado()) {
    Serial.println(MENSAGEM_THINGSPEAK_NAO_CONFIGURADO);
  }
}

void imprimirCabecalhoLeitura() {
  Serial.println();
  Serial.println("--- Leitura da estação meteorológica ---");
}

void imprimirLeitura(const LeituraEstacao& leitura) {
  imprimirCabecalhoLeitura();

  if (!leitura.dht.ok) {
    Serial.println("DHT22 indisponivel. Verifique as conexoes e alimentacao.");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(leitura.dht.temperatura, 1);
    Serial.println(" °C");
    Serial.print("Umidade: ");
    Serial.print(leitura.dht.umidade, 1);
    Serial.println(" %");
  }

  if (!leitura.bmp.ok) {
    Serial.println("BMP180/BMP085 indisponivel. Verifique as conexoes I2C.");
  } else {
    Serial.print("Pressão: ");
    Serial.print(leitura.bmp.pressao, 1);
    Serial.println(" hPa");
  }

  if (leitura.mq135.qualidade == QualidadeAr::Aquecendo) {
    Serial.println(qualidadeArParaTexto(leitura.mq135.qualidade));
  } else if (leitura.mq135.qualidade == QualidadeAr::Indisponivel) {
    Serial.println("MQ-135 indisponivel. Verifique o sinal analogico e as conexoes.");
  } else {
    Serial.print("MQ-135 (raw): ");
    Serial.print(leitura.mq135.raw);
    Serial.print(" | MQ-135 (%): ");
    Serial.print(leitura.mq135.percentual, 1);
    Serial.print(" | Qualidade do ar: ");
    Serial.println(qualidadeArParaTexto(leitura.mq135.qualidade));
  }
}

LeituraEstacao lerEstacao() {
  LeituraEstacao leitura;
  leitura.dht = sensorDHT.ler();
  leitura.bmp = sensorBMP.ler();
  leitura.mq135 = sensorMQ.ler();
  leitura.momentoMillis = millis();
  leitura.timestampUtc = relogioNtp.agoraUtc();
  leitura.horarioSincronizado = relogioNtp.sincronizado();
  leitura.wifiConectado = gerenciadorWiFi.conectado();
  return leitura;
}

void loop() {
  static unsigned long ultimaLeituraMillis = 0;
  const unsigned long momentoAtualMillis = millis();
  gerenciadorWiFi.atualizar();
  relogioNtp.atualizar(gerenciadorWiFi.conectado());

  if (momentoAtualMillis - ultimaLeituraMillis < INTERVALO_LEITURA_MS) {
    return;
  }

  ultimaLeituraMillis = momentoAtualMillis;
  const LeituraEstacao leitura = lerEstacao();
  imprimirLeitura(leitura);

  static unsigned long ultimaPublicacaoMillis = 0;
  if (momentoAtualMillis - ultimaPublicacaoMillis >= INTERVALO_PUBLICACAO_MS &&
      leitura.wifiConectado && leitura.horarioSincronizado) {
    ultimaPublicacaoMillis = momentoAtualMillis;
    publicadorThingSpeak.publicar(leitura, WiFi.RSSI());
  }
}
