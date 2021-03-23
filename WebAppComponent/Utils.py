import re

EMAIL_TEMPLATE = "^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$"
# username: 5-30 letters/numbers only
USERNAME_TEMPLATE = "^[a-zA-Z0-9]{5,30}$"
# password: 8 characters min, at least one letter, one number, one special char
PASSWORD_TEMPLATE = "^(?=.*[A-Za-z])(?=.*\d)(?=.*[@$!%*#?&])[A-Za-z\d@$!%*#?&]{8,}$"

IP_TEMPLATE = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"


def validate_input(username, password, email="valid@gmail.com"):
    try:
        valid_email = re.search(EMAIL_TEMPLATE, email)
        valid_username = re.search(USERNAME_TEMPLATE, username)
        valid_password = re.search(PASSWORD_TEMPLATE, password)
    except Exception as e:
        print(e)
        return False

    return valid_email and valid_password and valid_username


def validate_ip_address(address):
    try:
        return re.search(IP_TEMPLATE, address)
    except Exception as e:
        return False
