/* ESP32 */

#include <DHT.h>

#define DHTPIN 19
#define DHTMODEL DHT22

#define LEDVERMELHO 26

DHT dht(DHTPIN, DHTMODEL);

float temp, umid;
float hic;

void setup() {
    Serial.begin(9600);
    dht.begin();
    pinMode(LEDVERMELHO, OUTPUT);
}

void loop() {
    temp = dht.readTemperature();
    umid = dht.readHumidity();

    if (isnan(temp) || isnan(umid)) {
        Serial.printf("\nLeitura incorreta!");
        return;
    }

    hic = dht.computeHeatIndex(temp, umid, false);

    Serial.printf("\nTemperatura: %.2f. Umidade: %.2f, IC: %.2f", temp, umid, hic);
    Serial.println("");

    if ( hic > 20 ) {
        digitalWrite(LEDVERMELHO, HIGH);
        Serial.println("ATENÇÃO: Índice de Calor alto!");
    } else {
        digitalWrite(LEDVERMELHO, LOW);
    }

    delay(3000);
    digitalWrite(LEDVERMELHO, LOW);
}
