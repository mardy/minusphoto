import QtQuick 2.0
import QtQuick.Controls 1.0
import it.mardy.folderlistmodel 1.0

ScrollView {
    property alias folder: folderModel.folder

    ListView {
        focus: true
        model: folderModel
        delegate: FolderDelegate {
            id: folderDelegate
            width: ListView.view.width
            fileName: model.fileName
            selected: ListView.isCurrentItem
            onClicked: folderModel.folder = "file://" + model.filePath
        }

        FolderListModel {
            id: folderModel
            showFiles: false
            showDirs: true
            showDotAndDotDot: true
        }

        Component.onCompleted: interactive = true // QTBUG-31976
    }
}
