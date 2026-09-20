#include <Adafruit_MPU6050.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  if (!Serial)
    {while(1) delay(10);}

  Wire.begin (6,7);
  if(!mpu.begin())
    {Serial.println ("MPU não encontrado!");
    while (1) delay (1000);}

  Serial.println (" === Teste iniciado ===");
  delay (1000);

}


void loop() {
  // put your main code here, to run repeatedly:
  MPU6050 ();
  delay (1000);
  

}


void MPU6050 () {

  sensors_event_t ace, giro, temp;
  mpu.getEvent (&ace, &giro, &temp);

  Serial.print (" Aceleração eixo X:");
  Serial.println (ace.acceleration.x);
  Serial.print (" Aceleração eixo y:");
  Serial.println (ace.acceleration.y);
  Serial.print (" Aceleração eixo z:");
  Serial.println (ace.acceleration.z);
  Serial.print (" Giro eixo x:");
  Serial.println(giro.gyro.x);
  Serial.print (" Giro eixo y:");
  Serial.println(giro.gyro.y);
  Serial.print (" Giro eixo z:");
  Serial.println(giro.gyro.z);
}