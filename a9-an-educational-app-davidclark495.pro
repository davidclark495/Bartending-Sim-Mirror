QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    amountdialog.cpp \
    buttondata.cpp \
    cocktail.cpp \
    infodialog.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp

HEADERS += \
    amountdialog.h \
    buttondata.h \
    cocktail.h \
    infodialog.h \
    mainwindow.h \
    model.h \
    mainwindow.h

FORMS += \
    amountdialog.ui \
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
