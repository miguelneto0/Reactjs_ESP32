#include "DHT.h"
#include "WiFi.h"
#include <WebServer.h>

#define DHT_type DHT11      // DHT11
#define DHT_pin  4          // GPIO4 ou T0
                            // GPIO2 ou T2
                            // GPIO22 LED_BUILTIN
#define WIFI_timeout 10000

const char* ssid = "COMMON-Cilene";
const char* pswd = "cilene12";

unsigned long tempoUltimaLeitura = millis();
const long espera = 2000;

// Funcao que conecta o ESP32 na rede
void conectar(){
  // Imprime a mensagem inicial para tentar conectar
  Serial.print("Conectando à rede: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA); // habilita o wifi em modo estacao (STATION)
  WiFi.begin(ssid,pswd);

  unsigned long tempoInicial = millis(); // tempo inicial de contagem para timeout

  // laco que imprime o simbolo de carregamento ate o estouro de tempo (timeout)
  while(WiFi.status() != WL_CONNECTED && millis() - tempoInicial < WIFI_timeout){
    Serial.print(" #");
    delay(100);
  }
  // se nao conectar exibe falha
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Falha na conexao");
  }else{ // se conectar, exibe a mensagem com o IP
    Serial.print("\nConectado a ");
    Serial.print(ssid);
    Serial.print(" com IP ");
    Serial.println(WiFi.localIP());
  }
}

DHT dht(DHT_pin, DHT_type); // variavel para leitura pelo DHT11
WebServer server(80);

float temp, humi;
String valor = "";

#define LEDR 26
#define LEDG 27

void setup() {
  pinMode(T2, OUTPUT);      // LED ESP32
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);

  Serial.begin(115200);

  conectar();
  
  dht.begin();
  Serial.println("Lendo sensor DHT . . .");

  temp = dht.readTemperature();
  humi = dht.readHumidity();
  
  server.begin();           // inicializa o servidor
  
  Serial.println("Servidor WEB iniciado");
  delay(500);

  server.on("/", [](){
    server.send(200, "cabecalho", "Pagina Inicial\nSERVIDOR ESP32 INICIADO\n");
    delay(500);
  });
 
  server.on("/ledR/on", [](){
    server.send(200, "cabecalho", "LED vermelha acesa");
    digitalWrite(LEDR, HIGH);
    digitalWrite(T2, HIGH);
    delay(2000);
    if(digitalRead(LEDR) == HIGH){
      Serial.println("LED vermelha acesa");
    }
    Serial.println(digitalRead(LEDR));
  });

  server.on("/ledR/off", [](){
    server.send(200, "cabecalho", "LED vermelha apagada");
    digitalWrite(LEDR, LOW);
    digitalWrite(T2, LOW);
    delay(2000);
  });

  server.on("/ledG/on", [](){
    server.send(200, "cabecalho", "LED verde acesa");
    digitalWrite(LEDG, HIGH);
    delay(2000);
    if(digitalRead(LEDG) == HIGH){
      Serial.println("LED verde acesa");
    }
    Serial.println(digitalRead(LEDG));
  });

  server.on("/ledG/off", [](){
    server.send(200, "cabecalho", "LED verde apagada");
    digitalWrite(LEDG, LOW);
    delay(2000);
  });
  
  server.on("/sensor/temp", [](){
    valor = String(float(temp));
    server.send(200, "cabecalho", valor);
  });

  server.on("/sensor/humi", [](){
    valor = String(float(humi));
    server.send(200, "cabecalho", valor);
  });
}

void loop() {
  
  server.handleClient();

//  if(humi > 89){
//    digitalWrite(T2, HIGH); // ligando a LED do DHT
//    Serial.println("LED acesa :)");  
//  }else{
//    digitalWrite(T2, LOW);
//  }
//
  if(temp > 32){
    digitalWrite(LEDR, HIGH);
    digitalWrite(T2, HIGH);
  }else{
    digitalWrite(LEDR, LOW);
    digitalWrite(T2, LOW);
  }
  if(humi < 68){
    digitalWrite(LEDG, HIGH);
  }else{
    digitalWrite(LEDG, LOW);
  }
  Serial.println(digitalRead(LEDR));
  Serial.println(digitalRead(LEDG));
  Serial.print("Temperatura = ");
  Serial.print(temp);
  Serial.print(" C\t| ");
  
  Serial.print("Umidade = ");
  Serial.print(humi);
  Serial.print(" %");
  Serial.println();
  
  delay(2000);                    // aguarda 2s 
 
}
