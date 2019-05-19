import QtQuick 2.12
import QtQuick.Layouts 1.9
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.12

Page {
    id: loginCredentials
    visible: false
    property string password : passwordTextArea.text
    property string username : usernameTextArea.text
    property bool registerButtonState: gotoRegisterPage.checked
    property bool credentialsButtonState: credentialsButton.checked

    function clickRegisterButton(){
        gotoRegisterPage.checked = true;
    }

    function clickCredentialsButton(){
        credentialsButton.checked = true;
    }

    Connections {
        target: authenticator
        onValidCredentials: mainLayout.push("qrc:/Resources/qml/MainApplicationWindow.qml")
        onInvalidCredentials: {
            invalidLabel.visible = true
        }
    }

    Rectangle{
        id: backgroundColor
        color: "#EFEEEE"
        z: -2
        anchors.fill: parent
        Rectangle {
            id: foregroundBackgroundColor
            x: 220
            width: 300
            color: "#EFEEEE"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40
            anchors.top: parent.top
            anchors.topMargin: 60
            Layout.fillHeight: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Label {
        id: invalidLabel
        visible: false
        z: 1
        color: "#fff"
        text: qsTr("Invalid credentials")
        styleColor: "#fff"
        anchors.verticalCenterOffset: 120
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        Rectangle {
            id: invalidBackground
            width: 200
            height: 40
            color: "#B22222"
            z: -1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Pane {
        id: usernamePane
        width: 200
        height: 50
        anchors.verticalCenterOffset: -50
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        TextField {
            id: usernameTextArea
            width: usernamePane.width
            height: usernamePane.height
            text: qsTr("user_1") //qsTr("")
            Layout.fillWidth: true
            anchors.centerIn: parent
            wrapMode: TextEdit.Wrap
            clip: true
        }

        Label {
            id: usernameLabel
            x: 64
            y: -36
            color: "#ffffff"
            text: qsTr("Username")
            styleColor: "#ffffff"
            anchors.verticalCenterOffset: -45
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                id: usernameBackground
                width: 200
                height: 40
                color: "#4592af"
                z: -1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Pane {
        id: passwordPane
        width: 200
        height: 50
        anchors.verticalCenterOffset: 50
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        TextField {
            id: passwordTextArea
            width: passwordPane.width
            height: passwordPane.height
            text: qsTr("password") //qsTr("")
            Layout.fillWidth: true
            anchors.centerIn: parent
            wrapMode: TextEdit.Wrap
            clip: true
            echoMode: TextInput.Password
        }

        Label {
            id: passwordLabel
            x: 66
            y: -26
            color: "#ffffff"
            text: qsTr("Password")
            styleColor: "#ffffff"
            anchors.verticalCenterOffset: -45
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                id: passwordBackground
                x: -66
                y: -4
                width: 200
                height: 40
                color: "#4592af"
                z: -1
                anchors.horizontalCenter: passwordLabel.horizontalCenter
                anchors.verticalCenter: passwordLabel.verticalCenter
            }
        }
    }

    Rectangle {
        id: loginTextBackground
        width: parent.width
        height: 150
        color: "#33313b"
        z: -1
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: loginText
        x: 308
        y: 58
        text: qsTr("LOGIN")
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        anchors.top: loginTextBackground.bottom
        anchors.topMargin: -50
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 30
        color: "#FFF"
    }

    Button {
        id: credentialsButton
        x: 278
        y: 391
        height: 50
        width: 150
        text: qsTr("Login")
        anchors.verticalCenterOffset: 200
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        enabled: usernameTextArea.length && passwordTextArea.length
        onClicked: {
            clientHandler.sendMessage("SRV|login|" + usernameTextArea.text + "|" + passwordTextArea.text)
        }
        background: Rectangle{
            id: credentialsButtonBackground
            anchors.fill: parent
            color: credentialsButton.enabled ? "#4592af" : "#DDD"
        }
        contentItem: Text {
            renderType: Text.NativeRendering
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            color: "white"
            text: credentialsButton.text
        }
    }

    Button {
        id: gotoRegisterPage
        y: 382
        text: qsTr("I don't have an account")
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 200
        onClicked: mainLayout.push("qrc:/Resources/qml/RegisterPage.qml")
        contentItem: Text {
            renderType: Text.NativeRendering
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 12
            color: "grey"
            text: gotoRegisterPage.text
        }
    }
}
