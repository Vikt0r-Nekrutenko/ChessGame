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
        bishops.cpp \
        cells.cpp \
        cursor.cpp \
        gameboard.cpp \
        gamemodel.cpp \
        kings.cpp \
        knights.cpp \
        main.cpp \
        pawns.cpp \
        queens.cpp \
        rooks.cpp

HEADERS += \
    bishops.hpp \
    cells.hpp \
    cursor.hpp \
    gameboard.hpp \
    gamemodel.hpp \
    kings.hpp \
    knights.hpp \
    pawns.hpp \
    queens.hpp \
    rooks.hpp
