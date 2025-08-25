/* ESP32 DHT22
*/

#include <DHT.h>

#define LEDRED 26

#define DHTPIN 19
#define DHTMODEL DHT22

DHT dht(DHTPIN, DHTMODEL);

float temp, umid, hi;

int idMedicao = 1;

float tempMedia, umidMedia, icMedio = 0;

void setup() {
    Serial.begin(115200);
    pinMode(LEDRED, OUTPUT);
    dht.begin();
    Serial.println("Leitura de temperatura e umidade");
}

void loop() {

    /* *** Medições *** */
    temp = dht.readTemperature();
    umid = dht.readHumidity();

    // Verifica se houve erro de leitura e sai do loop
    if (isnan(umid) || isnan(temp)) {
        Serial.println("Falha na leitura!");
        return;
    }

    // Calcula índice de calor (heat index)
    hi = dht.computeHeatIndex(temp, umid, false);


    /* Zera contador */
    if (idMedicao > 4) {
        idMedicao = 1;
        tempMedia = 0;
        umidMedia = 0;
        icMedio = 0;
    }


    /* Mostra condições atuais */
    Serial.printf("\n--- Temperatura id %d: %.2f.\n", idMedicao, temp);
    Serial.printf("\n--- Umidade id %d: %.2f.\n", idMedicao, umid);
    Serial.printf("\n--- Índice de calor (Heat Index) id %d: %.2f.\n", idMedicao, hi);
    Serial.println("");
    Serial.println("------------------------------------------------");


    /* Soma */
    tempMedia += temp;
    umidMedia += umid;
    icMedio += hi;

    if (idMedicao == 4) {
        tempMedia = tempMedia / idMedicao;
        umidMedia = umidMedia / idMedicao;
        icMedio = icMedio / idMedicao;
        Serial.println("--- Média de 4 medições:");
        Serial.printf("--- Média de temperatura: %.2f, Média de umidade: %.2f, IC médio: %.2f.", tempMedia, umidMedia, icMedio);
        Serial.println("\n------------------------------------------------");
        if (icMedio > 20) {
            Serial.println("\n*-*-*-*-*- ALERTA: Índice de Calor Alto! *-*-*-*-*-\n\n");
            digitalWrite(LEDRED, HIGH);
        }
        Serial.println("\n---\n");
    }

    // Delay é importantíssimo, considerando o tipo de sensor usado!
    delay(3000);
    digitalWrite(LEDRED, LOW);
    idMedicao++;

}
