/* ESP32 2 LEDs
*/

int ledGreenPin = 13;  
int ledRedPin = 12;  

void setup() {
    Serial.begin(9600);
    Serial.println("ESP32 rocks!\n\n");
    Serial.print("Inicializando");
    for (int i = 0; i < 3; i++) {
        delay(1000);
        Serial.print(".");
    }
    Serial.print("\n\n\n");

    pinMode(ledGreenPin, OUTPUT);  // Define o pino do LED como saída.
    pinMode(ledRedPin, OUTPUT);  // Define o pino do LED como saída.
}

void loop() {

    Serial.println("\n\n----------- Aplicação: 2 LEDs -----------");

    digitalWrite(ledGreenPin, HIGH);
    digitalWrite(ledRedPin, HIGH);
    delay(1000);
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledGreenPin, LOW);
    delay(1000);    

}