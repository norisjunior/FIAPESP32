//Include
#include <DHT.h>

//DHT
#define DHTPIN 21
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//LED
#define LED 26

//Botão
#define BOTAO 17

//Tempo padrão
const int temporizador = 3000;


void setup() {
	Serial.begin(115200);
	dht.begin();

	pinMode(LED, OUTPUT);
	pinMode(BOTAO, INPUT_PULLUP);

	Serial.println("Bem-vindo! \n Miniestação climática ligada.");
	Serial.println("\n\nPressione o botão (e mantenha pressionado para a coleta de medições.)");
}

void loop() {
	float temp, umid, hic = 0.0;
	bool isConfort = false;

	while(digitalRead(BOTAO) == LOW) {
		Serial.println("\n\nMedições iniciadas.");

		temp = dht.readTemperature();
		umid = dht.readHumidity();

		if ( (isnan(temp)) || (isnan(umid)) ) {
			Serial.println("Medições inválidas. Retornando...");
			delay(2000);
			return;
		}

		hic = dht.computeHeatIndex(temp, umid, false);

		Serial.printf("Medições: Temperatura: %.2f, Umidade: %.2f, IC: %.2f.", temp, umid, hic);
		Serial.println("");

		if (hic > 25) {
			Serial.println("\nÍndice de Calor Alto! LED Aceso.");
			digitalWrite(LED, HIGH);
		} else {
			Serial.println("\nÍndice de Calor Baixo. LED Apagado.");
			digitalWrite(LED, LOW);
		}

		isConfort = (umid > 30 && umid <= 80) ? true : false;
		Serial.print("Umidade confortável? ");
		Serial.println(isConfort ? "Sim" : "Não");

		Serial.print("Umidade confortável? ");
		Serial.println((umid > 30 && umid <= 80) ? "Sim" : "Não");
		
		delay(temporizador);
	}
	
}

