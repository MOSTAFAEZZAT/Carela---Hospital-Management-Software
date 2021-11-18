QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets designer printsupport


CONFIG += c++11 designer

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mysqldatabase.cpp \
    profile3.cpp \
    showingdata.cpp

HEADERS += \
    mainwindow.h \
    mysqldatabase.h \
    profile3.h \
    showingdata.h

FORMS += \
    mainwindow.ui \
    profile3.ui \
    showingdata.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
