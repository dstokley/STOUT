######################################################################
<<<<<<< HEAD
<<<<<<< HEAD
# qmake project file for qv4l2
=======
# Automatically generated by qmake (1.07a) Sat Jun 17 12:35:16 2006
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
# Automatically generated by qmake (1.07a) Sat Jun 17 12:35:16 2006
=======
# qmake project file for qv4l2
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
######################################################################

TEMPLATE = app
INCLUDEPATH += . ../libv4l2util ../../lib/include ../../include
CONFIG += debug

<<<<<<< HEAD
<<<<<<< HEAD
=======
# Input
HEADERS += qv4l2.h general-tab.h v4l2-api.h capture-win.h
SOURCES += qv4l2.cpp general-tab.cpp ctrl-tab.cpp v4l2-api.cpp capture-win.cpp
LIBS += -L../../lib/libv4l2 -lv4l2 -L../../lib/libv4lconvert -lv4lconvert -lrt -L../libv4l2util -lv4l2util -ldl -ljpeg
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# opengl: to disable opengl suppport comment out the following
# line and the line '#define HAVE_QTGL 1' from ../../config.h
QT += opengl

INCLUDEPATH += $$PWD/../..
INCLUDEPATH += $$PWD/../common
INCLUDEPATH += $$PWD/../v4l2-ctl/
INCLUDEPATH += $$PWD/../v4l2-compliance

# Input
HEADERS += alsa_stream.h
HEADERS += capture-win-gl.h
HEADERS += capture-win.h
HEADERS += capture-win-qt.h
HEADERS += general-tab.h
HEADERS += qv4l2.h
HEADERS += raw2sliced.h
HEADERS += vbi-tab.h
HEADERS += ../common/v4l2-tpg.h
HEADERS += ../common/v4l2-tpg-colors.h
HEADERS += ../../config.h

SOURCES += capture-win.cpp
SOURCES += capture-win-gl.cpp
SOURCES += capture-win-qt.cpp
SOURCES += ctrl-tab.cpp
SOURCES += general-tab.cpp
SOURCES += qv4l2.cpp
SOURCES += raw2sliced.cpp
SOURCES += tpg-tab.cpp
SOURCES += vbi-tab.cpp
SOURCES += ../v4l2-ctl/v4l2-tpg-core.c
SOURCES += ../v4l2-ctl/v4l2-tpg-colors.c

LIBS += -L$$PWD/../../lib/libv4l2/.libs -lv4l2
LIBS += -L$$PWD/../../lib/libv4lconvert/.libs -lv4lconvert
LIBS += -L$$PWD/../libv4l2util/.libs -lv4l2util 
LIBS += -lrt -ldl -ljpeg
<<<<<<< HEAD
=======
# Input
HEADERS += qv4l2.h general-tab.h v4l2-api.h capture-win.h
SOURCES += qv4l2.cpp general-tab.cpp ctrl-tab.cpp v4l2-api.cpp capture-win.cpp
LIBS += -L../../lib/libv4l2 -lv4l2 -L../../lib/libv4lconvert -lv4lconvert -lrt -L../libv4l2util -lv4l2util -ldl -ljpeg
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

RESOURCES += qv4l2.qrc
