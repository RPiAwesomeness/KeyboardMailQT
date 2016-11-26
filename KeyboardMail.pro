#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T00:04:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KeyboardMail
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    smtp/src/emailaddress.cpp \
    smtp/src/mimeattachment.cpp \
    smtp/src/mimecontentformatter.cpp \
    smtp/src/mimefile.cpp \
    smtp/src/mimehtml.cpp \
    smtp/src/mimeinlinefile.cpp \
    smtp/src/mimemessage.cpp \
    smtp/src/mimemultipart.cpp \
    smtp/src/mimepart.cpp \
    smtp/src/mimetext.cpp \
    smtp/src/quotedprintable.cpp \
    smtp/src/smtpclient.cpp \
    message.cpp

HEADERS  += mainwindow.hpp \
    smtp/src/emailaddress.h \
    smtp/src/mimeattachment.h \
    smtp/src/mimecontentformatter.h \
    smtp/src/mimefile.h \
    smtp/src/mimehtml.h \
    smtp/src/mimeinlinefile.h \
    smtp/src/mimemessage.h \
    smtp/src/mimemultipart.h \
    smtp/src/mimepart.h \
    smtp/src/mimetext.h \
    smtp/src/quotedprintable.h \
    smtp/src/smtpclient.h \
    smtp/src/smtpexports.h \
    message.hpp

FORMS    += mainwindow.ui
