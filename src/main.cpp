#include <Arduino.h>
#include "Constantes.h"
#include "DHTSensor.h"
#include "BMPSensor.h"
#include "MQ135Sensor.h"

// Instâncias dos módulos de sensor
DHTSensor sensorDHT(PIN_DHT, DHT22);
BMPSensor sensorBMP(BMP_SENSOR_ID);
MQ135Sensor sensorMQ(PIN_MQ135);

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);

  Serial.println(MENSAGEM_INICIAL);
  Serial.println("Inicializando sensores...");

  sensorDHT.iniciar();
  if (!sensorBMP.iniciar()) {
    Serial.println("Erro: não foi possível inicializar o BMP180/BMP085.");
    while (true) {
      delay(2000);
    }
  }
  sensorMQ.iniciar();

  analogReadResolution(12);
}

void imprimirCabecalhoLeitura() {
  Serial.println();
  Serial.println("--- Leitura da estação meteorológica ---");
}

void loop() {
  auto leituraDHT = sensorDHT.ler();
  auto leituraBMP = sensorBMP.ler();
  auto leituraMQ = sensorMQ.ler();

  imprimirCabecalhoLeitura();

  if (!leituraDHT.ok) {
    Serial.println("Falha ao ler o DHT22. Verifique as conexões e alimentação.");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(leituraDHT.temperatura, 1);
    Serial.println(" °C");
    Serial.print("Umidade: ");
    Serial.print(leituraDHT.umidade, 1);
    Serial.println(" %");
  }

  if (!leituraBMP.ok) {
    Serial.println("Falha ao ler o BMP180/BMP085. Verifique as conexões I2C.");
  } else {
    Serial.print("Pressão: ");
    Serial.print(leituraBMP.pressao, 1);
    Serial.println(" hPa");
  }

  Serial.print("MQ-135 (raw): ");
  Serial.print(leituraMQ.raw);
  Serial.print(" | MQ-135 (%): ");
  Serial.print(leituraMQ.percentual, 1);
  Serial.print(" | Qualidade do ar: ");
  Serial.println(leituraMQ.qualidade);

  delay(INTERVALO_LEITURA_MS);
}
