from flask import Flask
from flask import render_template
from flask import request
from flask import redirect, url_for
from flask import session

import DatabaseManager
import config


app = Flask(__name__)
app.secret_key = "secretKey"
db_manager = DatabaseManager.DatabaseManager(db_file_name=config.DB_FILE_NAME)


def main():
    app.run(debug=True)  # , port=80, host="0.0.0.0")


@app.route("/")  # if we use the domain only, we'll get here
def home_page():
    return render_template("index.html")


@app.route("/login", methods=["POST", "GET"])
def login_page():
    if "userID" in session:  # the user is connected
        return redirect(url_for("dashboard_page"))
    else:
        if request.method == "POST":
            # find user in data base and add to session:
            user_name = request.form["usernameName"]
            password = request.form["passwordName"]
            if db_manager.check_login(user_name, password):
                session["userID"] = db_manager.get_user_id(user_name)
                return redirect(url_for("dashboard_page"))
            else:  
                # todo: throw exception and raise message
                return render_template("login.html")

        else:  
            # GET request
            return render_template("login.html")


@app.route("/register", methods=["POST", "GET"])
def register_page():
    if "userID" in session:  # the user is connected
        return redirect(url_for("dashboard_page"))

    if request.method == "POST":
        user_name = request.form["usernameName"]
        password = request.form["passwordName"]
        email = request.form["emailName"]
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


@app.route("/rules")
def rule_management_page():
    if "userID" in session:  # the user is connected
        data = db_manager.get_all_rules()
        return render_template("rules.html", content=data, user_id=session["userID"])
    else:
        return redirect(url_for("login_page"))


@app.route("/logout")
def logout():
    session.pop("userID", None)
    return redirect(url_for("login_page"))


if __name__ == '__main__':
    main()
