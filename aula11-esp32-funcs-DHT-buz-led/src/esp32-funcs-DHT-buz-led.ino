/* Definições e variáveis globais - início */
//DHT
#include "DHT.h"
#define DHTPIN 21
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//Buzzer
#define BUZZER 27

//PWM
#define CANAL 0
#define FREQ 1000
#define RESOLUCAO 8

//LED
#define LED 26
/* Definições e variáveis globais - fim */


/* Funções - início */
void inicializaSensores() {
  //DHT
  dht.begin();

  //LED 
  pinMode(LED, OUTPUT);

  //Buzzer
  pinMode(BUZZER, OUTPUT);
  ledcSetup(CANAL, FREQ, RESOLUCAO);
  ledcAttachPin(BUZZER, CANAL);  
}

float lerTemperatura() {
  return dht.readTemperature();
}

void imprimeTemperatura(float varTemp) {
  Serial.println("Temp: " + String(varTemp) + "ºC");	
}

float lerUmidade() {
	return dht.readHumidity();
}

void ativarAlarme() {
  ledcWriteTone(CANAL, 1000); // Ativa som de 1kHz
}

void desativarAlarme() {
  ledcWriteTone(CANAL, 0);
}

void acendeLED(float varUmid) {
	bool status = varUmid < 20 ? HIGH : LOW;
	digitalWrite(LED, status);
}
/* Funções - fim */


void setup() {
  Serial.begin(115200);
  inicializaSensores();
}

void loop() {
  float temperatura = lerTemperatura();
  float umidade = lerUmidade();
  imprimeTemperatura(temperatura);

  if (temperatura > 40) {
    ativarAlarme();
  } else {
    desativarAlarme();
  }

  acendeLED(umidade);

  delay(2000);
}

