import QtQuick 2.12
import QtQuick.Layouts 1.9
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.12

Page {
    id: registerCredentials
    property string username
    property string password

    Rectangle{
        id: backgroundColor
        color: "#1d3973"
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
                color: "#944530"
                z: -1
                anchors.horizontalCenter: passwordLabel.horizontalCenter
                anchors.verticalCenter: passwordLabel.verticalCenter
            }
        }
    }



    Pane {
        id: confirmPasswordPane
        x: 2
        y: 7
        width: 200
        height: 50
        z: 1
        anchors.verticalCenter: parent.verticalCenter
        TextArea {
            id: confirmPasswordTextArea
            width: confirmPasswordPane.width
            height: confirmPasswordPane.height
            text: qsTr("")
            Layout.fillWidth: true
        }

        Label {
            id: confirmPasswordLabel
            x: 66
            y: -26
            color: "#ffffff"
            text: qsTr("Confirm Password")
            styleColor: "#ffffff"
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -40
            anchors.horizontalCenter: parent.horizontalCenter
            Rectangle {
                id: confirmPasswordBackground
                x: -66
                y: -4
                width: 200
                height: 30
                color: "#592525"
                anchors.verticalCenter: confirmPasswordLabel.verticalCenter
                anchors.horizontalCenter: confirmPasswordLabel.horizontalCenter
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
            color: "#e87909"
            z: -1
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            DropShadow{
                id: registerRectShadow
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
        text: qsTr("Register")
        anchors.verticalCenterOffset: 200
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        enabled: usernameTextArea.length && passwordTextArea.length && confirmPasswordTextArea.length
        onClicked: {
            //            username = usernameTextArea.getText;
            //            password = passwordTextArea.getText;
            mainLayout.push("qrc:/LoginPage.qml")
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

        }

    }





}



























































































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2;anchors_height:200;anchors_y:140}
}
 ##^##*/
