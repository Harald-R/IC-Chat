import QtQuick 2.12
import QtQuick.Layouts 1.9
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.12

Page {
    id: registerCredentials
//    property string username
//    property string password

    Rectangle{
        id: backgroundColor
        color: "#273043"
        z: -2
        anchors.fill: parent

        Rectangle {
            id: foregroundBackgroundColor
            x: 220
            width: 300
            color: "#EFF6EE"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40
            anchors.top: parent.top
            anchors.topMargin: 60
            Layout.fillHeight: true
            anchors.horizontalCenter: parent.horizontalCenter
            Rectangle{
                id: foregroundShadow
                width: foregroundBackgroundColor.width
                height: foregroundBackgroundColor.height
                color: "#7EA8BE"
                z: -1
                anchors.verticalCenterOffset: 5
                anchors.horizontalCenterOffset: 5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Pane {
        id: usernamePane
        width: 200
        height: 50
        anchors.verticalCenterOffset: -50
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        TextArea {
            id: usernameTextArea
            width: usernamePane.width
            height: usernamePane.height
            text: qsTr("")
            Layout.fillWidth: true
            anchors.centerIn: parent
            background: Rectangle{
                id: usernameTextAreaBackground
                border.width: 1
                border.color: "#000000"
            }
        }

        Label {
            id: usernameLabel
            x: 64
            y: -26
            color: "#ffffff"
            text: qsTr("Username")
            styleColor: "#ffffff"
            anchors.verticalCenterOffset: -40
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                id: usernameBackground
                width: 200
                height: 30
                color: "#9197AE"
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

        TextArea {
            id: passwordTextArea
            width: passwordPane.width
            height: passwordPane.height
            text: qsTr("")
            Layout.fillWidth: true
            anchors.centerIn: parent
            background: Rectangle{
                id: passwordTextAreaBackground
                border.width: 1
                border.color: "#000000"
            }
        }

        Label {
            id: passwordLabel
            x: 66
            y: -26
            color: "#ffffff"
            text: qsTr("Password")
            styleColor: "#ffffff"
            anchors.verticalCenterOffset: -40
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                id: passwordBackground
                x: -66
                y: -4
                width: 200
                height: 30
                color: "#273043"
                z: -1
                anchors.horizontalCenter: passwordLabel.horizontalCenter
                anchors.verticalCenter: passwordLabel.verticalCenter
            }
        }
    }



    Pane {
        id: emailPane
        x: 2
        y: 7
        width: 200
        height: 50
        z: 1
        anchors.verticalCenter: parent.verticalCenter
        TextArea {
            id: emailTextArea
            width: emailPane.width
            height: emailPane.height
            text: qsTr("")
            Layout.fillWidth: true
            anchors.centerIn: parent
            background: Rectangle{
                id: confirmPasswordTextAreaBackground
                border.width: 1
                border.color: "#000000"
            }
        }

        Label {
            id: emailLabel
            x: 66
            y: -26
            color: "#ffffff"
            text: qsTr("Email")
            styleColor: "#ffffff"
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -40
            anchors.horizontalCenter: parent.horizontalCenter
            Rectangle {
                id: emailBackground
                x: -66
                y: -4
                width: 200
                height: 30
                color: "#273043"
                anchors.verticalCenter: emailLabel.verticalCenter
                anchors.horizontalCenter: emailLabel.horizontalCenter
                z: -1
            }
            anchors.horizontalCenterOffset: 0
        }
        anchors.verticalCenterOffset: 130
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: registerText
        x: 308
        y: 58
        text: qsTr("Register")
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        anchors.verticalCenterOffset: -200
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 25

        Rectangle {
            id: registerTextBackground
            width: 200
            height: 30
            color: "#7EA8BE"
            z: -1
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            Rectangle{
                id: registerTextBackgroundShadow

                width: parent.width
                height: parent.height
                color: "#273043"
                z: -1
                anchors.verticalCenterOffset: 3
                anchors.horizontalCenterOffset: 3
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Button {
        id: credentialsButton
        x: 278
        y: 391
        height: 50
        width: 200
        text: qsTr("Register")
        anchors.verticalCenterOffset: 200
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        enabled: usernameTextArea.length && passwordTextArea.length && emailTextArea.length
        onClicked: {
            //            username = usernameTextArea.getText;
            //            password = passwordTextArea.getText;

            // TODO: Check registration data
            clientHandler.sendMessage("SRV|register|" + usernameTextArea.text + "|" + passwordTextArea.text + "|" + emailTextArea.text)
            mainLayout.push("qrc:/Resources/qml/MainApplicationWindow.qml")
        }

        background: Rectangle{
            id: credentialsButtonBackground
            anchors.fill: parent
            color: credentialsButton.enabled ? "#7EA8BE" : "#EFF6EE"
            border.color: "#000000"
            border.width: 1
            Rectangle{
                id: credentialsButtonBackgroundShadow

                width: parent.width
                height: parent.height
                color: credentialsButton.enabled ? "#273043" : "#EFF6EE"
                z: -1
                anchors.verticalCenterOffset: 3
                anchors.horizontalCenterOffset: 3
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
