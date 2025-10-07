// Cria uma STRUCT para armazenar os dados de uma pessoa
struct PESSOA {
    int idade;    // define o campo idade
    float peso;   // define o campo peso
    float altura; // define o campo altura
}; // Define o nome do novo tipo criado

void setup() {
    Serial.begin(115200);

    PESSOA Pele;
    Pele.idade = 82;
    Pele.peso = 73.0;
    Pele.altura = 1.73;
    //Atenção: requer que seja na mesma ordem!
    PESSOA Messi{ .idade = 38, .peso = 67.0, .altura = 1.70 };
    Serial.printf("Dados do Pelé: Idade: %d, Peso: %.2f, Altura: %.2f.",
        Pele.idade, Pele.peso, Pele.altura); Serial.println("");
    Serial.printf("Dados do Messi: Idade: %d, Peso: %.2f, Altura: %.2f.",
        Messi.idade, Messi.peso, Messi.altura); Serial.println("");
}

void loop() {
    // Nada
}
 