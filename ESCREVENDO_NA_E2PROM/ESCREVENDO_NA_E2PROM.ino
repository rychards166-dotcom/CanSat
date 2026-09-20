#include <Wire.h>


#define E2PROM 0x50
#define LED_AMARELO 1
#define LED_VERDE 2



void EscreverE2PROM (uint8_t Endereco, byte dado){

  Wire.beginTransmission(E2PROM);
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

  
  Serial.printf("=== Gravação iniciada ===\n\n");
  delay(1000);
  pinMode (LED_AMARELO, OUTPUT);
  pinMode (LED_VERDE, OUTPUT);

  int i;
  byte numero = 33;

  for (i=0; i<256; i++)
   {  EscreverE2PROM(i, numero);
      Serial.printf("Endereço %d, valor escrito %d\n", i, numero); 
      digitalWrite (LED_AMARELO, HIGH);
      delay(50);
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


