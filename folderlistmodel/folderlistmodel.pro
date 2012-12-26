TARGET  = qmlfolderlistmodelplugin
TARGETPATH = it/mardy/folderlistmodel
DESTDIR = $${TARGETPATH}
TEMPLATE = lib

QT += declarative script

CONFIG += plugin

SOURCES += qdeclarativefolderlistmodel.cpp plugin.cpp
HEADERS += qdeclarativefolderlistmodel.h

QTDIR_build:DESTDIR = $$QT_BUILD_TREE/imports/$$TARGETPATH
target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

qmldir.files += $$DESTDIR/qmldir
qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

symbian:{
    TARGET.UID3 = 0x20021320

    isEmpty(DESTDIR):importFiles.files = qmlfolderlistmodelplugin$${QT_LIBINFIX}.dll qmldir
    else:importFiles.files = $$DESTDIR/qmlfolderlistmodelplugin$${QT_LIBINFIX}.dll qmldir
    importFiles.path = $$QT_IMPORTS_BASE_DIR/$$TARGETPATH

    DEPLOYMENT += importFiles
}

INSTALLS += target qmldir
