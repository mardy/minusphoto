import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

FocusScope {
    id: root

    width: 360
    height: 400
    focus: true

    Keys.onDeletePressed: deleteFile(folderView.selectedFile)

    Rectangle {
        anchors.fill: parent
        color: "#efe"

        SplitView {
            anchors.fill: parent
            orientation: Qt.Horizontal

            SplitView {
                Layout.minimumWidth: 120
                orientation: Qt.Vertical

                FolderBrowser {
                    id: folderBrowser
                    Layout.minimumHeight: 64
                    KeyNavigation.tab: folderView
                    KeyNavigation.backtab: folderView
                    focus: true
                    folder: startFolder
                }

                FolderView {
                    id: folderView
                    KeyNavigation.tab: folderBrowser
                    KeyNavigation.backtab: folderBrowser
                    folder: folderBrowser.folder
                    onSelectedFilesChanged: console.log("Selected files: " + selectedFiles)
                }
            }

            ImageView {
                id: imageView
                source: folderView.selectedFile
            }
        }
    }

    DeletionDialog {
        id: confirmDeletion
        visible: false

        //onAccepted: console.log("Accepted")
        //onRejected: console.log("Rejected")
    }

    function deleteFile(fileName) {
        console.log("Deleting " + fileName)
        confirmDeletion.fileName = fileName
        confirmDeletion.focus = true
        confirmDeletion.visible = true
    }
}
