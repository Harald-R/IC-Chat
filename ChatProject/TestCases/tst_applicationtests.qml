import QtQuick 2.0
import QtTest 1.0
import "../Chat/Resources/qml"
import "../ServerApp/"

TestCase {
    name: "ApplicationTests"
    id: testCase

    LoginPage{
        id: loginPage
    }
    RegisterPage{
        id: registerPage
    }

    function test_loginInputFields() {
        var username = loginPage.username;
        compare(username, "user_1");
        var password = loginPage.password;
        compare(password, "password");
    }

    function test_loginButtonsFunc() {
        var beforeRegisterState = loginPage.registerButtonState;
        loginPage.clickRegisterButton();
        var afterRegisterState = loginPage.registerButtonState;
        compare(afterRegisterState, !beforeRegisterState);

        var beforeCredentialsState = loginPage.credentialsButtonState;
        loginPage.clickCredentialsButton();
        var afterCredentialsState = loginPage.credentialsButtonState;
        compare(afterCredentialsState, !beforeCredentialsState);
    }

    function test_registerButtonFunc() {
        var beforeRegisterState = registerPage.registerButtonState;
        registerPage.clickRegisterButton();
        var afterRegisterState = registerPage.registerButtonState;
        compare(afterRegisterState, !beforeRegisterState);
    }
}
