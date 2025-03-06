/* ESP32 Led-button
*/

int ledPin = 26;  // pino GPIO 26 conectado ao LED
int buttonPin = 5;  // pino GPIO 5 conectado ao botão

void setup() {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);  // Define o pino do LED como saída.
    pinMode(buttonPin, INPUT_PULLUP);  // Define o pino do botão como entrada
}

void loop() {
    int buttonState = digitalRead(buttonPin);  // Lê o estado do botão
    Serial.println(buttonState);

    if (buttonState == LOW) {
       digitalWrite(ledPin, HIGH);  // Acende o LED
       Serial.println("Botão pressionado!");
    } else {
        digitalWrite(ledPin, LOW);  // Apaga o LED
    }

    delay(100);
}
