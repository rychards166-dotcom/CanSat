#include <Wire.h>
#include <AHT20.h>
#define Led 0

AHT20 aht;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  
  if (!Serial)
  {while (1) delay (10);}
  
  Wire.begin (6,7);

  if (!aht.begin()) 
  {Serial.println (" AHT20 não encontrado. Ajuste os cabos ou altere o endereço");
  while (1) delay (1000);}

  Serial.println ("==== Teste iniciado ====");

  pinMode (Led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  AHT20 ();

}

 AHT20 () {

  float Humidade = aht.getHumidity();
  
  if ( Humidade > 60) {
    
    Serial.println ("Humidade tá muito boa!!!");
    digitalWrite (Led, HIGH);
    delay (1000);
  }
  
  if ( Humidade < 60){

  Serial.println ("=======================");
  Serial.print (" Humidade = ");
  Serial.println (Humidade, 2);
  Serial.println ("=======================");
  digitalWrite (Led, LOW);
  delay (1000);
  }
  
  
  

}
