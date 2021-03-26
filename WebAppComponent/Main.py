import time

from flask import Flask
from flask import render_template
from flask import request
from flask import redirect, url_for
from flask import session
from flask import flash
from flask import send_from_directory
from flask import send_file
from flask import Response

import zipfile
import json
import shutil
import os

import DatabaseManager
import config
import Utils
LOC = "/media/ofir/TOSHIBA EXT/magshimim/Year3/Magshimim/idps-20-21/WebAppComponent"
ZIP_FILE ="Example/base.zip"

app = Flask(__name__)
app.secret_key = "secretKey"
db_manager = DatabaseManager.DatabaseManager(db_file_name=config.DB_FILE_NAME)


def main():
    app.run(debug=True, port=config.WEB_LISTEN_PORT, host=config.HOST)


@app.route("/")  # if we use the domain only, we'll get here
def home_page():
    if "userID" in session:
        base_page = "userBase.html"
    else:
        base_page = "guestBase.html"
    return render_template("index.html", base=base_page)


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
                flash("Invalid Credentials")
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
        try:
            session["userID"] = db_manager.insert_user(user_name, password)
        except Exception as e:
            flash('Invalid Register')
            return render_template("register.html")

        return redirect(url_for("dashboard_page"))

    else:  # GET request
        return render_template("register.html")


@app.route("/dashboard")
def dashboard_page():
    if "userID" in session:  # the user is connected
        # request method is always GET
        return render_template("dashboard.html", content=db_manager.get_all_events(session["userID"]),
                               anomalies_amount=db_manager.get_anomalies(session["userID"]),
                               sort_by_level=order_by_third)
    else:
        return redirect(url_for("login_page"))


@app.route("/rule")
def rule_management_page():
    if "userID" in session:  # the user is connected
        return render_template("rules.html", content=db_manager.get_all_rules(session["userID"]))
    else:
        return redirect(url_for("login_page"))


@app.route("/addRule", methods=["POST", "GET"])
def add_rule_page():
    if "userID" in session:  # the user is connected
        if request.method == "POST":
            # get numbers and avoid pre-zeros (0003 -> 3)
            first = str(int(request.form["rule data1"]))
            second = str(int(request.form["rule data2"]))
            third = str(int(request.form["rule data3"]))
            fourth = str(int(request.form["rule data4"]))

            rule = first + '.' + second + '.' + third + '.' + fourth

            if Utils.validate_ip_address(rule):
                db_manager.add_rule(session["userID"], rule)
            return redirect(url_for("rule_management_page"))
        else:  # GET request
            return render_template("addRule.html")
    else:
        return redirect(url_for("login_page"))


@app.route("/removeRule/<data>")
def remove_rule(data):
    if "userID" not in session:  # user is not connected
        return redirect(url_for("login_page"))

    db_manager.remove_rule_by_data(session["userID"], data)
    return redirect(url_for("rule_management_page"))

@app.route("/download")
def download():

    def generate(file):
        for part in file:
            yield part


    if "userID" not in session:  # user is not connected
        return redirect(url_for("login_page"))
    product_id = db_manager.get_product_id(session["userID"])
    
    make_config_file(product_id)
    config_tmp = "Example/Configuration{}_tmp.json".format(product_id)

    new_zip = "Example/{}.zip".format(product_id)
    shutil.copy(ZIP_FILE,new_zip)
    
    with zipfile.ZipFile(new_zip, "a") as zipped:
        zipped.write(config_tmp,"Configuration.json",zipfile.ZIP_DEFLATED)
    os.remove(config_tmp)
    
    with open(new_zip,'rb') as zip_file:
        data = zip_file.read()

    return Response(data,mimetype = "application/zip")
     

    """try:
        return send_file(LOC +'/'+ new_zip)
    except Exception as e:
        print(e)
        raise e
    #return send_from_directory(directory=, filename=new_zip.split("/")[1],as_attachment=True)
    """


@app.route("/logout")
def logout():
    session.pop("userID", None)
    return redirect(url_for("login_page"))




def order_by_third(arr, rev=False):
    """
    The function will sort a list of lists by the inner list's third element
    :param arr: the list to be sorted
    :type arr: list(list())
    :param rev: indicates if the list should be reversed
    :type rev: bool
    :return: a new sorted list
    :rtype: list(list())
    """
    temp = list(arr)
    if rev:
        a = sorted(temp, key=lambda temp:temp[2])
        a.reverse()
        return a
    else:
        return sorted(temp, key=lambda temp: temp[2])

def make_config_file(product_id):
    """
    The function will create a string that can be added to a json file.
    """
    data = {
            "General" : {
                "ProductID": product_id,
            },   
            "Model" :
            {
                "FM_Limit": 5000,
                "M": 7,
                "AD_Limit":50000,
                "Learning_Rate": 0.01,
                "Hidden_Layer_Ratio": 0.75
            },
        "Communication" :
        {
            "ServerDomain": "defence.rocks",
            "ServerPort": 80,
            "DefenderListenPort": 4123
        }
    }
    
    with open('Example/Configuration{}_tmp.json'.format(product_id), 'w') as json_file:
        json.dump(data, json_file)


if __name__ == '__main__':
    main()
