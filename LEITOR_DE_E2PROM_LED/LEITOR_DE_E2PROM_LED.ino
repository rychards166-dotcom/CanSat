#include <Wire.h>

#define E2PROM 0x50
#define LED_AMARELO 1
#define LED_VERDE 2

byte lerEPROM( uint8_t endereco ) { // uint8_t = um número de 8bits/1byte 00000000
  
    Wire.beginTransmission(E2PROM); // Inicia a comunicação com a E2PROM
    Wire.write(endereco);
    Wire.endTransmission();
    Wire.requestFrom(E2PROM, 1);

    if (Wire.available()){
      return Wire.read();
    }

    return 0;

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("=== Leitura iniciada ===");
  pinMode (LED_AMARELO, OUTPUT);
  pinMode (LED_VERDE, OUTPUT);

  Wire.begin(6,7);

  int i;

  for (i=-1; i<256; i++)
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
