# Instruções do workspace

Este projeto é uma estação meteorológica baseada em ESP32.

## Objetivo
- Monitorar condições ambientais usando sensores conectados à placa ESP32.
- Coletar leituras de temperatura, umidade, pressão atmosférica e qualidade do ar.

## Componentes principais
- ESP32 como controlador principal.
- Sensor DHT22 para leitura de temperatura e umidade.
- Sensor BMP180/BMP085 para leitura de pressão atmosférica.
- Sensor MQ-135 para estimar a qualidade do ar.

## Comportamento esperado
- O firmware deve inicializar os sensores e publicar as leituras via Serial.
- As medições devem ser exibidas de forma clara e legível para depuração e monitoramento.
- Alterações no código devem preservar o foco deste projeto como estação meteorológica.
- O projeto deve ser programado e documentado integralmente em português do Brasil.
 - Código deve ser escrito em português (identificadores, comentários e mensagens).
 - Evitar "magic numbers" e "magic strings": use constantes nomeadas para pinos, IDs, limiares e mensagens.
 - Mantenha o código limpo e modular: desacoplar lógica de sensores em módulos separados.

## Observações
- O pino do DHT22 está configurado para o GPIO 4.
- O MQ-135 é lido na entrada analógica GPIO 34.
- O BMP180/BMP085 usa comunicação I2C.
