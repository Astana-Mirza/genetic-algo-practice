QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 lrelease embed_translations

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR      = $${PWD}/build
OBJECTS_DIR  = $${PWD}/obj
MOC_DIR      = $${PWD}/obj
UI_DIR       = $${PWD}/obj
RCC_DIR      = $${PWD}/obj

TR_DIR       = translations
INCLUDE_DIR  = include
SOURCE_DIR   = src
FORM_DIR     = forms

ABSTRACT_DIR = abstract
GUI_DIR      = gui
LOGGER_DIR   = logger

INCLUDEPATH += $${INCLUDE_DIR}

SOURCES += \
    $${SOURCE_DIR}/$${GUI_DIR}/settings_dialog.cpp \
    $${SOURCE_DIR}/main.cpp \
    $${SOURCE_DIR}/$${GUI_DIR}/main_window.cpp \
    $${SOURCE_DIR}/$${LOGGER_DIR}/log.cpp \
    $${SOURCE_DIR}/$${LOGGER_DIR}/console_logger.cpp \
    $${SOURCE_DIR}/$${LOGGER_DIR}/file_logger.cpp \
    $${SOURCE_DIR}/$${LOGGER_DIR}/tab_logger.cpp

HEADERS += \
    $${INCLUDE_DIR}/$${ABSTRACT_DIR}/ilogger.h \
    $${INCLUDE_DIR}/$${GUI_DIR}/main_window.h \
    $${INCLUDE_DIR}/$${GUI_DIR}/settings_dialog.h \
    $${INCLUDE_DIR}/$${GUI_DIR}/settings.h \
    $${INCLUDE_DIR}/$${LOGGER_DIR}/log.h \
    $${INCLUDE_DIR}/$${LOGGER_DIR}/console_logger.h \
    $${INCLUDE_DIR}/$${LOGGER_DIR}/file_logger.h \
    $${INCLUDE_DIR}/$${LOGGER_DIR}/tab_logger.h

FORMS += \
    $${FORM_DIR}/main_window.ui \
    $${FORM_DIR}/settings_dialog.ui

TRANSLATIONS += \
    $${TR_DIR}/genetic_algorithm_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
