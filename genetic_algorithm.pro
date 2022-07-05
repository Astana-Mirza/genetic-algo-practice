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
GENETIC_DIR  = genetic
COMMON_DIR   = common

INCLUDEPATH += $${INCLUDE_DIR}

SOURCES += \
    $${SOURCE_DIR}/main.cpp \
    $${SOURCE_DIR}/$${GUI_DIR}/settings_dialog.cpp \
    $${SOURCE_DIR}/$${GUI_DIR}/main_window.cpp \
    $${SOURCE_DIR}/$${GUI_DIR}/enter_data.cpp \
    $${SOURCE_DIR}/$${GUI_DIR}/data.cpp \
    $${SOURCE_DIR}/$${LOGGER_DIR}/log.cpp \
    $${SOURCE_DIR}/$${LOGGER_DIR}/console_logger.cpp \
    $${SOURCE_DIR}/$${LOGGER_DIR}/file_logger.cpp \
    $${SOURCE_DIR}/$${LOGGER_DIR}/tab_logger.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/gene.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/individual.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/packer.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/order_crossover.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/separator_crossover.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/order_mutator.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/panmixing_parent_selector.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/roulette_parent_selector.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/truncation_selector.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/elite_selector.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/iter_stop_condition.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/fitness_stop_condition.cpp \
    $${SOURCE_DIR}/$${GENETIC_DIR}/distance_stop_condition.cpp \
    $${SOURCE_DIR}/$${COMMON_DIR}/rectangle_representation.cpp \
    $${SOURCE_DIR}/$${COMMON_DIR}/individual_representation.cpp

HEADERS += \
    $${INCLUDE_DIR}/$${ABSTRACT_DIR}/ilogger.h \
    $${INCLUDE_DIR}/$${ABSTRACT_DIR}/istop_condition.h \
    $${INCLUDE_DIR}/$${ABSTRACT_DIR}/icrossover.h \
    $${INCLUDE_DIR}/$${ABSTRACT_DIR}/imutator.h \
    $${INCLUDE_DIR}/$${ABSTRACT_DIR}/iparent_selector.h \
    $${INCLUDE_DIR}/$${ABSTRACT_DIR}/iparent_selector.h \
    $${INCLUDE_DIR}/$${ABSTRACT_DIR}/iselector.h \
    $${INCLUDE_DIR}/$${GUI_DIR}/main_window.h \
    $${INCLUDE_DIR}/$${GUI_DIR}/settings_dialog.h \
    $${INCLUDE_DIR}/$${GUI_DIR}/settings.h \
    $${INCLUDE_DIR}/$${GUI_DIR}/enter_data.h \
    $${INCLUDE_DIR}/$${GUI_DIR}/data.h \
    $${INCLUDE_DIR}/$${LOGGER_DIR}/log.h \
    $${INCLUDE_DIR}/$${LOGGER_DIR}/console_logger.h \
    $${INCLUDE_DIR}/$${LOGGER_DIR}/file_logger.h \
    $${INCLUDE_DIR}/$${LOGGER_DIR}/tab_logger.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/gene.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/individual.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/packer.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/order_crossover.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/separator_crossover.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/order_mutator.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/panmixing_parent_selector.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/roulette_parent_selector.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/panmixing_parent_selector.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/roulette_parent_selector.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/truncation_selector.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/elite_selector.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/result.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/iter_stop_condition.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/fitness_stop_condition.h \
    $${INCLUDE_DIR}/$${GENETIC_DIR}/distance_stop_condition.h \
    $${INCLUDE_DIR}/$${COMMON_DIR}/rectangle_representation.h \
    $${INCLUDE_DIR}/$${COMMON_DIR}/individual_representation.h


FORMS += \
    $${FORM_DIR}/main_window.ui \
    $${FORM_DIR}/settings_dialog.ui \
    $${FORM_DIR}/enter_data.ui

TRANSLATIONS += \
    $${TR_DIR}/genetic_algorithm_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
