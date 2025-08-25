
#define LED 26
#define BOTAO 16

void setup() {
	Serial.begin(9600);

	pinMode(LED, OUTPUT);
	pinMode(BOTAO, INPUT);

	Serial.println("Pressione o botão para iniciar");
}

void loop() {
	while (digitalRead(BOTAO) == LOW) {
		//nada
	}

	Serial.println("Botão pressionado");
	digitalWrite(LED, HIGH);
	delay(1000);
	digitalWrite(LED, LOW);
}