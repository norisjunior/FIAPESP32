/* ESP32 Led pisca-pisca
*/
int ledPin = 26;  // pino GPIO 26 conectado ao LED

void setup() {
    pinMode(ledPin, OUTPUT);  // Define o pino do LED como saída.
}

void loop() {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
}
