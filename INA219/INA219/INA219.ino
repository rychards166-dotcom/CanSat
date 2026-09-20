#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina;


void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  if (!Serial) 
  {while (1) delay (10);}

  Wire.begin (6,7);
  if (!ina.begin ())
  {Serial.println("Ina não encontrado");
  while (1) delay (1000);}

  Serial.println("Teste inciado");

}

void loop() {
  // put your main code here, to run repeatedly:
  INA219();
  delay(1000);


}


void INA219 (){

  Serial.print("Tensão no Shunt: ");
  Serial.print(ina.getShuntVoltage_mV());
  Serial.println("mV");

  Serial.print("Corrente:");
  Serial.print(ina.getCurrent_mA());
  Serial.println("mA");

  Serial.print("Potencia:");
  Serial.print(ina.getPower_mW());
  Serial.println("mW");

  Serial.print("Load Voltage:  "); Serial.print(ina.getBusVoltage_V()); Serial.println(" V");
}