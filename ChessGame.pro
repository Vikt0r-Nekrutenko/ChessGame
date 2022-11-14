TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L$$PWD/../stf/release/ -lstf

INCLUDEPATH += $$PWD/../stf/ \
                $$PWD/../stf/smv \
                $$PWD/../stf/sdb \
                $$PWD/model/headers \
                $$PWD/views/headers \

DEPENDPATH += $$PWD/../stf/ \
                $$PWD/../stf/smv \
                $$PWD/../stf/sdb \
                $$PWD/model/headers \
                $$PWD/views/headers \

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
    model/sources/rooks.cpp \
    views/sources/closeview.cpp \
    views/sources/endview.cpp \
    views/sources/gameview.cpp \
    views/sources/menuview.cpp \
    views/sources/pausemenuview.cpp \
    views/sources/storyview.cpp

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
    model/headers/rooks.hpp \
    views/headers/closeview.hpp \
    views/headers/endview.hpp \
    views/headers/gameview.hpp \
    views/headers/menuview.hpp \
    views/headers/pausemenuview.hpp \
    views/headers/storyview.hpp

DISTFILES += \
    sprs/end.spr \
    sprs/logo.spr \
    sprs/menu.spr \
    sprs/pause_menu.spr \
    sprs/sboard.spr \
    sprs/stats.spr
