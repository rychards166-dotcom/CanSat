#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <math.h>

Adafruit_ADS1115 ads;

// Constantes elétricas e do NTC (comuns para ambos os sensores)
const float VCC = 3.3;          // Alimentação de 3.3V
const float R_FIXO = 10000.0;   // Resistor de pull-up de 10k Ohms
const float R_NTC_25 = 10000.0; // Resistência nominal do NTC a 25°C
const float BETA = 3950.0;      // Coeficiente Beta do NTC
const float TEMP_REF = 298.15;  // 25°C em Kelvin

// Função auxiliar para calcular a temperatura a partir do valor bruto do ADC
float calcularTemperatura(int16_t adc_valor) {
  // Multiplicador de GAIN_ONE (0.125 mV por bit) para converter em Volts
  float v_ntc = adc_valor * 0.125 / 1000.0; 

  // Validação física do sinal (evita erros nas extremidades ou circuito aberto)
  if (v_ntc < 0.03 || v_ntc > (VCC - 0.03)) {
    return -999.0; // Retorna um código de erro caso o sensor esteja desconectado/em curto
  }

  // Equações matemáticas para descobrir a temperatura
  float r_ntc = R_FIXO * (v_ntc / (VCC - v_ntc));
  float temperaturaK = 1.0 / ((1.0 / TEMP_REF) + (log(r_ntc / R_NTC_25) / BETA));
  
  return temperaturaK - 273.15; // Retorna em Graus Celsius
}

void setup(void) {
  Serial.begin(9600);
  Wire.begin(6,7);
  
  if (!ads.begin()) {
    Serial.println("ADS1115 nao encontrado! Verifique as conexoes I2C.");
    while (1);
  }
  
  // Mantém a escala ideal de +/- 4.096V para máxima precisão em 3.3V
  ads.setGain(GAIN_ONE); 
}

void loop(void) {
  // 1. Efetua a leitura física dos canais A0 e A1
  int16_t raw_bat1 = ads.readADC_SingleEnded(0);
  int16_t raw_bat2 = ads.readADC_SingleEnded(1);

  // 2. Processa os cálculos de temperatura através da função
  float temp_bat1 = calcularTemperatura(raw_bat1);
  float temp_bat2 = calcularTemperatura(raw_bat2);

  // 3. Exibe os resultados da Bateria 1
  Serial.print("BATERIA 1: ");
  if (temp_bat1 == -999.0) {
    Serial.print("Erro/Desconectada");
  } else {
    Serial.print(temp_bat1, 1);
    Serial.print(" C");
  }

  Serial.print("  |  ");

  // 4. Exibe os resultados da Bateria 2
  Serial.print("BATERIA 2: ");
  if (temp_bat2 == -999.0) {
    Serial.println("Erro/Desconectada");
  } else {
    Serial.print(temp_bat2, 1);
    Serial.println(" C");
  }

  delay(1500); // Aguarda 1,5 segundos antes da próxima leitura
}
