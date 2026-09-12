# Referência Arduino + PlatformIO para Estação Meteorológica ESP32

## Contexto do projeto
Este projeto usa ESP32 com o framework Arduino dentro do PlatformIO. A combinação permite escrever código Arduino familiar enquanto usa o gerenciador de projetos e bibliotecas do PlatformIO.

## Links importantes
- Arduino Reference: https://www.arduino.cc/reference/en/
- PlatformIO Docs: https://docs.platformio.org/en/latest/
- ESP32 Arduino Core Docs: https://docs.espressif.com/projects/arduino-esp32/en/latest/

## Configuração do `platformio.ini`
Use uma seção de ambiente como esta:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps =
  adafruit/Adafruit BMP280 Library@^2.1.2
  adafruit/Adafruit Unified Sensor@^1.1.4
  bblanchon/ArduinoJson@^6.20.0
```

### Dicas de `platformio.ini`
- `platform`: especifica a plataforma do chip (`espressif32`).
- `board`: usa a placa `esp32dev` para desenvolvimento genérico.
- `framework`: deve ser `arduino` para código compatível com Arduino.
- `lib_deps`: declara bibliotecas necessárias para o projeto.

## Boas práticas com Arduino no ESP32
- Incluir `Arduino.h` no arquivo principal.
- Usar `setup()` para inicialização única e `loop()` para repetição.
- Inicializar `Serial.begin(115200)` para depuração.
- Preferir `Wire` para I2C e `SPI` para sensores SPI.

### Exemplo de estrutura básica
```cpp
#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Hello ESP32");
  delay(1000);
}
```

## Sensores recomendados
- DHT22: temperatura e umidade simples.
- BMP180/BMP085: pressão atmosférica via I2C.
- MQ-135: monitoramento de qualidade do ar / gás.
- BME280 / BMP280: alternativa para temperatura, pressão e umidade (I2C/SPI).

## Projeto atual: DHT22 + BMP180 + MQ-135
### Bibliotecas úteis
- `Adafruit BMP085 Unified`: suporte ao BMP180/BMP085.
- `Adafruit Unified Sensor`: camada comum para sensores Adafruit.
- `DHT sensor library`: leitura do DHT22.

### Exemplo de `platformio.ini`
```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps =
  adafruit/Adafruit BMP085 Unified@^1.0.4
  adafruit/Adafruit Unified Sensor@^1.1.4
  adafruit/DHT sensor library@^1.4.3
```

### Conexões sugeridas
- DHT22:
  - VCC -> 3.3V
  - GND -> GND
  - DATA -> GPIO4
  - Resistência de pull-up 10k entre DATA e 3.3V
- BMP180:
  - SDA -> GPIO21
  - SCL -> GPIO22
  - VCC -> 3.3V
  - GND -> GND
- MQ-135:
  - A0 -> GPIO34 (entrada analógica)
  - VCC -> 5V ou 3.3V dependendo da placa de sensor
  - GND -> GND

> Importante: o ESP32 aceita no máximo 3.3V na entrada analógica. Use um divisor de tensão ou módulo com saída compatível se o MQ-135 fornecer até 5V.

### Dicas de leitura
- O DHT22 deve ser lido a cada 2 segundos para obter resultados estáveis.
- O BMP180 usa I2C e funciona bem com o `Wire` padrão do ESP32.
- O MQ-135 produz uma saída analógica que pode ser interpretada como qualidade do ar; a calibração detalhada exige curvas do sensor e resistência de carga.

## Integração de bibliotecas
- Consulte o índice de bibliotecas do PlatformIO: https://platformio.org/lib
- Use `lib_deps` no `platformio.ini` para instalar automaticamente bibliotecas.
- Verifique os exemplos das bibliotecas para os sensores escolhidos.

## Uso de documentação durante o desenvolvimento
- Quando precisar de sintaxe ou funções Arduino, abra `https://www.arduino.cc/reference/en/`.
- Para ajustar `platformio.ini` ou instalar bibliotecas, use `https://docs.platformio.org/en/latest/`.
- Para detalhes do ESP32 Arduino core e pinos específicos, use `https://docs.espressif.com/projects/arduino-esp32/en/latest/`.

## Recomendação final
Este documento deve ser usado junto ao agente personalizado em `.vscode/arduino-esp32-weather-agent.instructions.md` para obter respostas alinhadas ao projeto e às melhores práticas de Arduino/PlatformIO.