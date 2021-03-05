from flask import Flask

app = Flask(__name__)

@app.route("/")  # if we use the domain only, we'll get here
def home():
    return "home page"

if __name__ == '__main__':
    app.run()