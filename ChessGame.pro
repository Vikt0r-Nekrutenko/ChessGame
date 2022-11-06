TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L$$PWD/../stf/release/ -lstf

INCLUDEPATH += $$PWD/../stf/
                $$PWD/../stf/smv
                $$PWD/../stf/sdb


DEPENDPATH += $$PWD/../stf/
                $$PWD/../stf/smv
                $$PWD/../stf/sdb

SOURCES += \
        Bishop.cpp \
        ChessBoard.cpp \
        ChessModel.cpp \
        King.cpp \
        Knight.cpp \
        ModelBackup.cpp \
        Pawn.cpp \
        Piece.cpp \
        Queen.cpp \
        Rook.cpp \
        main.cpp

HEADERS += \
    Bishop.h \
    ChessBoard.h \
    ChessModel.h \
    GrigParts.h \
    King.h \
    Knight.h \
    ModelBackup.h \
    Pawn.h \
    Piece.h \
    Queen.h \
    Rook.h
