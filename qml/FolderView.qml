import Minusphoto 1.0
import QtQuick 2.0
import QtQuick.Controls 1.0
import it.mardy.folderlistmodel 1.0

ScrollView {
    id: root

    property alias folder: folderModel.folder
    property string selectedFile: listView.currentItem ? listView.currentItem.filePath : ""
    property variant selectedFiles

    ListView {
        id: listView
        anchors.fill: parent
        clip: true
        focus: true
        model: folderModel
        spacing: 1
        delegate: FileDelegate {
            id: delegate
            width: ListView.view.width
            fileName: model.fileName
            filePath: "file:" + model.filePath
            selected: selection.isSelected(index)
            lastModified: Qt.formatDateTime(model.lastModified)
            onClicked: ListView.view.select(index, mouse.modifiers)

            Connections {
                target: selection
                onItemsChanged: delegate.selected = selection.isSelected(index)
            }
        }

        onCurrentIndexChanged: console.log("Current item: " + selection.get(currentIndex).fileName)

        FolderListModel {
            id: folderModel
            showDirs: false
        }

        ModelSelection {
            id: selection
            model: folderModel

            onIndexesChanged: root.selectedFiles = items("filePath")
        }

        function select(index, modifiers) {
            if (index < 0 || index >= model.count) return
            if (modifiers & Qt.ShiftModifier) {
                selection.setShiftSelection(index)
            } else if (modifiers & Qt.ControlModifier) {
                selection.setCtrlSelection(index)
            } else {
                selection.setSelection(index)
            }
            currentIndex = index
        }

        Keys.onPressed: {
            if (event.key == Qt.Key_Up) {
                select(currentIndex - 1, event.modifiers)
            } else if (event.key == Qt.Key_Down) {
                select(currentIndex + 1, event.modifiers)
            } else {
                return
            }
            event.accepted = true
        }
    }
}
