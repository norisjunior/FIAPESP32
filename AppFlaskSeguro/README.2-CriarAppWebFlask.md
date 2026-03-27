# De terminal para web — Flask no Raspberry Pi

Evolução de `app_sensores_DHT_PIR.py` (imprime no terminal) para `app_web_Totem_leitura_direta_HTMLpuro.py` (exibe os dados no navegador via Flask).

---

## O que mudou

### 1. Trocar o loop `while True` do arquivo `1-app_sensores_DHT_PIR.py` por rotas Flask

**Antes** — loop infinito com `print` e `time.sleep`:
```python
while True:
    temperatura = dht.temperature
    presenca = pir.motion_detected
    print(f"Temperatura: {temperatura} °C")
    time.sleep(1)
```

**Depois** — função de rota que responde a cada requisição HTTP:
```python
from flask import Flask, redirect
app = Flask(__name__)

@app.route("/")
def pagina():
    temp = dht.temperature
    presenca = pir.motion_detected
    return f"<p>Temperatura: {temp} °C</p>"
```

### 2. A página HTML é retornada como string f-string

Os valores dos sensores são embutidos diretamente no HTML:
```python
return f"""
<html>
<body>
    <p>Temperatura: {temp} °C</p>
    <p>Umidade: {umid} %</p>
    <p>Presença: {estado_pir}</p>
</body>
</html>
"""
```

### 3. Auto-refresh com JavaScript

Uma linha no `<head>` recarrega a página a cada 1 segundo, simulando o comportamento do loop:
```html
<script>setTimeout(() => location.reload(), 1000);</script>
```

### 4. Rotas para controlar o LED pelo navegador

Botões no HTML chamam rotas que ligam/desligam o LED e redirecionam de volta à página:
```python
@app.route("/led_on")
def ligar_led():
    led.on()
    return redirect("/")
```

### 5. Iniciar o servidor

```python
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
```

```bash
python3 2-app_web_Totem_leitura_direta_HTMLpuro.py
```

Acesse no navegador: `http://<IP-do-Raspberry>:5000`

---

## Rotas disponíveis

| Rota       | O que faz                              |
|------------|----------------------------------------|
| `/`        | Exibe temperatura, umidade, presença e LED |
| `/led_on`  | Liga o LED e volta para `/`            |
| `/led_off` | Desliga o LED e volta para `/`         |
