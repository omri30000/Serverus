from flask import Flask
from flask import render_template
from flask import request
from flask import redirect, url_for
from flask import session

import DatabaseManager

app = Flask(__name__)
app.secret_key = "secretKey"
db_manager = DatabaseManager.DatabaseManager(db_file_name="/home/ofir/Music/general_db.sqlite")


def main():
    print(db_manager)
    app.run(debug=True)


@app.route("/")  # if we use the domain only, we'll get here
def home_page():
    return render_template("index.html")


@app.route("/login", methods=["POST", "GET"])
def login_page():
    if "userID" in session:  # the user is connected
        return render_template("dashboard.html")
    else:
        if request.method == "POST":
            # todo: find user in data base and add to session
            return redirect(url_for("dashboard_page"))
        else:  # GET request
            return render_template("login.html")


@app.route("/register", methods=["POST", "GET"])
def register_page():
    if request.method == "POST":
        user_name = request.form["username"]
        password = request.form["password"]
        email = request.form["email"]
        print(user_name, password)
        session["userID"] = db_manager.insert_user(user_name, password)
        return redirect(url_for("dashboard_page"))
    else:  # GET request
        return render_template("register.html")


@app.route("/dashboard")
def dashboard_page():
    if "userID" in session:  # the user is connected
        return render_template("dashboard.html")
    else:
        return redirect(url_for("login_page"))


@app.route("/logout")
def logout():
    session.pop("userID", None)
    return redirect(url_for("login_page"))


if __name__ == '__main__':
    main()
