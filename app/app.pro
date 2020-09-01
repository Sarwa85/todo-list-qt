QT       += core gui quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widgets/mainwidget.cpp \
    widgets/mainwindow.cpp \
    widgets/previewtaskwidget.cpp \
    widgets/taskdelegate.cpp

TRANSLATIONS += \
    app_pl_PL.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    widgets/mainwidget.ui \
    widgets/mainwindow.ui \
    widgets/previewtaskwidget.ui

HEADERS += \
    widgets/mainwidget.h \
    widgets/mainwindow.h \
    widgets/previewtaskwidget.h \
    widgets/taskdelegate.h

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -ltodolist
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -ltodolist
#else:unix: LIBS += -L$$OUT_PWD/../lib/ -ltodolist
LIBS += -L$$OUT_PWD/../lib/ -ltodolist

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/release/libtodolist.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/debug/libtodolist.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/release/todolist.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/debug/todolist.lib
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/libtodolist.a
PRE_TARGETDEPS += $$OUT_PWD/../lib/libtodolist.a

DISTFILES += \
    qml/EditPage.qml \
    qml/ListPage.qml \
    qml/Style.qml \
    qml/TaskDelegate.qml \
    qml/main.qml \
    qml/qmldir
