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
    property int currentWindow : 10

    title: qsTr("Chat")
    StackView{
        id: mainLayout
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.fill:parent

        initialItem: LoginPage{}
        delegate: StackViewDelegate{
            function transitionFinished(properties)
            {
                properties.exitItem.opacity = 1
            }
            pushTransition: StackViewTransition{
                PropertyAnimation{
                    target: enterItem
                    property: "opacity"
                    from: 0
                    to: 1
                }
            }
        }
    }

}
