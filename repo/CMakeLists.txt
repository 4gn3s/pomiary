CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(pomiary)

SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_CXX_FLAGS "-Wall")

FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})

SET( P_SRC
                MainWindow.h
                MyWidget.h
)

SET( P_UI
)
SET( P_RES
)

QT4_WRAP_CPP(P_MOC_CPP ${P_SRC})
QT4_WRAP_UI(P_UI_CPP ${P_UI})
QT4_ADD_RESOURCES(P_RES_H ${P_RES})

ADD_SUBDIRECTORY(synektik)

ADD_DEFINITIONS(${synektik_DEF})

INCLUDE_DIRECTORIES( . ${synektik_INC})

SET( P_SRC
        main.cpp
        MainWindow.cpp
        MyWidget.cpp
        ${P_MOC_CPP}
        ${P_UI_CPP}
        ${P_RES_H}
)

SET( P_LIB
        ${QT_LIBRARIES}
)

ADD_EXECUTABLE(pomiary ${P_SRC})
TARGET_LINK_LIBRARIES(pomiary synektik_dcmimage ${P_LIB})
INSTALL_TARGETS( /bin pomiary)
