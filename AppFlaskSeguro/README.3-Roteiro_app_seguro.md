# Roteiro - Login Flask + SQLite no Raspberry Pi

Estruturando aplicação Python/Flask web com autenticação e segurança no login.

---

## 1. Preparar o ambiente

> Ao seguir o README.1, pip, venv e Flask já estão instalados. Instale o sqlite3 e ative o venv:

```bash
sudo apt install sqlite3
cd ~/appTotem
source AppEnv/bin/activate
```

---

## 2. Criar uma pasta para o projeto

```bash
mkdir totem_login
cd totem_login
```

---

## 3. Criar o script de inicialização do banco

Criar o arquivo `init_db.py`:

```python
import sqlite3
from werkzeug.security import generate_password_hash

conn = sqlite3.connect("usuarios.db")
cursor = conn.cursor()

cursor.execute("""
CREATE TABLE IF NOT EXISTS usuarios (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password_hash TEXT NOT NULL
)
""")

usuario = "admin"
senha = "123456"
hash_senha = generate_password_hash(senha)

cursor.execute("SELECT * FROM usuarios WHERE username = ?", (usuario,))
existe = cursor.fetchone()

if not existe:
    cursor.execute(
        "INSERT INTO usuarios (username, password_hash) VALUES (?, ?)",
        (usuario, hash_senha)
    )
    print("Usuário admin criado com sucesso.")
else:
    print("Usuário admin já existe.")

conn.commit()
conn.close()
```

---

## 4. Executar a criação do banco

```bash
python3 init_db.py
```

## 5. Conferir o banco SQLite

Instalar sqlite3:
```bash
sudo apt install sqlite3
```


Abrir o banco:

```bash
sqlite3 usuarios.db
```

Listar tabelas:

```sql
.tables
```

Consultar usuários:

```sql
SELECT id, username, password_hash FROM usuarios;
```

Sair:

```sql
.quit
```

---

## 6. Criar a aplicação Flask simples

Criar o arquivo `app_inicial.py`:

```python
from flask import Flask, request, redirect, session
import sqlite3
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = "chave-temporaria-aula"


def buscar_usuario(username):
    conn = sqlite3.connect("usuarios.db")
    cursor = conn.cursor()
    cursor.execute(
        "SELECT username, password_hash FROM usuarios WHERE username = ?",
        (username,)
    )
    usuario = cursor.fetchone()
    conn.close()
    return usuario


@app.route("/")
def inicio():
    if session.get("logado"):
        return redirect("/admin")

    return """
    <h1>Totem FIAP</h1>
    <h2>Área pública</h2>
    <p> Temperatura: 99 </p>
    <p> Umidade: 99 </p>
    <p> Presença: Detectada </p>
    <p></p>
    <a href='/login'>Ir para login</a>
    """


@app.route("/login", methods=["GET", "POST"])
def login():
    erro = ""

    if request.method == "POST":
        username = request.form.get("username", "")
        senha = request.form.get("senha", "")

        usuario = buscar_usuario(username)

        if usuario and check_password_hash(usuario[1], senha):
            session["logado"] = True
            session["username"] = usuario[0]
            return redirect("/admin")
        else:
            erro = "Usuário ou senha inválidos"

    return f"""
    <h1>Login</h1>
    <form method='POST'>
        <input type='text' name='username' placeholder='Usuário'><br><br>
        <input type='password' name='senha' placeholder='Senha'><br><br>
        <button type='submit'>Entrar</button>
    </form>
    <p style='color:red;'>{erro}</p>
    <a href='/'>Voltar</a>
    """


@app.route("/admin")
def admin():
    if not session.get("logado"):
        return redirect("/login")

    return f"""
    <h1>Área Administrativa</h1>
    <p>Usuário logado: {session.get('username')}</p>
    <a href='/logout'>Sair</a>
    """


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/login")


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=False)
```

---

## 7. Executar a aplicação

```bash
python3 app_inicial.py
```

## 8. Acessar pelo navegador

No navegador, abrir:

```text
http://IP_DO_RASPBERRY:5000
```

Exemplo:

```text
http://192.168.0.15:5000
```

---

## 9. Testes

### Teste 1 — Página inicial

* acessar `/`
* verificar que é a área pública
* clicar em login

### Teste 2 — Login correto

Usar:

* usuário: `admin`
* senha: `123456`

### Teste 3 — Área administrativa

* confirmar que a página `/admin` aparece apenas depois do login
* mostrar o nome do usuário autenticado

### Teste 4 — Proteção da rota

* tentar acessar `/admin` sem login
* verificar redirecionamento para `/login`

### Teste 5 — Logout

* clicar em sair
* tentar acessar `/admin` novamente
* verificar novo bloqueio

---

## Observações importantes

### Parte 1 — Banco de dados

* o usuário está salvo no SQLite
* a senha não está em texto claro
* o banco guarda `password_hash`

### Parte 2 — Login

* o formulário envia usuário e senha por `POST`
* o Flask consulta o banco
* a senha digitada é comparada com o hash

### Parte 3 — Sessão

* depois do login, o Flask grava `session["logado"] = True`
* a rota `/admin` só abre se a sessão existir
* no logout, a sessão é apagada
