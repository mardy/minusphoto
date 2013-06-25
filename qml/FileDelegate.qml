import QtQuick 2.0

Rectangle {
    id: root

    property alias fileName: name.text
    property alias filePath: image.source
    property alias lastModified: time.text
    property bool selected: false

    signal clicked(variant mouse)

    height: 64
    color: selected ? "lightsteelblue" : "white"

    Item {
        id: imageBox
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: height

        Image {
            id: image
            anchors.centerIn: parent
            asynchronous: true
            fillMode: Image.PreserveAspectFit
            sourceSize.width: 64
            width: parent.width
            height: width
        }

        Image {
            id: notImage
            anchors.centerIn: parent
            source: "qrc:/not-image.svg"
            visible: image.status == Image.Error
        }
    }

    Column {
        id: textBox
        anchors.left: imageBox.right
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        spacing: 2

        Text {
            id: name
        }

        Text {
            id: time
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked(mouse)
    }
}
