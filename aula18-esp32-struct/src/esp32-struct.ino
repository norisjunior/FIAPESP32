/* Struct */

struct PESSOA {
	String nome;
	int idade;
    float peso;
    float altura;
};

void imprimePessoa(PESSOA P) {
	Serial.printf("Nome: %s, Idade: %d | Peso: %.2f | Altura: %.2f", P.nome, P.idade, P.peso, P.altura);
	Serial.println("\n-----------------------------------------------");
}

void setup() {
	Serial.begin(115200);
	
	PESSOA Pessoas[10];
	Pessoas[1].nome = "Pelé";
	Pessoas[1].idade = 82;
	Pessoas[1].peso = 73.0;
	Pessoas[1].altura = 1.73;
	
	Pessoas[2].nome = "Messi";
	Pessoas[2].idade = 38;
	Pessoas[2].peso = 67.0;
	Pessoas[2].altura = 1.70;
	
	PESSOA Pele = Pessoas[1];

	PESSOA Messi = Pessoas[2];
	Messi.idade++;

	PESSOA Ademir{.nome = "Ademir", .idade = 83, .peso = 75.0, .altura = 1.80};

	imprimePessoa(Pele);
	imprimePessoa(Pessoas[2]);
	imprimePessoa(Messi);
	imprimePessoa(Ademir);
}

void loop() {
	// Nada
}