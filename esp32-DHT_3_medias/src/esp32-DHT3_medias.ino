/* DHT22
*/

#include <DHT.h>

#define DHTPIN 21
#define DHTMODEL DHT22

#define LEDRED 26

#define BOTAO 18

DHT dht(DHTPIN, DHTMODEL);

float temp, umid = 0;
float hic = 0;
float tempMedia, umidMedia, hicMedio = 0;

uint8_t contador = 0;

void setup() {
  //Código que será executado apenas uma vez
  Serial.begin(115200);
  dht.begin();
  pinMode(LEDRED, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);
}

void loop() {
  //Aguardar o pressionamento do botão para iniciar
  while (digitalRead(BOTAO) == HIGH) {
    //Nada, espera o botão, porque aí sai do while
  }
  
  //Código que será executado continuamente
  temp = dht.readTemperature();
  umid = dht.readHumidity();

  //Se as medições estão OK
  if ( isnan(temp) || isnan(umid) ) {
    Serial.println("Erro de leitura no sensor DHT 22! Reiniciando...");
    delay(2000);
    return;
  }

  hic = dht.computeHeatIndex(temp, umid, false);

  Serial.println("------------------------------------------------------------------------");
  Serial.printf("Temperatura id %d: %.2f. Umidade id %d: %.2f. IC id %d: %.2f.", contador, temp, contador, umid, contador, hic); Serial.println("");
  Serial.println("------------------------------------------------------------------------");

  if (hic > 20) {
    digitalWrite(LEDRED, HIGH);
    Serial.printf("\nÍndice de calor ALTO! Alerta! IC: %.2f\n", hic); Serial.println("");
  }

  contador++; 
  tempMedia = tempMedia + temp;
  umidMedia = umidMedia + umid;
  hicMedio = hicMedio + hic;

  if (contador == 3) {
    tempMedia = tempMedia / contador;
    umidMedia = umidMedia / contador;
    hicMedio = hicMedio / contador;
    Serial.printf("\nTemperatura média: %.2f. Umidade média: %.2f. IC médio: %.2f.", tempMedia, umidMedia, hicMedio); Serial.println("");
	contador = 0;
	tempMedia = 0;
	umidMedia = 0;
	hicMedio = 0;
  }

  delay(3000);
  Serial.println("Pressione o botão para realizar nova leitura.");
  digitalWrite(LEDRED, LOW);  
}
