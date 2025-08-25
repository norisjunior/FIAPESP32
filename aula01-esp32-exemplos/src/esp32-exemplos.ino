/* ESP32 Led pisca-pisca
*/

#include <string>

void setup() {
    Serial.begin(115200);

    char palavra[6] = "AICSS";
    char letra;
    letra = palavra[1];
    Serial.println(letra);

    std::string texto = "AICSS: ESP32 rocks!";
    letra = texto[13];
    Serial.println(letra);

    
}

void loop() {
    //
}
