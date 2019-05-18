import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.9

Page {
    id:root
    width: 300
    anchors.fill: parent
    header: ToolBar {
        id: toolBar
        Label {
            text: qsTr("Groups")
            transformOrigin: Item.Left
            anchors.verticalCenterOffset: 0
            anchors.horizontalCenterOffset: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            font.pixelSize: 17
            anchors.centerIn: parent
        }
    }

    ListView {
           id: listView
           width: 300
           anchors.fill: parent
           spacing: 10
           model: groupsModel //["User1", "User2", "User3"]
           delegate: ItemDelegate {
               id: itemDelegate
               background: Rectangle{
                   id: userItemBackground
                   anchors.centerIn: parent
                   width: parent.width
                   height: parent.height + 10
                   color: itemDelegate.down ? "#ffffff" : "#efefef"
                   border.color: "#ddd"
                   border.width: 1
               }
               contentItem: Text {
                   text: itemDelegate.text
                   color: "#33313b"
               }

               text: model.name
               width: listView.width - listView.leftMargin - listView.rightMargin
               height: avatar.height
               leftPadding: avatar.width + 32
               onClicked: rightGridView.push("qrc:/Resources/qml/ConversationPage.qml", { groupId: model.id, groupName: model.name })

               Image {
                   id: avatar
                   width: 40
                   height: 40
                   fillMode:Image.PreserveAspectFit

                   source: "qrc:/Resources/images/download.png"/* + modelData.replace(" ", "_") + ".png"*/
                }

           }

    }

       Rectangle {
           id: background
           color: "#33313b"
           z: -1
           anchors.fill: parent
       }
}
