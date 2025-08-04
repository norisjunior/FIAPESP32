#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define SCLPIN 19
#define SDAPIN 18
#define LED 14

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  // Inicializa comunicação I2C nos pinos padrão do ESP32 (SDA=18, SCL=19)
  Wire.begin(SDAPIN, SCLPIN);

  if (!mpu.begin()) {
    Serial.println("Erro: MPU6050 não encontrado. Verifique as conexões.");
    while (1) delay(10);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(1000);

  Serial.println("MPU6050 inicializado com sucesso!");
  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.println("---- Medições coletadas -----");
  Serial.println("Acelerometro: x: ");
  Serial.print(a.acceleration.x);
  Serial.print(", y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", z: ");
  Serial.print(a.acceleration.z);
  Serial.println("\n-----------------------------\n");

  
  delay(10);

  // Verifica se houve movimento forte em qualquer eixo
  if (abs(a.acceleration.x) > 2 || abs(a.acceleration.y) > 2 || abs(a.acceleration.z) > 2) {
    Serial.println("Movimento detectado!");
	digitalWrite(LED, HIGH);
  } else {
    Serial.println("Ambiente estável.");
	digitalWrite(LED, LOW);
  }

  delay(2000);
}
