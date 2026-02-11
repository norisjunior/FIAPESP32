/* ESP32 DHT22
*/

#include <DHT.h>

#define DHTPIN 19
#define DHTMODEL DHT22

DHT dht(DHTPIN, DHTMODEL);

float temp, umid;
float hi;

void setup() {
    Serial.begin(115200);
    Serial.println("Leitura de temperatura e umidade");
    dht.begin();
}

void loop() {
    temp = dht.readTemperature();
    umid = dht.readHumidity();

    // Verifica se houve erro de leitura e sai do loop
    if (isnan(umid) || isnan(temp)) {
        Serial.println("Falha na leitura!");
        return;
    }

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
