#define BOTAO 16
#define LEDRED   25
#define LEDBLUE  26

uint16_t i = 0;

bool acendeuLED = false;
bool desligouLED = false;

void setup() {
    Serial.begin(9600);

    pinMode(BOTAO, INPUT_PULLUP); //Inicia como HIGH
    pinMode(LEDRED, OUTPUT);
    pinMode(LEDBLUE, OUTPUT);
}

void loop() {
    //Exercício 1:
    //Crie um programa que avalie se a temperatura está abaixo de 35 graus.
    //Caso esteja igual ou superior a 35 graus emita um alerta: "Temperatura Alta!"

    float temp1 = 35.0;

    if (temp1 >= 35) {
        Serial.println("Temperatura Alta!");
    }


    //Exercício 2:
    //Crie um programa que avalie a temperatura e umidade
    //O sistema deve:
    //Emitir a mensagem "Condições adequadas, caso a temperatura esteja menor que 35 e a
    //umidade maior que 30 e menor que 80". Caso a temperatura esteja menor que 35 e a umidade
    //não esteja entre 30 e 80, informar: umidade inadequada
    //Caso contrário, deve ser exibida a mensagem: "Condições inadequadas"
    
    float temp2 = 40.0;
    float umid2 = 90.0;
    
    if (temp2 < 35) {
        if (umid2 > 30 && umid2 < 80) {
            Serial.println("Condições adequadas");
        } else {
            Serial.println("Umidade inadequada");
        }
    } else {
        Serial.println("Condições inadequadas");
    }



    //Exercício 3:
    //Crie um programa que acenda um LED vermelho caso a temperatura ultrapasse 40 graus.
    //Outra função do programa está relacionada à umidade:
    //se a umidade estiver acima de 80, acenda um LED azul
    //Depois de 2 segundos apague o LED e deixe o programa prosseguir com novas medições

    float temp3 = 45.0;
    float umid3 = 90.0;

    if (temp3 > 40) {
        digitalWrite(LEDRED, HIGH);
    } else {
        digitalWrite(LEDRED, LOW);
    }

    if (umid3 > 80) {
        digitalWrite(LEDBLUE, HIGH);
    } else {
        digitalWrite(LEDBLUE, LOW);
    }

    delay(2000);
    digitalWrite(LEDRED, LOW);
    digitalWrite(LEDBLUE, LOW);


    //Exercício 4:
    //Crie um programa que verifica se a temperatura está acima de 30 graus e, caso esteja,
    //deve acenter o LED vermelho uma única vez e não alterar mais o estado do LED
    //Insira um botão que apague o LED e mantenha-o apagado depois de acionado (não é necessário
    //alternar entre LED aceso e apagado, apenas apague-o)
    
    bool botaoPressionado4;
    bool estadoLED4 = 0;
    float temp4 = 40.0;

    if (temp4 > 30 && !acendeuLED) {
        digitalWrite(LEDRED, HIGH);
        Serial.println("Temperatura acima de 30 graus, LED aceso");
        acendeuLED = true;
    }

    botaoPressionado4 = digitalRead(BOTAO);

    if ( (botaoPressionado4 == LOW) && (!desligouLED) ) { //botão pressionado
        digitalWrite(LEDRED, LOW);
        Serial.println("Botão acionado, LED apagado");
        desligouLED = true;
    }
    



    //Exercício 5:
    //Este programa requer 2 LEDs e um BOTÃO
    //Crie um programa que acenda o LED AZUL caso a umidade esteja abaixo de 20.
    //O programa deve acender o LED VERMELHO se:
    // a temperatura estiver acima de 30,
    // a umidade estiver abaixo de 10,
    // o botão for mantido pressionado clicado.
    // Caso o botão não seja clicado, o LED deverá permanecer desligado.

    float temp5 = 50.0;
    float umid5 = 5.0;
    bool botaoPressionado5;

    botaoPressionado5 = digitalRead(BOTAO);

    if (umid5 < 20) {
        digitalWrite(LEDBLUE, HIGH);
    }

    if ( (temp5 > 30) && (umid5 < 10) && (botaoPressionado5 == LOW) ) {
        //temp > 30, umid < 10 e botão pressionado
        digitalWrite(LEDRED, HIGH);
    } else {
        digitalWrite(LEDRED, LOW);
    }


    delay(200);


    // Exercício 6
    // Crie um programa que:
    // Avalie se a temperatura for maior ou igual a 37 graus, e, se for, acenda o LED vermelho, caso contrário, deixe o LED apagado. Utilize o operador ternário para implementar essa lógica.

    float temp6 = 30.0;

    (temp6 > 37) ? digitalWrite(LEDRED, HIGH) : digitalWrite(LEDRED, LOW);
}

