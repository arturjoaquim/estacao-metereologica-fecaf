Para conectar o pino analógico (AO) do MQ-135 a um ESP32, a escolha da GPIO é crítica devido à arquitetura interna do chip.

A melhor escolha são as portas do barramento ADC1.

1. Por que usar o ADC1 e não o ADC2?
O ESP32 possui dois Conversores Analógico-Digitais (ADC). O ADC2 é compartilhado com o Wi-Fi. Se o seu projeto utiliza Wi-Fi (o que é comum no ESP32), o uso de qualquer pino do ADC2 causará erros ou leituras nulas quando o Wi-Fi estiver ativo.

2. Pinos Recomendados (ADC1)
Estes são os pinos mais seguros e comumente usados para leitura analógica no ESP32:

GPIO	Canal ADC	Recomendação
GPIO 34	ADC1_CH6	Excelente (Apenas entrada, sem resistores internos de pull-up/down).
GPIO 35	ADC1_CH7	Excelente (Apenas entrada).
GPIO 32	ADC1_CH4	Muito boa.
GPIO 33	ADC1_CH5	Muito boa.
GPIO 36 (VP)	ADC1_CH0	Boa, mas pode captar ruído se não blindada.
GPIO 39 (VN)	ADC1_CH3	Boa, mas pode captar ruído.
3. Atenção Importante: Tensão de 5V vs 3.3V
Este é o ponto onde a maioria dos iniciantes queima o ESP32:

O Sensor MQ-135 precisa de 5V no pino VCC para aquecer corretamente.
O ESP32 suporta apenas 3.3V em suas portas GPIO.
Embora a saída analógica do MQ-135 possa chegar perto de 5V se houver muito gás, em condições normais de ar limpo, ela costuma ficar baixa.
Recomendação de segurança: Use um Divisor de Tensão (dois resistores) entre o pino AO do sensor e a GPIO do ESP32 para garantir que o sinal nunca ultrapasse 3.3V.

4. Configuração no Código (Arduino IDE)
Como o ADC do ESP32 tem resolução de 12 bits (0 a 4095), o código muda levemente em relação ao Arduino Uno (10 bits):

const int pinoSensor = 34; // GPIO 34 (ADC1)

void setup() {
  Serial.begin(115200);
  pinMode(pinoSensor, INPUT);
  
  // Opcional: Configura a atenuação para ler até ~3.3V
  // ADC_11db permite ler a faixa completa de tensão
  analogSetAttenuation(ADC_11db); 
}

void loop() {
  int valor = analogRead(pinoSensor); 
  Serial.printf("Valor ADC: %d\n", valor);
  delay(500);
}
Resumo da Conexão
VCC do Sensor -> Pino 5V ou Vin do ESP32 (conectado ao USB).
GND do Sensor -> GND do ESP32.
AO do Sensor -> GPIO 34 (preferencialmente com divisor de tensão).

Para conectar a saída analógica do módulo MQ-135 (alimentado em 5V) a um pino ADC do ESP32 (tensão máxima de entrada de 3.3V), o divisor de tensão recomendado é formado por dois resistores: $R_1 = 1\text{ k}\Omega$ e $R_2 = 2\text{ k}\Omega$ (ambos de $1/4\text{ W}$).Esquema de LigaçãoPlaintext                     R1 (1 kΩ)
  MQ-135 (A0) ------/\/\/\/\-------+--------> GPIO do ESP32 (ex: GPIO 34)
                                   |
                                   \
                                   /  R2 (2 kΩ)
                                   \
                                   |
                                  GND
Conecte o pino analógico A0 do MQ-135 em uma das pontas do resistor $R_1$ ($1\text{ k}\Omega$).Conecte a outra ponta de $R_1$ à porta analógica do ESP32 (ex: GPIO 34).Conecte o resistor $R_2$ ($2\text{ k}\Omega$) entre essa mesma porta do ESP32 e o GND (compartilhado com o MQ-135 e o ESP32).Cálculo da Tensão de Saída ($V_{out}$)$$V_{out} = V_{in} \cdot \left( \frac{R_2}{R_1 + R_2} \right)$$Quando o sinal do sensor atinge o valor máximo de $5\text{ V}$:$$V_{out} = 5\text{V} \cdot \left( \frac{2000}{1000 + 2000} \right) = 5\text{V} \cdot \frac{2}{3} \approx 3{,}33\text{ V}$$Essa tensão de saída de $3{,}33\text{ V}$ fica alinhada ao limite de operação do conversor analógico-digital (ADC) do ESP32, garantindo proteção contra sobretensão no pino.