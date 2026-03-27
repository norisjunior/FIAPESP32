from flask import Flask, redirect # pyright: ignore[reportMissingImports]
from gpiozero import LED, MotionSensor # type: ignore
import board # type: ignore
import adafruit_dht # type: ignore

app = Flask(__name__)

# LED no GPIO26
led = LED(26)

# PIR no GPIO18
pir = MotionSensor(18)

# DHT11 no GPIO2
dht = adafruit_dht.DHT22(board.D2)

@app.route("/")
def pagina():

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

    return f"""
    <html>

        <head>
            <title>Monitor Raspberry</title>

            <!-- Atualiza a página a cada 1 segundo -->
            <script>setTimeout(() => location.reload(), 1000);</script>

            <style>
                body {{ font-family: sans-serif; text-align: center; padding: 40px; background: #f0f0f0; }}
                h1 {{ color: #333; }}
                .card {{ background: white; border-radius: 12px; padding: 20px; display: inline-block; margin: 20px; min-width: 250px; box-shadow: 0 2px 8px rgba(0,0,0,0.1); }}
                button {{ padding: 12px 30px; font-size: 16px; border: none; border-radius: 8px; cursor: pointer; margin: 8px; }}
                .btn-on  {{ background: #4CAF50; color: white; }}
                .btn-off {{ background: #f44336; color: white; }}
            </style>

        </head>

        <body>

            <h1>Monitor Raspberry Pi</h1>

            <div class="card">
                <h2>Ambiente</h2>
                <p>Temperatura: {temperatura} °C</p>
                <p>Umidade: {umidade} %</p>
                <p>Presença: {estado_pir}</p>
            </div>

            <div class="card">
                <h2>LED</h2>
                <p>Status: <strong>{estado_led}</strong></p>
                <a href="/led_on" ><button class="btn-on" >Ligar</button></a>
                <a href="/led_off"><button class="btn-off">Desligar</button></a>
            </div>

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