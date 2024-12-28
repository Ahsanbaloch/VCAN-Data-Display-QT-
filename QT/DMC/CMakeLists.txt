set(CMAKE_PREFIX_PATH "~/Qt/6.8.0/gcc_64/lib/cmake")
set(CMAKE_BUILD_TYPE Debug)


cmake_minimum_required(VERSION 3.16)

project(DMC VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick SerialBus SerialPort)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appDMC
    main.cpp
)

set(QML_IMPORT_PATH "${CMAKE_PREFIX_PATH}/qml" CACHE STRING "" FORCE)
set(QML_DESIGNER_IMPORT_PATH "${CMAKE_PREFIX_PATH}/qml" CACHE STRING "" FORCE)


qt_add_qml_module(appDMC
    URI DMC
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES cans_info.h cans_info.cpp
        SOURCES candatamodel.h candatamodel.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appDMC PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appDMC
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appDMC
    PRIVATE Qt6::Quick Qt6::SerialBus Qt6::SerialPort
)

include(GNUInstallDirs)
install(TARGETS appDMC
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
