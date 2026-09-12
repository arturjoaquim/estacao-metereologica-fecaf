#include <Arduino.h>
#include <unity.h>
#include "DHTSensor.h"
#include "BMPSensor.h"
#include "MQ135Sensor.h"
#include "Constantes.h"

// Incluir implementações diretamente para garantir linkage nos testes
#include "../../src/DHTSensor.cpp"
#include "../../src/BMPSensor.cpp"
#include "../../src/MQ135Sensor.cpp"

// Instâncias para testes
DHTSensor sensorDHTTest(PIN_DHT, DHT22);
BMPSensor sensorBMPTest(BMP_SENSOR_ID);
MQ135Sensor sensorMQTest(PIN_MQ135);

void setUp() {
  sensorDHTTest.iniciar();
  sensorBMPTest.iniciar();
  sensorMQTest.iniciar();
  delay(10);
}

void tearDown() {}

void test_leituras_nao_travam() {
  auto lDht = sensorDHTTest.ler();
  auto lBmp = sensorBMPTest.ler();
  auto lMq = sensorMQTest.ler();

  // Se chegamos até aqui, as leituras não travaram. Asserção trivial.
  TEST_ASSERT_TRUE(true);
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_leituras_nao_travam);
  UNITY_END();
}

void loop() {
  // Nada aqui: testes executam em setup
}
