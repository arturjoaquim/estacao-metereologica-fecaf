---
name: desenvolvimento-seguro
description: "Aplicar práticas de desenvolvimento seguro em C++, Arduino, PlatformIO, ESP32 e aplicações: modelagem de ameaças, validação de entradas, gestão de segredos, menor privilégio, dependências, memória, comunicação e tratamento seguro de erros. Use para criar, revisar, depurar ou refatorar código com foco em segurança."
argument-hint: "Descreva o código, componente ou risco de segurança que deve ser analisado."
---

# Desenvolvimento Seguro

## Quando usar

- Criar ou revisar código que recebe dados de sensores, usuários, rede, serial ou arquivos.
- Integrar bibliotecas, dispositivos, APIs, Wi-Fi, MQTT, HTTP, Bluetooth ou armazenamento.
- Investigar validação insuficiente, vazamento de segredo, corrupção de memória ou falhas de autorização.
- Avaliar firmware ESP32, projetos Arduino/PlatformIO e aplicações conectadas.
- Preparar testes de segurança, revisão de dependências ou análise de uma mudança.

## Princípios

- Modele ameaças antes de escolher controles: ativo, entrada, impacto, confiança e atacante plausível.
- Valide todas as entradas na fronteira de confiança; não confie em valores vindos de sensores, serial, rede ou memória persistente.
- Prefira listas permitidas, limites explícitos, tipos fortes e estados válidos a filtros frágeis ou listas de bloqueio.
- Use o menor privilégio, a menor superfície exposta e o menor tempo de retenção necessários.
- Nunca inclua senhas, tokens, chaves privadas ou certificados sensíveis no código-fonte, logs ou repositório.
- Não registre dados sensíveis; quando necessário, mascare identificadores e segredos.
- Trate falhas de forma segura, sem expor detalhes internos nem continuar com estado potencialmente inválido.
- Mantenha dependências atualizadas, fixadas de forma reproduzível e avaliadas quanto à origem e necessidade.
- Não implemente criptografia própria. Use primitivas e bibliotecas reconhecidas, com configuração documentada.
- Segurança não substitui correção: medições inválidas devem ser marcadas como inválidas, nunca convertidas silenciosamente em valores confiáveis.

## Procedimento

1. Delimite o componente, os ativos protegidos, as entradas, as saídas e as fronteiras de confiança.
2. Liste abuso plausível e impacto: leitura indevida, alteração de configuração, comando não autorizado, indisponibilidade, vazamento ou dano físico.
3. Identifique validações, autenticação, autorização, criptografia, armazenamento, logs e dependências já existentes.
4. Valide formato, tamanho, faixa, unidade, codificação, frequência e sequência das entradas antes de processá-las.
5. Separe dados não confiáveis de comandos, consultas, caminhos, mensagens e configurações executáveis.
6. Garanta que cada operação sensível exige autorização explícita e que credenciais não ficam embutidas no firmware.
7. Trate timeout, desconexão, leitura inválida, estouro, falta de memória e falha de inicialização com estados seguros.
8. Adicione testes de limites, entradas malformadas, repetição, concorrência, perda de comunicação e recuperação após falha.
9. Execute build, testes, análise estática e auditoria de dependências; registre riscos residuais e premissas.

## Checklist de revisão

- Quais são as fronteiras de confiança e os ativos protegidos?
- Toda entrada tem validação de tamanho, faixa, tipo, unidade e estado?
- Existe algum segredo no código, no `platformio.ini`, em logs ou no histórico do Git?
- Operações sensíveis têm autenticação e autorização, ou apenas ocultação no cliente?
- A falha deixa o sistema em estado seguro e observável?
- Buffers têm limites e operações de memória são verificadas?
- Bibliotecas e versões são necessárias, confiáveis e reproduzíveis?
- O comportamento pode ser abusado por repetição, valores extremos ou perda de conectividade?
- Há testes que demonstram os controles e documentam riscos que permanecem?

## Aplicação ao ESP32

- Restrinja comandos recebidos pela Serial, Wi-Fi, MQTT, HTTP ou Bluetooth a formatos e operações permitidos.
- Proteja credenciais de rede e chaves usando o mecanismo de configuração segura apropriado ao produto; não as grave em texto puro.
- Considere secure boot, flash encryption, atualização autenticada e desativação de interfaces de depuração no ciclo de produção.
- Separe leitura de sensor de comandos de atuadores; uma leitura anômala não deve acionar uma operação perigosa.
- Valide ADC, I2C e dados dos sensores por faixa, timeout e consistência; sinalize falhas em vez de publicar medições falsas.
- Evite logs seriais que revelem credenciais, dados pessoais, topologia de rede ou material criptográfico.
- Use watchdog e limites de recursos para reduzir impacto de travamentos e consumo excessivo, sem mascarar a causa da falha.
