/* HC-SR04 */

#define TRIG_PIN 25
#define ECHO_PIN 26
#define LED_PIN 21

int readUltrasonicDistance() {
  // Etapa 1: Garante estabilidade prévia à leitura
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Etapa 2: Pulso de disparo de 10 microssegundos 
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Etapa 3: Quanto tempo se passou até o obstáculo
  int duracao = pulseIn(ECHO_PIN, HIGH);
  // Etapa 4: Calcula em centímetros (som = 340 m/s = 0.034 cm/µs)
  int distancia = duracao * 0.034 / 2; // /2 -> ida e volta
  return distancia;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  Serial.print("Distância (cm): ");
  int distance = readUltrasonicDistance();
  Serial.println(distance);
  if (distance < 50) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(300);
}
