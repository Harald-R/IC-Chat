import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtQuick .Layouts 1.12

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
