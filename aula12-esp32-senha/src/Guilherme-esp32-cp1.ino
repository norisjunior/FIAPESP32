/*
Guilherme Gama Bitencourt Souza |RM: 565293
Carolina Novakc Moraes |RM: 565621
Felipe Ferraz Vieira |RM: 561451
*/

// Biblioteca para o hash da senha
#include "mbedtls/sha256.h"

// Definições dos pinos
// HC-SR04
#define TRIG_PIN 25
#define ECHO_PIN 26

// LEDS
#define LED_AZUL 21
#define LED_VERMELHO 4

// Configuração de PWM do Buzzer e Led
// PWM - BUZZER
#define BUZZER 27
#define CANAL_BUZZER 1
#define FREQ_BUZZER 1000

// PWM - LED
#define CANAL 0
#define FREQ 1000
#define RESOLUCAO 8 // 8 bits de 0 a 255 (brilho do led)

// Senha (hash SHA-256 de "1234")
const char* senha_hash_hex = "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4";

// Variáveis globais
int tentativas = 3; // quantas x o usuário pode errar a senha de ADMIN
String comando = ""; // guarda o que o usuário digitou no Serial.
bool modoMonitoramento = false; // controla se está rodando o modo ADMIN ou o monitoramento

// Função para converter bytes para string hexadecimal
String bytesToHex(const uint8_t* hash, size_t len) {
  String hex = "";
  const char hexChars[] = "0123456789abcdef";
  for (size_t i = 0; i < len; i++) {
    hex += hexChars[(hash[i] >> 4) & 0x0F];
    hex += hexChars[hash[i] & 0x0F];
  }
  return hex;
}

// Função para calcular SHA-256
String sha256(String entrada) {
  uint8_t hash[32];  // 32 bytes
  mbedtls_sha256_context ctx;

  mbedtls_sha256_init(&ctx);
  mbedtls_sha256_starts_ret(&ctx, 0); // 0 = SHA-256
  mbedtls_sha256_update_ret(&ctx, (const unsigned char*)entrada.c_str(), entrada.length());
  mbedtls_sha256_finish_ret(&ctx, hash);
  mbedtls_sha256_free(&ctx);

  return bytesToHex(hash, sizeof(hash));
}


// Método: Ativa o TRIG, mede o tempo de respota no ECHO e convertem em centímetros
int lerDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, LOW);

  int duracao = pulseIn(ECHO_PIN, HIGH);
  int distancia = duracao * 0.034 / 2;
  return distancia;
}

// Método: Faz o led vermelho aumentar o brilho até 255 e depois diminuí até 0 usando PWM
void pulsarLed() {
  for (int i = 0; i <= 255; i++) {
    ledcWrite(CANAL, i);
    delay(5);
  }

  for (int i = 255; i >= 0; i--) {
    ledcWrite(CANAL, i);
    delay(5);
  }
}

// Método: Faz mudar o volume do Buzzer, usando PWM
void buzzerVolume(int volume) {
  if (volume > 0) {
    ledcWrite(CANAL_BUZZER, volume);
  } else {
    ledcWrite(CANAL_BUZZER, 0);
  }
}

void setup() {
  Serial.begin(115200);

  // Configuração de entrada e saída dos pinos
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_AZUL, OUTPUT);

  // PWM LED
  pinMode(LED_VERMELHO, OUTPUT);
  ledcSetup(CANAL, FREQ, RESOLUCAO);
  ledcAttachPin(LED_VERMELHO, CANAL);

  // PWM BUZZER
  pinMode(BUZZER, OUTPUT);
  ledcSetup(CANAL_BUZZER, FREQ_BUZZER, RESOLUCAO);
  ledcAttachPin(BUZZER, CANAL_BUZZER);

  Serial.println("Sistema inicializado!");
  Serial.println("Deseja iniciar o sistema de monitoramento? (S/N)");
  Serial.println(" "); 
}

void loop() {
  // Verifica se o usuário digitou algo
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      // Função trim apaga espaços em branco
      comando.trim();

      // Se usuário escolher monitoramento
      if (comando.equalsIgnoreCase("S")) {
        modoMonitoramento = true;
        Serial.println("Monitoramento iniciado...");
      }

      // Se usuário digitou ADMIN
      if (comando.equalsIgnoreCase("ADMIN")) {
        while (tentativas > 0) {
          Serial.println("Digite a senha: ");
          Serial.setTimeout(5000);
          // Lê todps os caracteres digitados até o enter
          String pass = Serial.readStringUntil('\n');
          pass.trim();

          String hashDigitado = sha256(pass);

          if (!hashDigitado.equalsIgnoreCase(senha_hash_hex)) {
            tentativas--;
            if (tentativas == 0) {
              Serial.println("Tentativas de senha máximas atingidas. Sistema bloqueado!");
              while (1); // trava até reiniciar
            }
            Serial.print("Senha incorreta. Tentativas restantes: ");
            Serial.println(tentativas);
            // volta para o while -> pede senha de novo
          } else {
            Serial.println("ÁREA ADMIN: ACESSO PERMITIDO");
            // Todos os LEDs acesos
            digitalWrite(LED_AZUL, HIGH);
            digitalWrite(LED_VERMELHO, HIGH);
            // Importante essa parte
            // garante brilho no LED vermelho
            ledcWrite(CANAL, 255);   

            // Buzzer desligado
            buzzerVolume(0);

            tentativas = 3; // reseta tentativas
            break; // sai do while
          }
        }
      }

      // Após o enter, o código já processou o comando digitado e limpa a variável
      comando = "";
    } else {
      // Cada caractere que o usuário digitou é acrescentando nessa variável
      comando += c;
    }
  }

  // --- Monitoramento só roda se usuário escolheu ---
  if (modoMonitoramento) {
    Serial.print("Distância (cm): ");
    int distancia = lerDistancia();
    Serial.println(distancia);

    if (distancia < 50) {
      ledcWrite(CANAL, 0);
      digitalWrite(LED_AZUL, HIGH);
      buzzerVolume(30);
      delay(1000);
    } else {
      digitalWrite(LED_AZUL, LOW);
      buzzerVolume(0);
      pulsarLed();
    }
    delay(100);
  }
}
