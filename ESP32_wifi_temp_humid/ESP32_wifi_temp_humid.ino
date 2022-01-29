#include "WiFi.h"

#define TIMEOUT 20000

const char* ssid = "Lino neto";
const char* pswd = "t25t06z15";

void conectar(){
  Serial.print("Conectando à rede");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pswd);

  unsigned long tempoInicial = millis();

  while(WiFi.status() != WL_CONNECTED && millis() - tempoInicial < TIMEOUT){
    Serial.print(" #");
    delay(100);
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Falha na conexao");
  }else{
    Serial.print("Conectado a ");
    Serial.print(ssid);
    Serial.print(" com IP ");
    Serial.println(WiFi.localIP());
  }
}

void setup() {
  Serial.begin(115200);
  conectar();  
}

void loop() {
  
}
