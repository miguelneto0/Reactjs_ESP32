#include "DHT.h"

#define DHT_type DHT11      // DHT11
#define DHT_pin  4          // GPIO4 ou T0
                            // GPIO2 ou T2
                            // GPIO22 LED_BUILTIN

DHT dht(DHT_pin, DHT_type); // variavel para leitura pelo DHT11

void setup() {
  pinMode(T2, OUTPUT);      // LED ESP32
//  pinMode(P4, INPUT);       // DHT 11 na Porta P4
  Serial.begin(115200);
  Serial.println(F("DHTxx test"));
  dht.begin();
  Serial.println("Lendo sensor DHT . . .");
}

void loop() {

  float temp = dht.readTemperature();
  float humi = dht.readHumidity();

  if(humi > 89){
    digitalWrite(T2, HIGH); // ligando a LED do DHT
    Serial.println("LED acesa :)");  
  }else{
    digitalWrite(T2, LOW);
//    Serial.println("LED apagada :(");  
  }

  Serial.print("Temperatura = ");
  Serial.print(temp);
  Serial.print(" C\t| ");
  
  Serial.print("Umidade = ");
  Serial.print(humi);
  Serial.print(" %");
  Serial.println();
  
  delay(2000);                    // aguarda 2s 
 
}
