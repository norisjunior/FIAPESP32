from gpiozero import LED, MotionSensor
import board
import adafruit_dht
import time

# LED no GPIO26
led = LED(26)

# PIR no GPIO18
pir = MotionSensor(18)

# DHT11 no GPIO2
dht = adafruit_dht.DHT22(board.D2)

while True:

    # lê temperatura e umidade
    try:
        temperatura = dht.temperature
        umidade = dht.humidity
    except:
        temperatura = 0
        umidade = 0

    # lê presença
    presenca = pir.motion_detected

    # lógica do LED
    if presenca:
        led.on()
    else:
        led.off()

    estado_led = "Ligado" if led.is_lit else "Desligado"
    estado_pir = "Detectada" if presenca else "Não detectada"

    print(f"Temperatura: {temperatura} °C")
    print(f"Umidade: {umidade} %")
    print(f"Presença: {estado_pir}")
    print(f"LED: {estado_led}")
    print("---")

    time.sleep(1)