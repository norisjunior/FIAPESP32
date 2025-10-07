/* ESP32 3 LEDs
*/

int leds[] = {16, 17, 18}; // Ajuste os pinos
int tamanho = 3;

void setup() {
  for (int i = 0; i < tamanho; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < tamanho; i++) {
    digitalWrite(leds[i], HIGH);
    delay(200);
    digitalWrite(leds[i], LOW);
  }
  for (int i = tamanho - 2; i > 0; i--) {
    digitalWrite(leds[i], HIGH);
    delay(200);
    digitalWrite(leds[i], LOW);
  }
}
