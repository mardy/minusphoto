import QtQuick 2.0
import Speqtacle 1.0

Flickable {
    id: root
    property alias source: sizeController.source

    z: enabled ? 1 : 0
    anchors.fill: parent
    contentWidth: image.width; contentHeight: image.height

    states: State {
        name: "covered"; when: !root.enabled
        PropertyChanges { target: root; opacity: 0 }
    }

    transitions: [
        Transition {
            from: "covered"
            NumberAnimation { property: "opacity"; duration: 200 }
        },
        Transition {
            to: "covered"
            NumberAnimation { property: "opacity"; duration: 200; easing.type: Easing.InQuad }
        }
    ]

    Item {
        width: Math.max(image.width, root.width)
        height: Math.max(image.height, root.height)

        Image {
            id: image
            anchors.centerIn: parent
            asynchronous: true
            smooth: true
        }
    }

    SizeController {
        id: sizeController
        image: image
        viewSize: Qt.size(root.width, root.height)
        onZoomChanged: console.log("Zoom changed: " + zoom)
    }
}
