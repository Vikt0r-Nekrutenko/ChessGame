TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += UNICODE
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
