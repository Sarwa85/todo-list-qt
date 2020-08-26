QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_filerepository.cpp

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
