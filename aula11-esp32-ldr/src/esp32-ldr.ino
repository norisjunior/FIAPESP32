/* LDR sensor */
#define LDR_PIN 34  // Pino analógico
#define LED_PIN 18

const float RL10 = 50;  //resistência a 10lux
const float GAMMA = 0.7; 
const float resistencia = 10400; // resistência interna da placa

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Detecção de baixa luminosidade");
}

void loop() {
  int ldrLido = analogRead(LDR_PIN);
  float voltagem = (ldrLido / 4095.0) * 3.3;
  float resistenciaLDR = (resistencia * voltagem) / (3.3 - voltagem);
  float lux = pow(RL10 * 1000 * pow(10, GAMMA) / resistenciaLDR, (1 / GAMMA));
  Serial.println("Luminosidade (lux): " + String(lux));

  if (lux < 100) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  
  delay(200);
}
