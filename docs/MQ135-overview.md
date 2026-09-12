O MQ-135 é um sensor de qualidade do ar amplamente utilizado em projetos de eletrônica (como Arduino, ESP32 e Raspberry Pi) para detectar diversos gases nocivos e poluentes na atmosfera.

Ele pertence à família de sensores de óxido metálico semicondutor (MOS), conhecidos por sua durabilidade e baixo custo.

1. Gases Detectados
O MQ-135 é considerado um sensor de "propósito geral" para qualidade do ar, sendo sensível a:

Amônia (
N
H
3
NH 
3
​
 )
Óxidos de Nitrogênio (
N
O
x
NO 
x
​
 )
Álcool (Etanol)
Benzeno
Fumaça
Dióxido de Carbono (
C
O
2
CO 
2
​
 )
2. Especificações Técnicas
Abaixo estão as características elétricas e operacionais principais do módulo MQ-135:

Parâmetro	Descrição / Valor
Tensão de Operação	5V DC
Consumo do Aquecedor	Menor que 800mW
Resistência de Carga	Ajustável (via potenciômetro no módulo)
Tempo de Pré-aquecimento	24 a 48 horas (uso inicial) / 2 min (uso diário)
Saída Digital (DO)	Nível TTL (0 e 1) ajustável via potenciômetro
Saída Analógica (AO)	0V a 5V (proporcional à concentração de gás)
3. Princípio de Funcionamento
O sensor utiliza uma camada de Dióxido de Estanho (
S
n
O
2
SnO 
2
​
 ). 

Em ar limpo: O 
S
n
O
2
SnO 
2
​
  tem baixa condutividade (alta resistência).
Na presença de gases: Quando os gases poluentes entram em contato com o sensor aquecido, a condutividade aumenta.
Conversão: O circuito do módulo converte essa variação de condutividade em uma variação de voltagem que pode ser lida por um microcontrolador.
4. Pinagem do Módulo (Pinout)
A maioria dos módulos MQ-135 vendidos comercialmente possui 4 pinos:

Pino	Função	Conexão Sugerida
VCC	Alimentação	5V do Microcontrolador
GND	Terra	GND do Microcontrolador
DO	Digital Out	Pino Digital (detecta se passou do limite)
AO	Analog Out	Pino Analógico (leitura precisa da concentração)
5. Exemplo de Código para Arduino
Este código básico lê o valor analógico do sensor e exibe no Monitor Serial.

// Definição do pino analógico
const int pinoSensor = A0;
int valorLido = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Aquecendo o sensor MQ-135...");
  // O sensor precisa de um tempo para estabilizar o aquecedor interno
  delay(20000); 
}

void loop() {
  valorLido = analogRead(pinoSensor); // Lê o valor de 0 a 1023
  
  Serial.print("Qualidade do Ar (Leitura Analógica): ");
  Serial.println(valorLido);

  if (valorLido > 400) {
    Serial.println("Alerta: Má qualidade do ar detectada!");
  }

  delay(1000); // Aguarda 1 segundo para a próxima leitura
}
Observações Importantes
Calibração: Para obter valores em PPM (partes por milhão), é necessário realizar uma calibração matemática complexa baseada na curva de sensibilidade do datasheet e na resistência de carga (
R
L
R 
L
​
 ).
Aquecimento: O sensor fica quente ao toque durante o funcionamento. Isso é normal, pois ele possui uma resistência interna de aquecimento necessária para a reação química.
Burn-in: Novos sensores devem ser deixados ligados por pelo menos 24 horas antes do primeiro uso para garantir leituras estáveis.

