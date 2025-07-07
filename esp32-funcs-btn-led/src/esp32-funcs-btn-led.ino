//Definições
#define BOTAO 16
#define LED 26

/* *** Funções início *** */
bool botaoPressionado() {
  return digitalRead(BOTAO) == LOW;
}

void ligarLed() {
  digitalWrite(LED, HIGH);
}

void desligarLed() {
  digitalWrite(LED, LOW);
}
/* *** Funções fim *** */


void setup() {
  pinMode(BOTAO, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (botaoPressionado()) {
    ligarLed();
  } else {
    desligarLed();
  }
}

