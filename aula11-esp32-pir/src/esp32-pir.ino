/* PIR sensor */

#define PIR_PIN 25
#define BUZZER_PIN 14

//PWM
#define CANAL 0
#define FREQ 1000
#define RESOLUCAO 8

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);

  // Configuração do canal PWM para o buzzer
  ledcSetup(CANAL, FREQ, RESOLUCAO); // 1kHz, 8 bits de resolução
  ledcAttachPin(BUZZER_PIN, CANAL);

  Serial.println("Sistema em operação: Alarme sonoro em caso de movimento.");
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) {
    Serial.println("Movimento detectado! Alarme!");
    ledcWriteTone(CANAL, 1000); // Ativa som de 1kHz
    delay(1500);
    ledcWriteTone(CANAL, 0);    // Desliga o som
  }

  delay(2000); // aguardar até a próxima leitura
}
