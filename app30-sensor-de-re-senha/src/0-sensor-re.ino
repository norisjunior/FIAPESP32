// Sensor de ré

#include "EasyBuzzer.h"
 
#define trigPin 23      // Pino GPIO conectado ao Trig do HC-SR04
#define echoPin 22      // Pino GPIO conectado ao Echo do HC-SR04
#define pinLED 17       // Pino GPIO conectado ao resistor de LED
#define pinBuzzer 19    //Pino GPIO do buzzer
int16_t freqBeep = 800;
 
void setup() {
    Serial.begin(115200);         // Inicializa a comunicação serial
    pinMode(trigPin, OUTPUT);   // Define o pino Trig como saída
    pinMode(echoPin, INPUT);    // Define o pino Echo como entrada
    pinMode(pinLED, OUTPUT);    // Define o pino do LED como saída para acender o LED
    EasyBuzzer.setPin(pinBuzzer);
}

void loop() {
    long duration;
    int distance;

    // Coletar distância
    // Envia um pulso de 10us para o Trig
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Calcula o tempo de duração do pulso de retorno no Echo
    duration = pulseIn(echoPin, HIGH);
    // Calcula a distância em centímetros
    distance = duration * 0.034 / 2;
    // Exibe a distância no Monitor Serial
    Serial.print("Distância: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    // Aciona buzzer dependendo da distância
    if(distance >= 100) {
        EasyBuzzer.beep(freqBeep);
        delay(300);
        EasyBuzzer.beep(0);
        delay(300);
    }
    else if(distance >= 50 && distance < 100) {
        EasyBuzzer.beep(freqBeep);
        delay(150);
        EasyBuzzer.beep(0);
        delay(150);
    }
    else if(distance >= 40 && distance < 49) {
        EasyBuzzer.beep(freqBeep);
        delay(100);
        EasyBuzzer.beep(0);
        delay(100);
    }
    else {
        EasyBuzzer.beep(freqBeep);
        delay(10);
        EasyBuzzer.beep(0);
        delay(10);
    }
    EasyBuzzer.update();
}