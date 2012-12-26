include(common-config.pri)

TEMPLATE = subdirs
SUBDIRS = \
    folderlistmodel \
    src
CONFIG += ordered

DISTNAME = $${PROJECT_NAME}-$${PROJECT_VERSION}
dist.commands = "git archive --format=tar --prefix=$${DISTNAME}/ HEAD | bzip2 -9 > $${DISTNAME}.tar.bz2"
QMAKE_EXTRA_TARGETS += dist
