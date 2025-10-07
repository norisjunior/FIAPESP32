/* ESP32 DHT22 */

#include <DHT.h>

// =========== NAMESPACE SENSOR ===========
namespace Sensor {
  const uint8_t DHT_PIN   = 19;
  const uint8_t DHT_MODEL = DHT22;
  DHT dht(DHT_PIN, DHT_MODEL);

  void init() { dht.begin(); }

  float readTemp()    { return dht.readTemperature(); }
  float readHumidity() { return dht.readHumidity();  }
}

// =========== NAMESPACE LED ===========
namespace LED {
  const uint8_t PIN = 26;

  void init() { pinMode(PIN, OUTPUT); }
  void on()   { digitalWrite(PIN, HIGH); }
  void off()  { digitalWrite(PIN, LOW);  }
}

// =========== SETUP & LOOP ===========
void setup() {
  Serial.begin(115200);
  LED::init();
  Sensor::init();
}

void loop() {
  float temp = Sensor::readTemp();
  Serial.printf("Temperatura: %.2f °C\n", temp);
  Serial.println("");

  // Exemplo de alias para funções do LED
  namespace L = LED;
  (temp > 30) ? L::on() : L::off();

  delay(2000);
}
