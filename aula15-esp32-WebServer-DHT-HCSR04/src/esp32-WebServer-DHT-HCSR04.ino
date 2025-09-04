//Includes
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <DHT.h>


//WebServer
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
const char* HTTPCHARSET = "charset=utf-8";
const uint8_t WIFI_CHANNEL = 6;
WebServer server(80);

//LED
#define PIN_LED 21

//DHT
#define DHTPIN 27
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//HC-SR04
#define TRIG_PIN 25
#define ECHO_PIN 26


// Função para medir distância com HC-SR04
float lerDistanciaCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duracao = pulseIn(ECHO_PIN, HIGH);
  float distancia = duracao * 0.034 / 2;
  return distancia;
}

// Rota para temperatura
void handleTemperatura() {
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    server.send(500, HTTPCHARSET, "Erro ao ler temperatura");
  } else {
    server.send(200, HTTPCHARSET, String(temp) + " °C");
  }
}

// Rota para umidade
void handleUmidade() {
  float hum = dht.readHumidity();
  if (isnan(hum)) {
    server.send(500, HTTPCHARSET, "Erro ao ler umidade");
  } else {
    server.send(200, HTTPCHARSET, String(hum) + " %");
  }
}

// Rota para distância
void handleDistancia() {
  float dist = lerDistanciaCM();
  server.send(200, HTTPCHARSET, String(dist) + " cm");
}

int tempoAnterior = 0;
bool estadoLED = 0;
void piscar(int intervalo = 1000) {
  int tempoAtual = millis();
  
  if ( (tempoAtual - tempoAnterior) >= intervalo ) {
    estadoLED = !estadoLED;
    digitalWrite(PIN_LED, estadoLED);
    tempoAnterior = tempoAtual;
  }
}



void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(PIN_LED, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Rotas
  server.on("/temp", handleTemperatura);
  server.on("/umid", handleUmidade);
  server.on("/dist", handleDistancia);

  //Página inicial
  server.on("/", []() {
    String page = "<h1> *** Bem-vindo ao Servidor ESP32! *** </h1>\n\n";
    page += "Rotas disponíveis:<br>\n";
    page += " - /temp --> temperatura em °C<br>\n";
    page += " - /umid --> umidade em %<br>\n";
    page += " - <strong>/dist</strong> --> distância em cm<br>\n";
    server.send(200, HTTPCHARSET, page);
  });

  server.begin();
  Serial.println("Servidor iniciado! (http://localhost:8180)");
}

void loop() {
  server.handleClient();
  piscar(250);
  delay(10);
}
