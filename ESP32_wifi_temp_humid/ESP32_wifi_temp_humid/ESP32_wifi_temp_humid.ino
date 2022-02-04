#include "DHT.h"
#include "WiFi.h"
#include <WebServer.h>

#define DHT_type DHT11              // DHT11
#define DHT_pin  4                  // GPIO4 ou T0
                                    // GPIO2 ou T2
                                    // GPIO22 LED_BUILTIN
#define WIFI_timeout 10000          // tempo total de espera para conectar WiFi
DHT dht(DHT_pin, DHT_type);         // variavel para leitura pelo DHT11
WebServer server(80);               // variavel que gerencia o servidor web

float temp, humi;                   // variaveis para os dados de temperatura e umidade
String valor = "";                  // string que manipulara os dados lidos

#define LEDR 26                     // GPIO 26 (P26) para a LED vermelha
#define LEDG 27                     // GPIO 27 (P27) para a LED verde

const char* ssid = "COMMON-Cilene"; // nome da rede
const char* pswd = "cilene12";      // senha da rede

// Funcao que conecta o ESP32 na rede
void conectar(){
  // Imprime a mensagem inicial para tentar conectar
  Serial.print("Conectando à rede: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA); // habilita o wifi em modo estacao (STATION)
  WiFi.begin(ssid,pswd);

  unsigned long tempoInicial = millis(); // tempo inicial lido para contagem para timeout

  // laco que imprime o simbolo de carregamento ate o estouro de tempo (timeout)
  while(WiFi.status() != WL_CONNECTED && millis() - tempoInicial < WIFI_timeout){
    Serial.print(" #");
    delay(100);
  }
  
  if(WiFi.status() != WL_CONNECTED){      // se nao conectar exibe falha
    Serial.println("Falha na conexao");
  }else{                                  // se conectar, exibe a mensagem com o IP
    Serial.print("\nConectado a ");
    Serial.print(ssid);
    Serial.print(" com IP ");
    Serial.println(WiFi.localIP());
  }
}

void setup() {
  pinMode(T2, OUTPUT);                  // configura LED_BUILTIN do ESP32
  pinMode(LEDR, OUTPUT);                // configura LED vermelha como saida
  pinMode(LEDG, OUTPUT);                // configura LED verde como saida

  Serial.begin(115200);                 // baudrate adequado do ESP32

  conectar();                           // chama a funcao de conexao WiFi
  
  dht.begin();                          // inicia a leitura do sensor DHT11
  Serial.println("Lendo sensor DHT . . .");

  temp = dht.readTemperature();         // separa o dado lido para temperatura em 'temp'
  humi = dht.readHumidity();            // separa o dado lido para humidade em 'humi'
                                        // se apenas read() sao coletados ambos valores
  server.begin();                       // iniciao servidor
  
  Serial.println("Servidor WEB iniciado");
  delay(500);

  // define a pagina inicial do servidor
  server.on("/", [](){
    server.send(200, "cabecalho", "Pagina Inicial\nSERVIDOR ESP32 INICIADO\n");
    delay(500);
  });

  // define a pagina para acender o LED vermelho
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

  // define a pagina para apagar o LED vermelho
  server.on("/ledR/off", [](){
    server.send(200, "cabecalho", "LED vermelha apagada");
    digitalWrite(LEDR, LOW);
    digitalWrite(T2, LOW);
    delay(2000);
  });

  // define a pagina para acender o LED verde
  server.on("/ledG/on", [](){
    server.send(200, "cabecalho", "LED verde acesa");
    digitalWrite(LEDG, HIGH);
    delay(2000);
    if(digitalRead(LEDG) == HIGH){
      Serial.println("LED verde acesa");
    }
    Serial.println(digitalRead(LEDG));
  });

  // define a pagina para apagar o LED verde
  server.on("/ledG/off", [](){
    server.send(200, "cabecalho", "LED verde apagada");
    digitalWrite(LEDG, LOW);
    delay(2000);
  });

  // define a pagina para coletar o dado de temperatura
  server.on("/sensor/temp", [](){
    valor = String(float(temp));
    server.send(200, "cabecalho", valor);
  });

  // define a pagina para coletar o dado de humidade
  server.on("/sensor/humi", [](){
    valor = String(float(humi));
    server.send(200, "cabecalho", valor);
  });
}

void loop() {
  // chama a funcao que gerencia as requisicoes para o servidor  
  server.handleClient();

  // testes para verificar a resposta na placa
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

  // testes para verificar os dados pelo 
  // Monitor Serial da plataforma Arduino IDE
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
