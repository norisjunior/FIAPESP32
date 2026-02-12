/* CÓDGIO ESP32 - DHT22 - PINO 26 */

#include <DHT.h>

#define DHTPIN 26
#define DHTMODEL DHT22

DHT dht(DHTPIN, DHTMODEL);

#define LED 25

void setup() {
    Serial.begin(115200);
    Serial.println("Aula 00 - Leitura de temp e umid");
    dht.begin();
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
}

void loop() {
    float temp, umid;

    temp = dht.readTemperature();
    umid = dht.readHumidity();

    Serial.println("-- Temperatura: " + String(temp));
    Serial.println("-- Umidade: " + String(umid));

    if (temp > 25) {
        Serial.println("ALERTA: TEMPERATURA ELEVADA!");
        digitalWrite(LED, HIGH);
    }

    delay(2000);
    digitalWrite(LED, LOW);
    delay(1000);
}