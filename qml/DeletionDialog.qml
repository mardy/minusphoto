// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import QtQuick.Window 2.0

Window {
    id: root
    property string fileName
    visible: false

    Text {
        text: qsTr("Are you sure you want to delete '%1'?").arg(fileName)
    }
}
