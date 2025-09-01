/* ESP32 2 LEDs
*/

void setup() {
    Serial.begin(9600);
    Serial.print("Inicializando");
    for (int i = 0; i < 3; i++) {
        delay(1000);
        Serial.print(".");
    }
    Serial.print("\n\n\n");

    Serial.println("AICSS - Checkpoint 2\n");

    Serial.println("\n---------------------------------------------------\n");

    #define LED_GREEN 13
    #define LED_RED 12

    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    /* *********************************************************************** */

    //Módulo 1 - Exercício 1 - Configure dois LEDs conectados ao ESP32.
    Serial.println("\n---------------------------------------------------\n");
    Serial.println("--- Módulo 1 - Exercício 1\n");
    const int tempoLigado = 3000;
    const int tempoDesligado = tempoLigado / 3;
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, HIGH);
    delay(tempoLigado);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    delay(tempoDesligado);

    /* *********************************************************************** */

    //Módulo 1 - Exercício 2 - 2.	Continuando do exercício anterior, ajuste o brilho dos LEDs com PWM. Use o tipo de variável inteira mais adequado para essa situação
    Serial.println("\n---------------------------------------------------\n");
    Serial.println("--- Módulo 1 - Exercício 2\n");
    uint8_t brilhoGREENLED = 32;
    uint8_t brilhoREDLED = 255;
    analogWrite(LED_GREEN, brilhoGREENLED);
    analogWrite(LED_RED, brilhoREDLED);
    delay(2000);
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_RED, 0);
    delay(2000);

    /* *********************************************************************** */

    //Módulo 1 - Exercício 3. Corrija o códgio:
    Serial.println("\n---------------------------------------------------\n");
    Serial.println("--- Módulo 1 - Exercício 3\n");
    int tempo = 1000;
    tempo = 2000;
    Serial.println("Tempo corrigido " + String(tempo));

    
    /* *********************************************************************** */
    /* *********************************************************************** */

    //Módulo 2 - Exercício 4. Atividades com char array:
    Serial.println("\n---------------------------------------------------\n");
    Serial.println("--- Módulo 2 - Exercício 4\n");
    char meuNome[20];
    int tamanhoVarmeuNome = 0;
    strcpy(meuNome, "AICSS");
    strcat(meuNome, " com ESP32!");
    tamanhoVarmeuNome = strlen(meuNome);
    Serial.println("Conteúdo do char meuNome: " + String(meuNome) + ". Tamanho do char: " + String(tamanhoVarmeuNome));

    /* *********************************************************************** */

    //Módulo 2 - Exercício 5. Atividades com String:
    Serial.println("\n---------------------------------------------------\n");
    Serial.println("--- Módulo 2 - Exercício 5\n");
    String conteudo = "Checkpoint";
    Serial.println("String, posição a posição: ");
    Serial.println("conteudo[0]: " + String(conteudo[0]));
    Serial.println("conteudo[1]: " + String(conteudo[1]));
    Serial.println("conteudo[2]: " + String(conteudo[2]));
    Serial.println("conteudo[3]: " + String(conteudo[3]));
    Serial.println("conteudo[4]: " + String(conteudo[4]));
    Serial.println("conteudo[5]: " + String(conteudo[5]));
    Serial.println("conteudo[6]: " + String(conteudo[6]));
    Serial.println("conteudo[7]: " + String(conteudo[7]));
    Serial.println("conteudo[8]: " + String(conteudo[8]));
    Serial.println("conteudo[9]: " + String(conteudo[9]));

    /* *********************************************************************** */

    //Módulo 3 - Exercício 6. Atividades com String:
    Serial.println("\n---------------------------------------------------\n");
    Serial.println("--- Módulo 2 - Exercício 6\n");

    uint64_t startTime = 0;
    uint64_t endTime = 0;
    
    String nconteudo = "Checkpoint";

    startTime = esp_timer_get_time();
    delay(1500);
    Serial.println("String, posição a posição: ");
    Serial.println("conteudo[0]: " + String(nconteudo[0]));
    Serial.println("conteudo[1]: " + String(nconteudo[1]));
    Serial.println("conteudo[2]: " + String(nconteudo[2]));
    Serial.println("conteudo[3]: " + String(nconteudo[3]));
    Serial.println("conteudo[4]: " + String(nconteudo[4]));
    Serial.println("conteudo[5]: " + String(nconteudo[5]));
    Serial.println("conteudo[6]: " + String(nconteudo[6]));
    Serial.println("conteudo[7]: " + String(nconteudo[7]));
    Serial.println("conteudo[8]: " + String(nconteudo[8]));
    Serial.println("conteudo[9]: " + String(nconteudo[9]));
    endTime = esp_timer_get_time();
    
    uint64_t elapsedTime = endTime - startTime;
    Serial.println("Tempo decorrido: " + String(elapsedTime) + String("us."));

    

    /* *********************************************************************** */

    //Módulo 4 - Exercício 8.
    Serial.println("\n---------------------------------------------------\n");
    Serial.println("--- Módulo 4 - Exercício 8\n");
    uint16_t numero16bitsInicial = 10000;
    uint16_t numero16bitsFinal = numero16bitsInicial + 30000;
    Serial.println("Resultado da soma usando uint16_t: " + String(numero16bitsFinal));


    /* *********************************************************************** */

    //Módulo 5 - Exercício 9.
    Serial.println("\n---------------------------------------------------\n");
    Serial.println("--- Módulo 5 - Exercício 9\n");
    float temperatura = 25.7;
    float umidade = 70.1;
    float ic = temperatura + (0.3 * umidade) - 0.7;

    Serial.print("Índice de Calor: " + String(ic));
    Serial.print("| Temperatura: " + String(temperatura) + " ºC");
    Serial.println("| Umidade: " + String(umidade) + " %");
  
  
    /* *********************************************************************** */

    //Módulo 6 - Exercício 10.
    Serial.println("\n---------------------------------------------------\n");
    Serial.println("--- Módulo 6 - Exercício 10\n");
    float potencia = 0;
    float tensao = 0;
    float resistencia = 0;

    tensao = 3.3;
    resistencia = 100;
    potencia = (pow(tensao, 2)) / resistencia;
    Serial.println("Potência: " + String(potencia));
  


}

void loop() {

    /* *********************************************************************** */

    //Módulo 4 - Exercício 7.
    Serial.println("\n---------------------------------------------------\n");
    Serial.println("--- Módulo 4 - Exercício 7\n");

    String umNumeroEmTexto = "55000";
    uint16_t umNumeroEmNumero = umNumeroEmTexto.toInt();
    Serial.println("Número uint16_t umNumeroEmNumero: " + String(umNumeroEmNumero));
    delay(5000);

}