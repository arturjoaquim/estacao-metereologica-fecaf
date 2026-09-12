O DHT22 (também conhecido como AM2302) é um sensor digital de baixo custo, muito popular em projetos de eletrônica e IoT para medir a umidade relativa do ar e a temperatura.

Abaixo, apresento as especificações técnicas e detalhes de funcionamento estruturados:

1. Especificações Técnicas
Comparado ao seu "irmão menor" (DHT11), o DHT22 possui maior precisão e uma faixa de leitura mais ampla.

Característica	Especificação
Tensão de Operação	3.3V a 5V DC
Corrente Máxima	1.5mA (durante a conversão)
Faixa de Temperatura	-40°C a 80°C (Precisão de ±0.5°C)
Faixa de Umidade	0% a 100% RH (Precisão de ±2-5%)
Intervalo de Leitura	2 segundos (Frequência de 0.5 Hz)
Tipo de Sinal	Digital (Single-bus)
2. Componentes Internos
O DHT22 não é apenas um sensor, mas um sistema composto por:

Sensor de Umidade Capacitivo: Utiliza um substrato que retém umidade entre dois eletrodos; a mudança na umidade altera a capacitância.
Termistor NTC: Um resistor térmico cuja resistência diminui conforme a temperatura aumenta.
Microcontrolador de 8 bits: Responsável por converter os sinais analógicos em um pacote de dados digitais.
3. Pinagem (Pinout)
Embora possua 4 pinos físicos, na maioria das aplicações apenas 3 são utilizados.

Pino	Nome	Descrição
1	VCC	Alimentação (3.3V - 5V)
2	DATA	Saída de dados digitais
3	NC	Não conectado
4	GND	Terra (0V)
4. Conexão e Circuito
Para garantir o funcionamento estável, deve-se observar:

Resistor de Pull-up: É necessário conectar um resistor (geralmente de 4.7kΩ a 10kΩ) entre o pino VCC e o pino DATA. Isso mantém a linha de dados em nível alto quando o sensor está em espera.
Distância do Cabo: O DHT22 pode enviar sinais a distâncias de até 20 metros, mas quanto maior o cabo, menor deve ser a resistência do pull-up.
5. Exemplo de Código (Arduino)
Para utilizar o sensor, a biblioteca mais comum é a da Adafruit.

#include "DHT.h"

#define DHTPIN 2     // Pino onde o DATA está conectado
#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000); // Aguarda 2 segundos entre as leituras

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao ler o sensor!");
    return;
  }

  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.print("%  Temperatura: ");
  Serial.print(t);
  Serial.println("°C");
}