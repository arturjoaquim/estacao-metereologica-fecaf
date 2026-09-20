#pragma once

#include <time.h>

#include "BMPSensor.h"
#include "DHTSensor.h"
#include "MQ135Sensor.h"

struct LeituraEstacao {
  LeituraDHT dht;
  LeituraBMP bmp;
  LeituraMQ mq135;
  unsigned long momentoMillis;
  time_t timestampUtc;
  bool horarioSincronizado;
  bool wifiConectado;
};
