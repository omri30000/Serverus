from flask import Flask
from flask import render_template

app = Flask(__name__)

@app.route("/")  # if we use the domain only, we'll get here
def home():
    return render_template("index.html")

@app.route("/login")
def login_page():
    return render_template("login.html")

@app.route("/register")
def register_page():
    return "register page"


if __name__ == '__main__':
    app.run(debug=True)