QT       += core xml gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = dwNodeEditor
#DEPENDPATH += . tmp/rcc/debug_shared tmp/rcc/release_shared
DEPENDPATH += .
INCLUDEPATH += . src/Impl src/ExampleApp

# Input
HEADERS += src/Impl/diagramscene.h \
           src/ExampleApp/mainwindow.h \
           src/Impl/nodeconnection.h \
           src/Impl/nodeconnector.h \
           src/Impl/nodeitem.h \
           src/ExampleApp/stylesheeteditor.h \
           src/ExampleApp/windowflagseditor.h
FORMS    = src/ExampleApp/stylesheeteditor.ui
SOURCES += src/Impl/diagramscene.cpp \
           src/ExampleApp/main.cpp \
           src/ExampleApp/mainwindow.cpp \
           src/Impl/nodeconnection.cpp \
           src/Impl/nodeconnector.cpp \
           src/Impl/nodeitem.cpp \
           src/ExampleApp/stylesheeteditor.cpp \
           src/ExampleApp/windowflagseditor.cpp
RESOURCES += dwNodeEditor1.qrc
