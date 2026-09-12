// Constantes do projeto (usar nomes descritivos, sem magic numbers)
#pragma once
#include <Arduino.h>

constexpr int PIN_DHT = 4;
constexpr int PIN_MQ135 = 34;
constexpr int BMP_SENSOR_ID = 10085;

constexpr int SERIAL_BAUD = 115200;
constexpr unsigned long INTERVALO_LEITURA_MS = 2000;

// Limiares MQ-135 (percentual)
constexpr float MQ_LIMIAR_BOA = 35.0f;
constexpr float MQ_LIMIAR_MODERADA = 60.0f;
constexpr float MQ_LIMIAR_RUIM = 80.0f;

// Mensagens padrão
static const char MENSAGEM_INICIAL[] = "Estacao meteorologica ESP32";
