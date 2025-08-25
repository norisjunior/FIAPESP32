// LED
#define LEDRED   25
#define LEDBLUE  26
#define LEDGREEN 27

String comando = "";            // Armazena o comando completo
bool acendeRed   = false;
bool acendeBlue  = false;
bool acendeGreen = false;

void setup() {
  Serial.begin(115200);
  pinMode(LEDRED,   OUTPUT);
  pinMode(LEDBLUE,  OUTPUT);
  pinMode(LEDGREEN, OUTPUT);
  Serial.println("Digite o comando (ex: RED, GREEN, BLUE): ");
}

void loop() {
  // Enquanto houver dados no buffer, leia caractere a caractere
  while (Serial.available() > 0) {          
    char c = Serial.read();                 
    Serial.print(c);                        

    // Se chegou end-of-line, processa o comando completo
    if (c == '\n' || c == '\r') { // CR ou LF
      comando.trim();  // Remove espaços/brancos
      Serial.print("Você digitou: ");
      Serial.println(comando);

      // Lógica de acionamento dos LEDs
      acendeRed   = (comando == "RED");
      acendeBlue  = (comando == "BLUE");
      acendeGreen = (comando == "GREEN");

      digitalWrite(LEDRED,   acendeRed   ? HIGH : LOW);
      digitalWrite(LEDBLUE,  acendeBlue  ? HIGH : LOW);
      digitalWrite(LEDGREEN, acendeGreen ? HIGH : LOW);

      delay(1500);
      Serial.println("\nDigite o comando (ex: RED, GREEN, BLUE): ");

      comando = "";  // Reseta o buffer para o próximo comando
    } else {
      comando += c;  // Constrói a string enquanto não chega ENTER
    }
  }
  delay(50);
}
