#include <Arduino.h>

// Definições de pinos
#define PIN_SENSOR 34  // Pino do sensor LDR (saída digital DO -> GPIO34, somente entrada)
#define PIN_LED    25  // Pino do LED -> resistor -> GND

// Configurações gerais
const bool INVERT = false;      // Se true, inverte a lógica do sensor
const int BRILHO_BAIXO = 50;    // Brilho mínimo (LED nunca apaga totalmente)
const int BRILHO_ALTO  = 255;   // Brilho máximo do LED

void setup() {
  // Configura os modos dos pinos
  pinMode(PIN_SENSOR, INPUT);   // Sensor como entrada
  pinMode(PIN_LED, OUTPUT);     // LED como saída

  // Inicia comunicação serial para monitorar no terminal
  Serial.begin(115200);         
  delay(100);                   // Espera um pouco antes de começar
  Serial.println("Init OK");    // Confirma inicialização
}

void loop() {
  // 1. Ler valor do sensor (0 ou 1)
  int s = digitalRead(PIN_SENSOR);  

  // 2. Decidir se o LED deve ser considerado "ligado"
  // Se o sensor retornar LOW e não estiver invertido → LED ligado
  bool ledOn = ((s == LOW) == INVERT);

  // 3. Definir brilho com base no estado
  //    - Se LED "ligado" → brilho alto
  //    - Se LED "desligado" → brilho baixo (não apaga totalmente)
  int brilho = ledOn ? BRILHO_ALTO : BRILHO_BAIXO;

  // 4. Configurar PWM no ESP32
  ledcAttachPin(PIN_LED, 0);    // Anexa o LED ao canal 0 do PWM
  ledcSetup(0, 5000, 8);        // Canal 0 → frequência 5kHz, resolução 8 bits (0–255)
  ledcWrite(0, brilho);         // Aplica o valor de brilho no canal 0

  // 5. Mostrar no Serial Monitor o estado atual
  Serial.print("DO=");          // Valor do sensor
  Serial.print(s);
  Serial.print("  LED=");       // Estado lógico
  Serial.print(ledOn ? "ALTO" : "BAIXO");
  Serial.print("  PWM=");       // Valor do PWM aplicado
  Serial.println(brilho);

  // 6. Pequena pausa antes da próxima leitura
  delay(50);
}