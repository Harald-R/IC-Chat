import QtQuick 2.12
import QtQuick.Layouts 1.9
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.12

Page {
    id: loginCredentials
    property string username
    property string password
    visible: false
    Rectangle{
        id: backgroundColor
        color: "#1D3973"
        z: -2
        anchors.fill: parent
        Rectangle {
            id: foregroundBackgroundColor
            x: 220
            width: 300
            color: "#f9d41d"
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
                color: "#d26208"
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
                color: "#E7961A"
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
                color: "#592525"
                z: -1
                anchors.horizontalCenter: passwordLabel.horizontalCenter
                anchors.verticalCenter: passwordLabel.verticalCenter
            }
        }
    }



    Text {
        id: loginText
        x: 308
        y: 58
        text: qsTr("LOGIN")
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        anchors.verticalCenterOffset: -200
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 25

        Rectangle {
            id: loginTextBackground
            width: 200
            height: 30
            color: "#e87909"
            z: -1
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            DropShadow{
                id: loginRectShadow
                anchors.fill: source
                cached: true
                horizontalOffset: 2
                verticalOffset: 3
                radius: 10.0
                samples: 64
                color: "#80000000"
                smooth: true
                source: parent

            }
        }
    }

    Button {
        id: credentialsButton
        x: 278
        y: 391
        text: qsTr("Login")
        anchors.verticalCenterOffset: 200
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        enabled: usernameTextArea.length && passwordTextArea.length
        onClicked: {
            //            username = usernameTextArea.getText;
            //            password = passwordTextArea.getText;
            mainLayout.push("qrc:/MainApplicationWindow.qml")
        }
        DropShadow{
            id: credentialsButtonRectShadow
            anchors.fill: source
            cached: true
            horizontalOffset: 3
            verticalOffset: 3
            radius: 30.0
            samples: 64
            color: "#80000000"
            smooth: true
            source: parent
//
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
        onClicked: mainLayout.push("qrc:/RegisterPage.qml")
        DropShadow{
            id: registrationButtonRectShadow
            anchors.fill: source
            cached: true
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 16
            color: "#80000000"
            smooth: true
            source: parent

        }
    }




}













































































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:14;anchors_x:268}D{i:18;anchors_x:268}
}
 ##^##*/
