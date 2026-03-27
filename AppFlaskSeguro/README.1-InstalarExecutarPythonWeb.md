# Aplicação usando Raspberry Pi + sensor PIR + sensor DHT + LED

LED -> pino 26
DHT -> pino 2
PIR -> pino 18

### 1. Preparação do Raspberry Pi

#### 1.1 Instalar sistema operacional no SD Card
- Instruções no site oficial: [Raspberry Pi - Instalador](https://www.raspberrypi.com/software/)

#### 1.2 Depois de instalado
- Atualizar:
```bash
sudo apt update
```

### 2. Preparação do ambiente python para desenvolvimento do app

#### 2.1 Instalar pip e venv
```bash
sudo apt install python3-pip python3-venv
```

#### 2.2 Criar diretório para hospedar a aplicação:
```bash
cd ~
mkdir appTotem
cd appTotem
```

#### 2.3 Criar ambiente python para desenvolvimento e deploy da aplicação
```bash
python3 -m venv AppEnv
source AppEnv/bin/activate
python3 -m pip install --upgrade pip
```

#### 2.4 Instalação das bibliotecas necessárias para DHT, PIR, LED e Flask
```bash
python3 -m pip install board gpiozero adafruit-blinka adafruit-circuitpython-dht flask
```

### 3. Executar a aplicação

```bash
python3 3-app_web_Totem_leitura_direta_HTMLpuro.py
```

Acesse pelo navegador: `http://<ip-do-raspberry>:5000`
