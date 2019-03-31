import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.9
import SqlDB 1.0

Page {
    id:root
       anchors.fill: parent
       header: ToolBar {
               Label {
                   text: qsTr("Contacts")
                   font.pixelSize: 20
                   anchors.centerIn: parent
               }
           }

ListView {

           id: listView
           anchors.fill: parent
           topMargin: 48
           leftMargin: 48
           bottomMargin: 48
           rightMargin: 48
           spacing: 20
           model: ["User1", "User2", "User3"]
           delegate: ItemDelegate {
               text: modelData
               width: listView.width - listView.leftMargin - listView.rightMargin
               height: 40 /*avatar.implicitHeight*/
               leftPadding: 72 /*avatar.implicitWidth + 32*/
               onClicked: root.StackView.view.push("qrc:/ConversationPage.qml", { inConversationWith: modelData })
                Image {
                   id: avatar
                   width: 40
                   height: 40
                   fillMode:Image.PreserveAspectFit
                   source: "qrc:/download.png"/* + modelData.replace(" ", "_") + ".png"*/
               }
           }
       }
}
