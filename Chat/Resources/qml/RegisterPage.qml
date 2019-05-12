import QtQuick 2.12
import QtQuick.Layouts 1.9
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.12

Page {
    id: registerCredentials

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
            text: qsTr("")
            Layout.fillWidth: true
            anchors.centerIn: parent
            wrapMode: TextEdit.Wrap
            clip: true
        }

        Label {
            id: usernameLabel
            x: 64
            y: -26
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
            text: qsTr("")
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



    Pane {
        id: emailPane
        width: 200
        height: 50
        z: 1
        anchors.verticalCenterOffset: 150
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        TextField {
            id: emailTextArea
            width: emailPane.width
            height: emailPane.height
            text: qsTr("")
            Layout.fillWidth: true
            anchors.centerIn: parent
            wrapMode: TextEdit.Wrap
            clip: true
        }

        Label {
            id: emailLabel
            x: 66
            y: -26
            color: "#ffffff"
            text: qsTr("Email")
            styleColor: "#ffffff"
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -45
            anchors.horizontalCenter: parent.horizontalCenter
            Rectangle {
                id: emailBackground
                x: -66
                y: -4
                width: 200
                height: 40
                color: "#4592af"
                anchors.verticalCenter: emailLabel.verticalCenter
                anchors.horizontalCenter: emailLabel.horizontalCenter
                z: -1
            }
            anchors.horizontalCenterOffset: 0
        }
    }

    Rectangle {
        id: registerTextBackground
        width: parent.width
        height: 150
        color: "#33313b"
        z: -1
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: registerText
        x: 308
        y: 58
        text: qsTr("Register")
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        anchors.top: loginTextBackground.bottom
        anchors.topMargin: -50
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 30
        color: "#FFF"
    }

    Button {
        id: registerButton
        x: 278
        y: 391
        height: 50
        width: 150
        text: qsTr("Register")
        anchors.verticalCenterOffset: 220
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        enabled: usernameTextArea.length && passwordTextArea.length && emailTextArea.length
        onClicked: {
            // TODO: Check registration data
            clientHandler.sendMessage("SRV|register|" + usernameTextArea.text + "|" + passwordTextArea.text + "|" + emailTextArea.text)
            mainLayout.push("qrc:/Resources/qml/MainApplicationWindow.qml")
        }
        background: Rectangle{
            id: registerButtonBackground
            anchors.fill: parent
            color: registerButton.enabled ? "#4592af" : "#DDD"
        }
        contentItem: Text {
            renderType: Text.NativeRendering
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            color: "white"
            text: registerButton.text
        }
    }
}
