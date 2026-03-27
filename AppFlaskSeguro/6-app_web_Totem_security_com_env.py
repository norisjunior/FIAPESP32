from flask import Flask, request, redirect, session
import sqlite3
import os
from dotenv import load_dotenv
from werkzeug.security import check_password_hash

load_dotenv(dotenv_path="creds/creds.env")

FLASK_SECRET_KEY = os.getenv("FLASK_SECRET_KEY")
APP_DB_PATH = os.getenv("APP_DB_PATH")
TEST_API_KEY = os.getenv("TEST_API_KEY")

if not FLASK_SECRET_KEY:
    raise RuntimeError("Erro: FLASK_SECRET_KEY não definida no arquivo .env")

if not APP_DB_PATH:
    raise RuntimeError("Erro: APP_DB_PATH não definida no arquivo .env")

if not TEST_API_KEY:
    raise RuntimeError("Erro: TEST_API_KEY não definida no arquivo .env")

app = Flask(__name__)
app.secret_key = FLASK_SECRET_KEY

# Estado dummy do LED
led_ligado = False


def buscar_usuario(username):
    conn = sqlite3.connect(APP_DB_PATH)
    cursor = conn.cursor()
    cursor.execute("SELECT id, username, password_hash FROM usuarios WHERE username = ?", (username,))
    usuario = cursor.fetchone()
    conn.close()
    return usuario


@app.route("/")
def pagina_publica():
    temperatura = 24.5
    umidade = 58.0
    presenca = False

    estado_led = "Ligado" if led_ligado else "Desligado"
    estado_pir = "Detectada" if presenca else "Não detectada"

    return f"""
    <title>Totem Raspberry Pi</title>

    <h1>Monitor Raspberry Pi</h1>

    <h2>Ambiente</h2>
    <p>Temperatura: {temperatura} °C</p>
    <p>Umidade: {umidade} %</p>
    <p>Presença: {estado_pir}</p>
    <p>LED: {estado_led}</p>

    <hr>

    <h2>Acesso</h2>
    <p>Área administrativa protegida</p>
    <a href="/login">Entrar</a>
    """


@app.route("/login", methods=["GET", "POST"])
def login():
    erro = ""

    if request.method == "POST":
        username = request.form.get("username", "")
        senha = request.form.get("senha", "")

        usuario = buscar_usuario(username)

        if usuario and check_password_hash(usuario[2], senha):
            session["logado"] = True
            session["username"] = usuario[1]
            return redirect("/admin")
        else:
            erro = "Usuário ou senha inválidos."

    return f"""
    <title>Login</title>

    <h1>Login</h1>

    <form method="POST">
        <p><input type="text" name="username" placeholder="Usuário" required></p>
        <p><input type="password" name="senha" placeholder="Senha" required></p>
        <p><button type="submit">Entrar</button></p>
    </form>

    <p style="color:red;">{erro}</p>

    <p><a href="/">Voltar</a></p>
    """


@app.route("/admin")
def admin():
    if not session.get("logado"):
        return redirect("/login")

    estado_led = "Ligado" if led_ligado else "Desligado"

    return f"""
    <title>Administração</title>

    <h1>Área Administrativa</h1>

    <p>Usuário logado: <strong>{session.get("username")}</strong></p>
    <p>Status do LED: <strong>{estado_led}</strong></p>
    <p>Banco configurado: <strong>{APP_DB_PATH}</strong></p>
    <p>API Key de teste: <strong>{TEST_API_KEY}</strong></p>

    <form action="/led_on" method="POST">
        <button type="submit">Ligar LED</button>
    </form>

    <br>

    <form action="/led_off" method="POST">
        <button type="submit">Desligar LED</button>
    </form>

    <p><a href="/logout">Sair</a></p>
    """


@app.route("/led_on", methods=["POST"])
def ligar_led():
    global led_ligado

    if not session.get("logado"):
        return redirect("/login")

    led_ligado = True
    return redirect("/admin")


@app.route("/led_off", methods=["POST"])
def desligar_led():
    global led_ligado

    if not session.get("logado"):
        return redirect("/login")

    led_ligado = False
    return redirect("/admin")


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/login")


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=False)