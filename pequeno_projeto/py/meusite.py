from flask import Flask, render_template, request

app = Flask(__name__)

usuarios = {}

@app.route('/')
def index():
    return render_template("index.html")

@app.route('/register', methods=["POST"])
def register():
    nome = request.form.get("nome")
    senha = request.form.get("senha")
    usuarios[nome] = senha
    return render_template("register.html")

@app.route('/usuarios')
def listadeusuarios():
    return render_template("usuarios.html", usuarios=usuarios)