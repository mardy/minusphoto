include(../common-config.pri)

TARGET = speqtacle

QT += \
    gui \
    quick

SOURCES += \
    main.cpp \
    model-selection.cpp \
    size-controller.cpp \
    types.cpp \
    view.cpp

HEADERS += \
    debug.h \
    model-selection.h \
    size-controller.h \
    types.h \
    view.h

RESOURCES += \
    $${TOP_SRC_DIR}/data/icons.qrc \
    $${TOP_SRC_DIR}/qml/qml.qrc
