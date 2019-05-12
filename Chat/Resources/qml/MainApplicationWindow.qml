import QtQuick 2.9
import QtQuick.Window 2.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11


SplitView {
    id: conversationView
    anchors.left: parent.left
    anchors.leftMargin: 0
    anchors.fill:parent
        ContactPage{
            // Nu stiu de ce umple toata fereastra ca si width
            // desi are maximum width setat 300.
            //Asta vad in Design cand selectez leftGridView cu contactele
            id: leftGridView
            width: 300
            height: 199

            anchors.rightMargin: 700

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
            anchors.left: leftGridView.right
            anchors.leftMargin: 2

            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.minimumWidth: 300
            Layout.preferredWidth: 500
            Layout.maximumWidth: 500
            Layout.minimumHeight: 150
            delegate: StackViewDelegate {
                    function transitionFinished(properties)
                    {
                        properties.exitItem.opacity = 1
                    }

                    pushTransition: StackViewTransition {
                        PropertyAnimation {
                            target: enterItem
                            property: "opacity"
                            from: 0
                            to: 1
                        }
                    }
            }
            initialItem:ConversationPage{}
        }
    }
