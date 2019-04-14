import QtQuick 2.9
import QtQuick.Window 2.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11

ApplicationWindow {
    id: root_window
    visible: true
    width: 1000
    height: 600
    color: "#3d4766"

    title: qsTr("Chat")
    // Sa dea culoare sa se diferentieze contactele din stanga cu chatul din dreapta
    // am pus opacitate mai scazuta la lista de contacte
//    Rectangle {
//        implicitWidth: root_window.width
//        implicitHeight: root_window.height
//        color:"red"
        SplitView {
            id: layout
            anchors.fill:parent

            ContactPage{
                // Nu stiu de ce umple toata fereastra ca si width
                // desi are maximum width setat 300.
                //Asta vad in Design cand selectez leftGridView cu contactele

                id: leftGridView
                width: 300
                height: 199
                anchors.right: rightGridView.left
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.rightMargin: 700
                anchors.bottomMargin: 0
                Layout.minimumWidth: 50
                Layout.preferredWidth: 100
                Layout.maximumWidth: 300
                Layout.minimumHeight: 150

            }


            StackView{
                // Stack view ca sa putem pushui fereastra noua de chat cand se da click pe un user
                // Adica sa se schimbe conversatia
                id: rightGridView
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: leftGridView.right
                anchors.leftMargin: 2
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.minimumWidth: 300
                Layout.preferredWidth: 500
                Layout.maximumWidth: 500
                Layout.minimumHeight: 150
                initialItem: ConversationPage{ x: 0 ; width: 700 }
            }
        }
//    }

}








