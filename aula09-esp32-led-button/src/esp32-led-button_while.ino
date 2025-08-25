#define LED 26
#define BOTAO 16

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Mantenha o botão pressionado para acender o LED");
}

void loop() {
  while (digitalRead(BOTAO) == LOW) {
	digitalWrite(LED, HIGH);
	delay(200);
	digitalWrite(LED, LOW);
	delay(200);
  }
}
