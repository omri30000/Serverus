from flask import Flask
from flask import render_template
from flask import request


app = Flask(__name__)


@app.route("/")  # if we use the domain only, we'll get here
def home_page():
    return render_template("index.html")


@app.route("/login", methods=["POST", "GET"])
def login_page():
    if request.method == "POST":
        user = request.form['username']

    return render_template("login.html")


@app.route("/register")
def register_page():
    return render_template("register.html")


@app.route("/dashboard")
def dashboard_page():
    return render_template("dashboard.html")


if __name__ == '__main__':
    app.run(debug=True)
