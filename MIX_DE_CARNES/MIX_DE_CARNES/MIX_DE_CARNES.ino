#include <Wire.h>

// Forçando os pinos corretos para o ESP32-C3 Super Mini
#define SDA_PIN 6
#define SCL_PIN 7

void setup() {
  Serial.begin(115200);
  while (!Serial); // Aguarda o Monitor Serial abrir
  
  Serial.println("\n--- Scanner I2C para ESP32-C3 Super Mini ---");
  
  // Inicializa o barramento Wire definindo os pinos corretos
  Wire.begin(SDA_PIN, SCL_PIN);
}

void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Escaneando barramento I2C...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Sensor encontrado no endereço: 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    } 
    else if (error == 4) {
      Serial.print("Erro desconhecido no endereço: 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println("Nenhum sensor encontrado nos pinos 6 e 7.\n");
  } else {
    Serial.println("Escaneamento concluído.\n");
  }

  delay(3000); // Repete a busca a cada 3 segundos
}
