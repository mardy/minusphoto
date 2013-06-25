import QtQuick 2.0
import Speqtacle 1.0

Rectangle {
    id: root
    color: "#aaa"
    clip: true
    property variant source

    ResizedImage {
        id: image1
        enabled: true
    }

    ResizedImage {
        id: image2
        enabled: false
    }

    onSourceChanged: {
        if (image1.enabled) {
            image1.enabled = false
            image2.source = source
            image2.enabled = true
        } else {
            image2.enabled = false
            image1.source = source
            image1.enabled = true
        }
    }
}
