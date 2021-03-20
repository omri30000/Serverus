function registerValidateForm() {
    var name = document.forms["registerForm"]["usernameName"].value;
    var password = document.forms["registerForm"]["passwordName"].value;
    var email = document.forms["registerForm"]["emailName"].value;
    if (name.length < 5 || password.length < 5) {
        alert("Name and Password must contain 5 characters at least");
        return false;
    }

    var pattern = new RegExp(/[~`!#$%\^&*+=\-\[\]\\';,/{}|\\":<>\?]/); //unacceptable chars
    if (pattern.test(name) || pattern.test(password)) {
        alert("Please only use standard alphanumerics for username and password");
        return false;
    }

    var emailPattern = new RegExp(/[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+/);
    if (!emailPattern.test(email))
    {
        alert("Email is invalid, please check your input");
        return false;
    }

    return true; // form is valid
}

