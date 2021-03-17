function loginValidateForm() {
    let name = document.forms["loginForm"]["usernameName"].value;
    let password = document.forms["loginForm"]["passwordName"].value;

    if (name.length < 5 || password.length < 5) {
        alert("Name and Password must contain 5 characters at least");
        return false;
    }

    let pattern = new RegExp(/[~`!#$%\^&*+=\-\[\]\\';,/{}|\\":<>\?]/); //unacceptable chars
    if (pattern.test(name) || pattern.test(password)) {
        alert("Please only use standard alphanumerics for username and password");
        return false;
    }

    return true; // form is valid
}