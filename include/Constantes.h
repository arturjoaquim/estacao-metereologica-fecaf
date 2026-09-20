// Constantes do projeto (usar nomes descritivos, sem magic numbers)
#pragma once
#include <Arduino.h>

constexpr int PIN_DHT = 5;
constexpr int PIN_MQ135 = 34;
constexpr int PIN_I2C_SDA = 32;
constexpr int PIN_I2C_SCL = 33;
constexpr int BMP_SENSOR_ID = 10085;
constexpr int I2C_ENDERECO_INICIAL_SCAN = 0x03;
constexpr int I2C_ENDERECO_FINAL_SCAN = 0x77;

constexpr int SERIAL_BAUD = 115200;
constexpr unsigned long INTERVALO_LEITURA_MS = 2000;
constexpr unsigned long INTERVALO_PUBLICACAO_MS = 20000;
constexpr unsigned long TEMPO_AQUECIMENTO_MQ135_MS = 20000;
constexpr unsigned long INTERVALO_RELOGIO_NTP_MS = 1000;
constexpr int ADC_VALOR_MINIMO = 0;
constexpr int ADC_VALOR_MAXIMO = 4095;
constexpr int ADC_QUANTIDADE_AMOSTRAS = 8;
constexpr int ADC_VARIACAO_MAXIMA_VALIDO = 300;

// Limiares MQ-135 (percentual)
constexpr float MQ_LIMIAR_BOA = 35.0f;
constexpr float MQ_LIMIAR_MODERADA = 60.0f;
constexpr float MQ_LIMIAR_RUIM = 80.0f;

// Mensagens padrão
static const char MENSAGEM_INICIAL[] = "Estacao meteorologica ESP32";
static const char MENSAGEM_THINGSPEAK_NAO_CONFIGURADO[] =
	"ThingSpeak sem configuracao local; publicacao desativada.";
