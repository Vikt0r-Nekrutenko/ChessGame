TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L$$PWD/../stf/release/ -lstf

INCLUDEPATH += $$PWD/../stf/ \
                $$PWD/../stf/smv \
                $$PWD/../stf/sdb \
                $$PWD/model/headers \

DEPENDPATH += $$PWD/../stf/ \
                $$PWD/../stf/smv \
                $$PWD/../stf/sdb \
                $$PWD/model/headers \

SOURCES += \
        main.cpp \
    model/sources/bishops.cpp \
    model/sources/cells.cpp \
    model/sources/cursor.cpp \
    model/sources/gameboard.cpp \
    model/sources/gamemodel.cpp \
    model/sources/kings.cpp \
    model/sources/knights.cpp \
    model/sources/pawns.cpp \
    model/sources/queens.cpp \
    model/sources/rooks.cpp

HEADERS += \
    model/headers/bishops.hpp \
    model/headers/cells.hpp \
    model/headers/cursor.hpp \
    model/headers/gameboard.hpp \
    model/headers/gamemodel.hpp \
    model/headers/kings.hpp \
    model/headers/knights.hpp \
    model/headers/pawns.hpp \
    model/headers/queens.hpp \
    model/headers/rooks.hpp
