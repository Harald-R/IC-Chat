import QtQuick 2.0
import QtTest 1.0
import "../Chat/Resources/qml"

TestCase {
    name: "ApplicationTests"
    id: testCase

    LoginPage{
        id: loginPage
    }

//    function initTestCase() {

//    }

//    function cleanupTestCase() {
//    }

    function test_inputFields() {
        var username = loginPage.getUsername();
        compare(username, "user_1");

        var password = loginPage.getPassword();
        compare(password, "password");
    }

    function test_buttonFunc() {
        var beforeState = loginPage.getRegisterButtonState();
        loginPage.clickRegisterButton();
        var afterState = loginPage.getRegisterButtonState();

        compare(afterState, !beforeState);
    }
}
