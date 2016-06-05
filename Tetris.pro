QT += widgets gui
QT += opengl

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    MainWidget.h \
    Tetris.h \
    GameCanvas.h

SOURCES += \
    main.cpp \
    MainWidget.cpp \
    Tetris.cpp \
    GameCanvas.cpp
