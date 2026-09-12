Você está correto em sua observação. O MQ-135 é um sensor de "largo espectro", o que traz algumas limitações importantes no uso prático.

Aqui está a explicação detalhada sobre a detecção de gás de cozinha e a capacidade de distinção:

1. Ele detecta gás de cozinha (GLP)?
Sim, mas não é o ideal. 
O gás de cozinha (GLP - Gás Liquefeito de Petróleo, composto principalmente por Propano e Butano) pode ser detectado pelo MQ-135, mas ele tem uma sensibilidade muito baixa para esses gases.

Para Gás de Cozinha/Metano/Propano, o sensor recomendado é o MQ-2 ou o MQ-5, que são otimizados especificamente para gases combustíveis.
O MQ-135 é otimizado para poluentes do ar (como Amônia e Benzeno).
2. Ele consegue distinguir qual gás é qual?
Não. Esta é a maior limitação dos sensores da série MQ. 
Eles são sensores quimiorresistivos analógicos. Isso significa que:

Saída Única: O sensor fornece apenas um valor de voltagem (ou um valor digital 0/1).
Reação Cruzada: Se houver fumaça e amônia no ar ao mesmo tempo, o sensor apenas indicará que a condutividade aumentou (a resistência caiu), mas ele não sabe dizer se o aumento foi causado pela fumaça, pela amônia ou por ambos.
Leitura "Cega": Ele reporta a "soma" da contaminação do ar. Você saberá que a qualidade do ar piorou, mas não saberá exatamente qual substância causou isso.
Comparativo de Sensores MQ
Se o seu objetivo é detectar gases específicos, veja qual sensor é mais adequado:

Sensor	Foco Principal (Maior Sensibilidade)	Pode detectar Gás de Cozinha?
MQ-135	Qualidade do Ar (Amônia, Benzeno, Álcool, 
C
O
2
CO 
2
​
 )	Sim, mas com baixa precisão.
MQ-2	Fumaça e Gases Combustíveis (GLP, Propano, Hidrogênio)	Sim (Excelente para segurança doméstica).
MQ-4	Gás Natural e Metano (
C
H
4
CH 
4
​
 )	Sim.
MQ-7	Monóxido de Carbono (
C
O
CO)	Sim, mas foca no CO (tóxico).
Conclusão
Se você quer construir um monitor de poluição ambiental, o MQ-135 é o correto. 
Se você quer construir um alarme de vazamento de gás de cozinha, o MQ-2 é muito mais seguro e eficiente, pois ele ignorará pequenas variações de outros poluentes que poderiam causar alarmes falsos no MQ-135.