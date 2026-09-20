#include <Wire.h>
#include <AHT20.h>
#include <Adafruit_BMP280.h>

#define E2PROM 0x50
#define LED_AMARELO 1
#define LED_VERDE 2

AHT20 aht;
Adafruit_BMP280 bmp; // Cria o elemento "BMP280"

void EscreverE2PROM (uint8_t Endereco, byte dado, byte BLOCO){

  byte enderecoI2C = E2PROM + BLOCO;
  Wire.beginTransmission(enderecoI2C); // Inicia a comunicação com a E2PROM
  Wire.write(Endereco);
  Wire.write(dado);
  Wire.endTransmission();
  delay(5);


}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(155200);
  Wire.begin (6,7);
  delay (100);

  if (!aht.begin()) 
  {Serial.println (" AHT20 não encontrado. Ajuste os cabos ou altere o endereço");
  while (1) delay (1000);}

  Serial.printf("=== Gravação iniciada ===\n\n");
  delay(1000);
  pinMode (LED_AMARELO, OUTPUT);
  pinMode (LED_VERDE, OUTPUT);

  int i;
  

  for (i=0; i<256; i++)
   {  byte AHT20 = aht.getHumidity();
      byte BMPTEMP = bmp.readTemperature();
      EscreverE2PROM(i, AHT20, 0);
      delay(10);
      EscreverE2PROM(i, BMPTEMP, 1);
      delay(100);
      digitalWrite (LED_AMARELO, HIGH);
      Serial.printf("AHT20 == Endereço %d, valor escrito %d\n", i, AHT20); 
      Serial.printf("AHT20 == Endereço %d, valor escrito %d\n", i, BMPTEMP); 
      delay(100);
   }

  Serial.printf("Gravação finalizada");
  digitalWrite (LED_AMARELO, LOW);
  digitalWrite (LED_VERDE, HIGH);
  delay(3000);
  digitalWrite (LED_VERDE, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}


