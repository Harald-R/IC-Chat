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
               font.pixelSize: 20
               anchors.centerIn: parent
               }
           }

    ListView {
           id: listView
           width: 300
           anchors.fill: parent
           topMargin: 48
           leftMargin: 48
           bottomMargin: 48
           rightMargin: 48
           spacing: 15
           model: groupsModel //["User1", "User2", "User3"]
           delegate: ItemDelegate {
               id: itemDelegate
               background: Rectangle{
                    id: userItemBackground
                    anchors.centerIn: parent
                    width: parent.width + 5
                    height: parent.height + 5
                    color: itemDelegate.down ? "#ffffff" : "#EFF6EE"
                    radius: 4
               }

               text: model.name
               width: listView.width - listView.leftMargin - listView.rightMargin
               height: 40 /*avatar.implicitHeight*/
               leftPadding: 72 /*avatar.implicitWidth + 32*/

               onClicked: rightGridView.push("qrc:/ConversationPage.qml", { groupId: model.id, groupName: model.name })

               Image {
                   id: avatar
                   width: 40
                   height: 40
                   fillMode:Image.PreserveAspectFit

                   source: "qrc:/download.png"/* + modelData.replace(" ", "_") + ".png"*/
                }

           }

    }

       Rectangle {
           id: background
           color: "#273043"
           z: -1
           anchors.fill: parent
       }
}
