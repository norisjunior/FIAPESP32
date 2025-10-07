/* ESP32 namespace */

#include "meuPrintExterno.hpp"
using namespace MeuPrintExterno;

void MeuPrintNome(String nome) {
	Serial.println("\n-#-#-#- Função Impressão de Nome -#-#-#-");
	Serial.println(nome);
}

namespace MeuPrint {
	void imprimeNome(String nome) {
		Serial.println("\n-#-#-#- Namespace Impressão de Nome -#-#-#-");
		Serial.println(nome);
	}
}

void setup() {
    Serial.begin(115200);

	String meuNome = "Noris";

	delay(2000);
	// Impressão direta no Monitor Serial
	Serial.println(meuNome);

	delay(2000);
	// Impressão no Monitor Serial via função "MeuPrintNome"
	MeuPrintNome(meuNome);

	delay(2000);
	// Impressão no Monitor Serial via namespace "MeuPrint"
	MeuPrint::imprimeNome(meuNome);

	delay(2000);
	// Impressão no Monitor Serial via namespace em arquivo .hpp "MeuPrintExterno"
	//MeuPrintExterno::imprimeNome(meuNome);

	delay(2000);
	// Impressão no Monitor Serial via namespace em arquivo .hpp "MeuPrintExterno"
	imprimeNome(meuNome);
}

void loop() {
	// Nada
}

