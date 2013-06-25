import QtQuick 2.0

Rectangle {
    id: root

    property alias fileName: name.text
    property bool selected: false

    signal clicked

    height: name.height
    color: selected ? "lightsteelblue" : "white"

    Keys.onReturnPressed: clicked()

    Text {
        id: name
        width: parent.width
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
