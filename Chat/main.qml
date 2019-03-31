import QtQuick 2.9
import QtQuick.Window 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

ApplicationWindow {
    visible: true
    width: 540
    height: 960
    title: qsTr("Chat")

    StackView {
            id: stackView
            anchors.fill: parent
            initialItem: ContactPage {}
        }


}
