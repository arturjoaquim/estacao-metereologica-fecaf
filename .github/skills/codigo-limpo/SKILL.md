---
name: codigo-limpo
description: "Aplicar boas práticas de código limpo, legível e simples em C++, Arduino, PlatformIO, ESP32 e outras linguagens. Use para criar, revisar ou refatorar código, melhorar nomes, reduzir complexidade, aplicar SOLID e escolher enums para categorias, estados e tipos."
argument-hint: "Descreva o código que deve ser criado, revisado ou refatorado."
---

# Código Limpo

## Quando usar

- Criar ou revisar classes, funções, módulos e APIs.
- Refatorar código difícil de ler, duplicado ou com responsabilidades misturadas.
- Escolher representações para categorias, estados, modos, tipos e códigos conhecidos.
- Avaliar complexidade, coesão, acoplamento, nomes e testabilidade.
- Trabalhar em C++, Arduino, PlatformIO, ESP32 ou código de aplicação.

## Princípios

- Prefira a implementação correta de menor complexidade que atenda ao requisito.
- Use nomes claros, objetivos e consistentes para variáveis, constantes, classes, métodos e funções.
- Mantenha funções pequenas, com uma responsabilidade e um nível de abstração coerente.
- Encapsule estado e preserve invariantes dentro da classe responsável por eles.
- Prefira composição e interfaces pequenas a hierarquias profundas e herança desnecessária.
- Siga SOLID quando isso reduzir acoplamento ou melhorar a evolução do código; não crie abstrações apenas para cumprir um acrônimo.
- Elimine duplicação significativa, mas não generalize antes de haver um padrão real.
- Evite números e strings mágicos: use constantes nomeadas com unidade e intenção explícitas.
- Prefira `enum class` para conjuntos fechados de categorias, estados, modos ou tipos. Não use enum para dados abertos, configuráveis ou que precisem ser estendidos sem recompilar.
- Preserve APIs e comportamento existentes quando a tarefa for uma refatoração, salvo quando houver um motivo explícito para alterá-los.

## Procedimento

1. Identifique o comportamento esperado, as entradas, as saídas e as invariantes.
2. Localize a responsabilidade que decide o comportamento antes de editar código de encaminhamento ou configuração.
3. Dê nomes que expressem intenção, unidade e ciclo de vida; evite abreviações ambíguas e nomes genéricos como `dados`, `coisa` ou `temp` quando não forem precisos.
4. Catalogue valores fechados com `enum class` e converta para texto ou protocolo em um único ponto bem definido.
5. Separe leitura de hardware, regra de negócio, formatação e transporte em módulos coesos.
6. Reduza condicionais aninhadas com retornos antecipados, funções auxiliares bem nomeadas ou uma modelagem adequada do estado.
7. Verifique se cada classe tem uma responsabilidade principal, dependências explícitas e uma interface mínima.
8. Adicione ou ajuste testes para casos normais, limites, falhas e estados inválidos.
9. Compile, execute os testes e revise o diff para confirmar que a refatoração não alterou o comportamento sem intenção.

## Checklist de revisão

- Os nomes explicam o propósito sem exigir comentários?
- Há enumerações fechadas representadas como texto solto ou inteiros sem significado?
- Há números, pinos, limiares ou mensagens mágicos?
- Cada função tem uma responsabilidade verificável?
- Classes dependem de abstrações estáveis e não de detalhes desnecessários?
- O caminho de erro é explícito e testável?
- A solução é mais simples depois da mudança, ou apenas mais abstrata?
- O build e os testes relevantes foram executados?

## Aplicação ao ESP32

- Mantenha pinos, endereços I2C, intervalos e limiares em constantes nomeadas.
- Separe drivers de sensores da apresentação serial e da lógica de decisão.
- Dê unidade aos valores físicos nos nomes ou tipos, por exemplo, `temperaturaCelsius` e `pressaoHpa`.
- Evite alocações dinâmicas desnecessárias em caminhos executados repetidamente.
- Não esconda falhas de inicialização ou leituras inválidas atrás de valores padrão indistinguíveis de medições reais.
