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
    ChatPage{
        id: chatPage
    }

//    function initTestCase() {
//    }

//    function cleanupTestCase() {
//    }

    function test_inputFields() {
        var username = loginPage.username;
        compare(username, "user_1");
        var password = loginPage.password;
        compare(password, "password");
    }

    function test_buttonFunc() {
        var beforeRegisterState = loginPage.registerButtonState;
        loginPage.clickRegisterButton();
        var afterRegisterState = loginPage.registerButtonState;
        compare(afterRegisterState, !beforeRegisterState);

        var beforeCredentialsState = loginPage.credentialsButtonState;
        loginPage.clickCredentialsButton();
        var afterCredentialsState = loginPage.credentialsButtonState;
        compare(afterCredentialsState, !beforeCredentialsState);

        console.log(chatPage.currentWindow);
    }
}
