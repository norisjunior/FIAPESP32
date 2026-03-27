from flask import Flask, redirect
from gpiozero import LED, MotionSensor
import board, adafruit_dht

app = Flask(__name__)

led = LED(26)
pir = MotionSensor(18)
dht = adafruit_dht.DHT22(board.D2)

@app.route("/")
def pagina():
    try:
        temp = dht.temperature
        umid = dht.humidity
    except:
        temp = umid = 0

    presenca = pir.motion_detected
    if presenca:
        led.on()
    else:
        led.off()

    estado_led = "Ligado" if led.is_lit else "Desligado"
    estado_pir = "Detectada" if presenca else "Não detectada"


    return f"""
<html>
<head>
    <title>Monitor Raspberry</title>
    <script>setTimeout(() => location.reload(), 1000);</script>
</head>
<body>
    <h1>Monitor Raspberry Pi</h1>
    <p>Temperatura: {temp} °C</p>
    <p>Umidade: {umid} %</p>
    <p>Presenca: {estado_pir}</p>
    <p>LED: {estado_led}</p>
    <a href="/led_on" ><button>Ligar</button></a>
    <a href="/led_off"><button>Desligar</button></a>
</body>
</html>
"""

@app.route("/led_on")
def ligar_led():
    led.on()
    return redirect("/")

@app.route("/led_off")
def desligar_led():
    led.off()
    return redirect("/")

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
