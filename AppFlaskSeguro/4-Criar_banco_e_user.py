# sudo apt install sqlite3

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