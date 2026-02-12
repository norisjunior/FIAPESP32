/* ESP32 DHT22 */

#include <DHT.h>

#define DHTPIN 26
#define DHTMODEL DHT22

#define LED 25

DHT dht(DHTPIN, DHTMODEL);

float temp, umid;

void setup() {
    Serial.begin(115200);
    Serial.println("Leitura de temperatura e umidade");
    dht.begin();
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
}

void loop() {
    temp = dht.readTemperature();
    umid = dht.readHumidity();

    Serial.println("--- Temperatura: " + String(temp));
    Serial.println("--- Umidade: " + String(umid));

    if (temp > 20) {
        Serial.println("ALERTA: Temperatura Alta!");
        digitalWrite(LED, HIGH);
    }

    // Delay é importantíssimo, considerando o tipo de sensor usado!
    delay(3000);
    digitalWrite(LED, LOW);
    delay(1000);
}
