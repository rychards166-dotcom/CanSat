#include <Wire.h>

#define E2PROM 0x50

byte lerEPROM( uint8_t endereco, byte bloco ) { // uint8_t = um número de 8bits/1byte 00000000
   
    byte enderecoI2C = E2PROM + bloco;
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
  Wire.begin(6,7);

  int i;
  int sbloco=0;
  delay (1000);
  Serial.printf("=== Leitura iniciada ===\n\n");
  delay (4000);

  while (sbloco < 8)
 {
   Serial.printf("=== Bloco %d ===\n", sbloco);
  
   for (i=0; i<256; i++)
   { byte valor = lerEPROM (i,sbloco);
     Serial.printf("Endereço %d, valor lido %d\n", i, valor); 
     delay(50);
   }
     Serial.printf("\n");
   sbloco=sbloco+1;
 }

 Serial.println("Leitura Feita com sucesso!!");
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
