/* ESP32 Led-button
*/
int ledPin = 26;  // pino GPIO 5 conectado ao LED
int buttonPin = 23;  // pino GPIO 17 conectado ao botão

void setup() {
    pinMode(ledPin, OUTPUT);  // Define o pino do LED como saída.
    pinMode(buttonPin, INPUT);  // Define o pino do botão como entrada
}

void loop() {
    int buttonState = digitalRead(buttonPin);  // Lê o estado do botão
    
    if (buttonState == HIGH) {
       digitalWrite(ledPin, HIGH);  // Acende o LED
    } else {
        digitalWrite(ledPin, LOW);  // Apaga o LED
    }
}

