/* PWM com LED */

//PWM
#define CANAL 0
#define FREQ 1000
#define RESOLUCAO 8

// LED
#define LED 26

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  // Configuração do canal PWM para o buzzer
  ledcSetup(CANAL, FREQ, RESOLUCAO); // 1kHz, 8 bits de resolução
  ledcAttachPin(LED, CANAL);

  Serial.println("Sistema em operação: Controle de bilho do LED.");
}

void loop() {
	digitalWrite(LED, LOW);
	
	Serial.println("AUMENTANDO gradualmente o brilho do LED");
	for(int i = 0; i <= 255; i++) {
		Serial.printf("Brilho %i", i); Serial.println("");
		ledcWrite(CANAL, i);
		delay(100);
	}

	Serial.println("REDUZINDO gradualmente o brilho do LED");
	for(int i = 255; i >= 0; i--) {
		Serial.printf("Brilho %i", i); Serial.println("");
		ledcWrite(CANAL, i);
		delay(100);
	}
	
  delay(3000); // aguardar até a próxima leitura
	Serial.println("\n\nReiniciando os brilhos do LED.\n\n");
}
