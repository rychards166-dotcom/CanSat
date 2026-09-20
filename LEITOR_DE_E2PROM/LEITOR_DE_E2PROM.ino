#include <Wire.h>

#define BLOCO 0
#define E2PROM 0x50
#define LED_AMARELO 1
#define LED_VERDE 2

byte lerEPROM( uint8_t endereco ) { // uint8_t = um número de 8bits/1byte 00000000

    byte enderecoI2C = E2PROM + BLOCO;
    Wire.beginTransmission(enderecoI2C); // Inicia a comunicação com a E2PROM
    Wire.write(endereco);
    Wire.endTransmission();
    Wire.requestFrom(enderecoI2C, 1);

    if (Wire.available()){
      return Wire.read();
    }

    return 0;

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode (LED_AMARELO, OUTPUT);
  pinMode (LED_VERDE, OUTPUT);
  
  delay(100);
 

  Wire.begin(6,7);

  int i;
  Serial.println("=== Leitura iniciada ===\n\n");
  delay(2000);
  Serial.printf("=== Lendo o bloco %d ===", BLOCO);
  delay(2000);
  
  for (i=0; i<256; i++)
  {byte valor = lerEPROM (i);
   Serial.printf("Endereço %d, valor lido %d\n", i, valor); 
   digitalWrite (LED_AMARELO, HIGH);
   delay(100);
  }

  Serial.printf("Leitura finalizada");
  digitalWrite (LED_AMARELO, LOW);
  digitalWrite (LED_VERDE, HIGH);
  delay(3000);
  digitalWrite (LED_VERDE, LOW);
}



void loop() {
  // put your main code here, to run repeatedly:

}
