# Roteiro - Proteção de credenciais com `.env` e variáveis de ambiente no Linux

Este roteiro mostra primeiro o caminho menos seguro com `.env` e depois uma forma mais segura, usando variáveis de ambiente no Linux / Raspberry Pi.

---

## Objetivo

Observar que:

* deixar segredo dentro do código é errado;
* usar `.env` já melhora a organização, mas continua sendo um arquivo texto sensível;
* o mais adequado é manter os segredos fora do código e fora do repositório;
* no Linux / Raspberry Pi, isso pode ser feito com variáveis de ambiente e arquivo externo com permissão restrita;
* senha de usuário da aplicação deve ficar no banco com hash;
* segredos da aplicação devem ficar fora do código.

---

## Parte 1 - Forma menos segura usando `.env`

### 1. Ativar o ambiente virtual

```bash
source AppEnv/bin/activate
```

---

### 2. Instalar biblioteca para ler `.env`

```bash
python3 -m pip install python-dotenv
```

---

### 3. Criar o arquivo `.env`

Conteúdo do arquivo `.env`:

```env
FLASK_SECRET_KEY=minha_chave_super_secreta_123
TEST_API_KEY=abc123-chave-api-teste
APP_DB_PATH=usuarios.db
ADMIN_USER=admin
ADMIN_PASSWORD=123456
```

---

### 4. Criar o `.gitignore`

Conteúdo do `.gitignore`:

```gitignore
.env
__pycache__/
*.pyc
AppEnv/
creds/
```

---

### 5. Criar um script simples para testar o `.env`

Conteúdo do `teste_env.py`:

```python
import os
from dotenv import load_dotenv

load_dotenv()

print("FLASK_SECRET_KEY:", os.getenv("FLASK_SECRET_KEY"))
print("TEST_API_KEY:", os.getenv("TEST_API_KEY"))
print("APP_DB_PATH:", os.getenv("APP_DB_PATH"))
```

Executar:

```bash
python3 teste_env.py
```

### 6. Criar uma aplicação Flask simples usando `.env`

Conteúdo do `app_env.py`:

```python
from flask import Flask, request, redirect, session
import os
from dotenv import load_dotenv

load_dotenv()

app = Flask(__name__)
app.secret_key = os.getenv("FLASK_SECRET_KEY")

ADMIN_USER = os.getenv("ADMIN_USER")
ADMIN_PASSWORD = os.getenv("ADMIN_PASSWORD")
TEST_API_KEY = os.getenv("TEST_API_KEY")
APP_DB_PATH = os.getenv("APP_DB_PATH")


@app.route("/")
def inicio():
    return """
    <h1>Totem FIAP</h1>
    <p>Área pública</p>
    <a href='/login'>Login</a>
    """


@app.route("/login", methods=["GET", "POST"])
def login():
    erro = ""

    if request.method == "POST":
        username = request.form.get("username", "")
        senha = request.form.get("senha", "")

        if username == ADMIN_USER and senha == ADMIN_PASSWORD:
            session["logado"] = True
            session["username"] = username
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
    <p>APP_DB_PATH carregado: {APP_DB_PATH}</p>
    <p>TEST_API_KEY carregada: {TEST_API_KEY}</p>
    <a href='/logout'>Sair</a>
    """


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/login")


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=False)
```

Executar:

```bash
python3 app_env.py
```

---

## Comparado à aplicação anterior

### O que melhorou

* o segredo saiu do código;
* a aplicação lê as credenciais do `.env`;
* isso evita hardcode dentro do `.py`.

### O que continua problemático

* o `.env` continua sendo um arquivo texto;
* se ele for para o GitHub, vazou;
* se outra pessoa tiver acesso ao arquivo, consegue ver tudo.

---

## Parte 2 - Forma mais segura

### 1. Criar pasta externa de configuração

```bash
mkdir -p creds
```

---

### 2. Criar arquivo de ambiente fora do projeto

Conteúdo do arquivo `creds/creds.env`:

```env
FLASK_SECRET_KEY=chave-forte-gerada-no-linux
TEST_API_KEY=api-key-externa-teste
APP_DB_PATH=usuarios.db
```

> Aqui, propositalmente, não vamos guardar a senha do usuário admin. A senha do admin deve ficar no banco com hash.

---

### 3. Carregar as variáveis no shell

```bash
set -a
source creds/creds.env
set +a
```

---

### 4. Criar um script simples para testar as variáveis do Linux

Conteúdo do `teste_linux_env.py`:

```python
import os

print("FLASK_SECRET_KEY:", os.environ.get("FLASK_SECRET_KEY"))
print("TEST_API_KEY:", os.environ.get("TEST_API_KEY"))
print("APP_DB_PATH:", os.environ.get("APP_DB_PATH"))
```

Executar:

```bash
python3 teste_linux_env.py
```

### 5. Criar uma aplicação Flask simples lendo apenas `os.environ`

Conteúdo do `app_linux_env.py`:

```python
from flask import Flask
import os

app = Flask(__name__)
app.secret_key = os.environ.get("FLASK_SECRET_KEY")

TEST_API_KEY = os.environ.get("TEST_API_KEY")
APP_DB_PATH = os.environ.get("APP_DB_PATH")


@app.route("/")
def inicio():
    return f"""
    <h1>Totem FIAP</h1>
    <p>Secret key carregada por variável de ambiente do Linux.</p>
    <p>Banco configurado em: {APP_DB_PATH}</p>
    <p>API Key carregada: {TEST_API_KEY}</p>
    """


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=False)
```

Executar:

```bash
python3 app_linux_env.py
```

---

### O que melhorou

* os segredos não estão no código;
* os segredos não estão no repositório;
* o arquivo está fora do projeto;
* o arquivo tem permissão restrita;
* a aplicação lê tudo via variável de ambiente.

### O que ficar em mente

> Variável de ambiente é melhor porque a aplicação lê o segredo sem que ele precise estar dentro do código-fonte. Mas alguém ainda precisa guardar esse segredo em algum lugar. Por isso existe o arquivo externo protegido, ou um cofre de segredos em ambientes maiores.

---

## Parte 3 - Segurança web ampliada

### Regra correta para o projeto

#### Senha do usuário admin

* deve ficar no banco SQLite com hash;
* não deve ficar hardcoded no código;
* não deve ser a solução final em `.env`.

#### Segredos da aplicação

Exemplos:

* `FLASK_SECRET_KEY`
* chaves de API
* caminho do banco
* tokens de integração

Devem ficar:

* fora do código;
* fora do repositório;
* preferencialmente em variáveis de ambiente do Linux / Raspberry Pi.

---

## Parte 4 - Onde armazenar essas chaves?

As chaves sempre precisam existir em algum lugar.

### Exemplos de onde podem ficar

* arquivo externo protegido no Linux;
* variáveis definidas pelo shell;
* cofre de segredos;
* gerenciador de senhas institucional.

