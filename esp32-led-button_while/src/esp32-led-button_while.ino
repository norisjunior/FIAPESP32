#define LED 26
#define BOTAO 16

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Pressione o botão para acender o LED");
}

void loop() {
  while (digitalRead(BOTAO) == HIGH) {
    // Esperando botão ser pressionado
  }

  digitalWrite(LED, HIGH);
  Serial.println("Botão pressionado, LED aceso!");
  delay(2000);
  digitalWrite(LED, LOW);
}
