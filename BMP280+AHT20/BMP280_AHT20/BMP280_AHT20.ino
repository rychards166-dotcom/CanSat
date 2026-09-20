#include <Wire.h>
#include <AHT20.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // Cria o elemento "BMP280"
AHT20 aht;

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin (115200);
  
  if (!Serial)
  {while (1) delay (10);}
  
  Wire.begin (6,7);

  if (!aht.begin()) 
  {Serial.println (" AHT20 não encontrado");
  while (1) delay (1000);}

  if (!bmp.begin(0x77))
  { Serial.println("BMP280 não encontrado");
    while(1) delay(10);}

  Serial.println ("==== Teste iniciado ====");

 
}


void loop() {
  // put your main code here, to run repeatedly:
  AHT20 ();
  BMP280  ();
  delay (1000);

}


void AHT20 () {

  float Humidade = aht.getHumidity();
  
  if ( Humidade > 60) {
    
    Serial.println ("==========================");
    Serial.println ("Humidade tá muito boa!!!");
  }
  
  if ( Humidade < 60){

  Serial.println ("==========================");
  Serial.print ("Humidade = ");
  Serial.print (Humidade, 2);
  Serial.println ("%");
  }
}

void BMP280 () {

  // Mede a temperatura
  Serial.print(F("Temperatura = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" °C");

  
  //Imprimindo os valores de Pressão
  
  float pressão = bmp.readPressure();
  float realpressão = pressão/100;
  
  Serial.print(F("Pressão = "));
  Serial.print(realpressão, 2);
  Serial.println(" hPa");
  //Imprimindo os valores de Altitude Aproximada
  Serial.print(F("Altitude Aprox = "));
  Serial.print(bmp.readAltitude(1013.25)); /* Ajustar a pressão de nível do mar de acordo com o local!*/
  Serial.println(" m");

    Serial.println(F("=========================="));
  Serial.println();
}
