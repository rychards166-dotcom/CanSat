#define Led 0
#define Res 1
#include <Wire.h> // Biblioteca I2C 
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // Cria o elemento "BMP280"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  // Inicia o Serial em 9600 bits/s
  Wire.begin (21, 22); 
  // Considera os pinos 6 e 7 como SDA e SCL
  while (!Serial) delay (10); 
  // Aguarda o Serial
  if (!bmp.begin(0x77))
  {
    Serial.println("BMP280 não encontrado");
    while(1) delay(10);
  }

  Serial.println("=== Teste do BMP280+AHT20 Iniciado === ");
  delay(2000);

}

void loop() {
   // put your main code here, to run repeatedly:
   BMP ();
   delay(10);
}


void BMP () {

  // Mede a temperatura
  Serial.println(F("=========================="));
  
  Serial.print(F("Temperatura = "));
  Serial.print(bmp.readTemperature(), BIN);
  Serial.println("*C");

  
  //Imprimindo os valores de Pressão
  Serial.print(F("Pressão = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
  //Imprimindo os valores de Altitude Aproximada
  Serial.print(F("Altitude Aprox = "));
  Serial.print(bmp.readAltitude(1013.25)); /* Ajustar a pressão de nível do mar de acordo com o local!*/
  Serial.println(" m");

    Serial.println(F("=========================="));
  Serial.println();
  delay(1000);
}