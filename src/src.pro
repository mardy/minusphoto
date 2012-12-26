include(../common-config.pri)

TARGET = speqtacle

QT += \
    declarative \
    gui \
    opengl

SOURCES += \
    main.cpp \
    view.cpp

HEADERS += \
    debug.h \
    view.h

RESOURCES += \
    $${TOP_SRC_DIR}/data/icons.qrc \
    $${TOP_SRC_DIR}/qml/qml.qrc
