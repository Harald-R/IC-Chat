import QtQuick 2.12
import QtQuick.Layouts 1.9
import QtQuick.Controls 2.4

Page {
    id: root
//    anchors.rightMargin: parent.right
    property string groupId
    property string groupName

    Component.onCompleted: {
        clientHandler.clearMessages()
        clientHandler.requestMessages(groupId)
    }

    header: ToolBar {
//        ToolButton {
//            text: qsTr("Back")
//            anchors.left: parent.left
//            anchors.leftMargin: 10
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: root.StackView.view.pop()
//        }

        Label {
            id: pageTitle
            text: groupName
            font.pixelSize: 17
            anchors.centerIn: parent
        }
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: textInput.leftPadding + messageField.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            verticalLayoutDirection: ListView.BottomToTop
            spacing: 12
            model: conversationModel

            delegate: Column {
                anchors.right: sentByMe ? parent.right : undefined
                spacing: 6

                readonly property bool sentByMe: model.author === conversationModel.my_user_id

                Row {
                    id: messageRow
                    spacing: 6
                    anchors.right: sentByMe ? parent.right : undefined

                    Image {
                        id: avatar
                        width: 40
                        height: 40
                        source: !sentByMe ? "qrc:/Resources/images/download.png" : ""/* + model.author.replace(" ", "_") + ".png" : ""*/
                    }

                    Rectangle {
                        width: Math.min(messageText.implicitWidth + 24,
                            listView.width - (!sentByMe ? avatar.width + messageRow.spacing : 0))
                        height: messageText.implicitHeight + 24
                        color: sentByMe ? "#4592af" : "lightgrey"

                        Label {
                            id: messageText
                            text: model.content
                            color: sentByMe ? "white" : "black"
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }
                    }
                }

                Label {
                    id: timestampText
                    text: Qt.formatDateTime(model.date, "d MMM hh:mm")
                    color: "lightgrey"
                    anchors.right: sentByMe ? parent.right : undefined
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }

        Pane {
            id: textInput
            Layout.fillWidth: true
            background: Rectangle{
                id: textInputBackground
                anchors.fill: parent
                color: "#e2e2e2"
            }

            RowLayout {
                width: parent.width

                TextArea {
                    id: messageField
                    Layout.fillWidth: true
                    placeholderText: qsTr("Compose message")
                    wrapMode: TextArea.Wrap
                }

                Button {
                    id: sendButton
                    text: qsTr("Send")
                    enabled: messageField.length > 0
                    onClicked: {
                        clientHandler.sendMessage("SRV|new_message|"+groupId+"|"+messageField.text)
                        messageField.text = "";
                    }
                    background: Rectangle{
                       id:sendButtonBackground
                       border.width: 1
                       border.color: sendButton.enabled ? "#e2e2e2" : "#cccccc"
                    }
                }
            }
        }
    }
}
