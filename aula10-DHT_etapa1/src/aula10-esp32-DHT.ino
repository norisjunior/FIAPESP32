/* ESP32 DHT22 */

#include <DHT.h>

#define DHTPIN 26
#define DHTMODEL DHT22

DHT dht(DHTPIN, DHTMODEL);

float temp, umid;

void setup() {
    Serial.begin(115200);
    Serial.println("Leitura de temperatura e umidade");
    dht.begin();
}

void loop() {
    temp = dht.readTemperature();
    umid = dht.readHumidity();

    // Calcula índice de calor (heat index)
    hi = dht.computeHeatIndex(temp, umid, false);

    Serial.println("--- Temperatura: " + String(temp));
    Serial.println("--- Umidade: " + String(umid));
    Serial.printf("--- Índice de calor (Heat Index): %.2f", hi);
    Serial.println("");
    Serial.println("------------------------------------------------");

    if (temp > 35) {
        Serial.println("ALERTA: Temperatura Alta!");
    }

    // Delay é importantíssimo, considerando o tipo de sensor usado!
    delay(3000);
}
