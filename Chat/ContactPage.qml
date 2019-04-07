import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.9
import SqlDB 1.0

Page {
    id:root
    width: 300
    anchors.fill: parent
       header: ToolBar {
           id: toolBar
           Label {
               text: qsTr("Contacts")
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
           spacing: 20
           model: ["User1", "User2", "User3"]
           delegate: ItemDelegate {
               text: modelData
               width: listView.width - listView.leftMargin - listView.rightMargin
               height: 40 /*avatar.implicitHeight*/
               leftPadding: 72 /*avatar.implicitWidth + 32*/
               // Nu stiu cum sa gasesc StackView-ul din main ca sa pot face push la fereastra de conversatie
               // aferenta userului clicku-it (inConversationWith: modelData)
               // Inainte era root.StackView.view.push("qrc:/ConversationPage.qml", { inConversationWith: modelData })
               // ma gandeam la ceva de genul: root.Rectangle.RowLayout.StackView....
               // fiind nested una in alta, insa nu merge
               onClicked: rightGridView.push("qrc:/ConversationPage.qml", { inConversationWith: modelData })

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

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
