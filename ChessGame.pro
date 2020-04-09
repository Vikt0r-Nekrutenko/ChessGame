TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += UNICODE
SOURCES += \
        ChessBoard.cpp \
        ChessModel.cpp \
        Pieces.cpp \
        main.cpp

HEADERS += \
    ChessBoard.h \
    ChessModel.h \
    Pieces.h
