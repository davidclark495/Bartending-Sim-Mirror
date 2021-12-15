QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    box2ddialog.cpp \
    buttondata.cpp \
    cocktail.cpp \
    cocktailwidget.cpp \
    infodialog.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp

HEADERS += \
    box2ddialog.h \
    buttondata.h \
    cocktail.h \
    cocktailwidget.h \
    infodialog.h \
    mainwindow.h \
    model.h \
    mainwindow.h

FORMS += \
    box2ddialog.ui \
    infodialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    Images/PubQuiz.jpg \
    Images/Quiz.jpg \
    Images/Reference.jpg \
    Images/Teach.jpg

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/box2d-master/include/box2d/win32/ -lbox2d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/box2d-master/include/box2d/win32/ -lbox2d
else:unix: LIBS += -L$$PWD/box2d-master/include/box2d/macx/ -lbox2d

INCLUDEPATH += $$PWD/box2d-master/include
DEPENDPATH += $$PWD/box2d-master/include

