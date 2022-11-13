TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L$$PWD/../stf/release/ -lstf

INCLUDEPATH += $$PWD/../stf/ \
                $$PWD/../stf/smv \
                $$PWD/../stf/sdb \


DEPENDPATH += $$PWD/../stf/ \
                $$PWD/../stf/smv \
                $$PWD/../stf/sdb \

SOURCES += \
        cells.cpp \
        gameboard.cpp \
        gamemodel.cpp \
        main.cpp \
        pawns.cpp \
        pieces.cpp \
        players.cpp

HEADERS += \
    cells.hpp \
    gameboard.hpp \
    gamemodel.hpp \
    pawns.hpp \
    pieces.hpp \
    players.hpp
