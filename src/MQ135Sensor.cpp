#include "MQ135Sensor.h"
#include "Constantes.h"

namespace {

struct EstatisticasADC {
  int media;
  int menor;
  int maior;
};

LeituraMQ criarLeituraInicial() {
  return {0, 0.0f, QualidadeAr::Indisponivel};
}

bool sensorAindaAquecendo(bool iniciado, unsigned long momentoInicio) {
  return !iniciado || millis() - momentoInicio < TEMPO_AQUECIMENTO_MQ135_MS;
}

EstatisticasADC coletarAmostrasADC(int pino) {
  int menorLeitura = ADC_VALOR_MAXIMO;
  int maiorLeitura = ADC_VALOR_MINIMO;
  long somaLeituras = 0;

  for (int indice = 0; indice < ADC_QUANTIDADE_AMOSTRAS; indice++) {
    const int leituraAtual = analogRead(pino);
    somaLeituras += leituraAtual;
    menorLeitura = min(menorLeitura, leituraAtual);
    maiorLeitura = max(maiorLeitura, leituraAtual);
  }

  return {somaLeituras / ADC_QUANTIDADE_AMOSTRAS, menorLeitura,
          maiorLeitura};
}

bool leituraADCValida(const EstatisticasADC& estatisticas) {
  return estatisticas.media > ADC_VALOR_MINIMO &&
         estatisticas.media < ADC_VALOR_MAXIMO &&
         estatisticas.maior - estatisticas.menor <= ADC_VARIACAO_MAXIMA_VALIDO;
}

float converterParaPercentual(int leituraADC) {
  return (leituraADC / static_cast<float>(ADC_VALOR_MAXIMO)) * 100.0f;
}

QualidadeAr classificarQualidadeAr(float percentual) {
  if (percentual < MQ_LIMIAR_BOA) {
    return QualidadeAr::Boa;
  }
  if (percentual < MQ_LIMIAR_MODERADA) {
    return QualidadeAr::Moderada;
  }
  if (percentual < MQ_LIMIAR_RUIM) {
    return QualidadeAr::Ruim;
  }
  return QualidadeAr::Pessima;
}

}  // namespace

MQ135Sensor::MQ135Sensor(int pino)
    : _pino(pino), _momentoInicio(0), _iniciado(false) {}

const char* qualidadeArParaTexto(QualidadeAr qualidade) {
  switch (qualidade) {
    case QualidadeAr::Aquecendo:
      return "MQ-135 aquecendo; leitura ainda indisponivel.";
    case QualidadeAr::Boa:
      return "Boa";
    case QualidadeAr::Moderada:
      return "Moderada";
    case QualidadeAr::Ruim:
      return "Ruim";
    case QualidadeAr::Pessima:
      return "Pessima";
    case QualidadeAr::Indisponivel:
    default:
      return "Sensor indisponivel.";
  }
}

void MQ135Sensor::iniciar() {
  pinMode(_pino, INPUT);
  _momentoInicio = millis();
  _iniciado = true;
}

LeituraMQ MQ135Sensor::ler() {
  LeituraMQ leitura = criarLeituraInicial();

  if (sensorAindaAquecendo(_iniciado, _momentoInicio)) {
    leitura.qualidade = QualidadeAr::Aquecendo;
    return leitura;
  }

  const EstatisticasADC estatisticas = coletarAmostrasADC(_pino);
  leitura.raw = estatisticas.media;
  if (!leituraADCValida(estatisticas)) {
    return leitura;
  }

  leitura.percentual = converterParaPercentual(leitura.raw);
  leitura.qualidade = classificarQualidadeAr(leitura.percentual);

  return leitura;
}
