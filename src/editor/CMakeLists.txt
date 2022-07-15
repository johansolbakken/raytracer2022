set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /Users/johansolbakken/qt/6.2.4/macos C:/Qt/6.3.1/msvc2019_64)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        renderer.cpp
        renderer.h
        propertiespanel.h propertiespanel.cpp
        performancelist.h performancelist.cpp
        camerawidget.h camerawidget.cpp
        tripplefloatinputwidget.h tripplefloatinputwidget.cpp
        titledfloattextedit.cpp titledfloattextedit.h
        rendererpropertieswidget.h rendererpropertieswidget.cpp
        )

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(editor
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET editor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(editor SHARED
                ${PROJECT_SOURCES}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(editor
                ${PROJECT_SOURCES}
                )
    endif ()
endif ()

target_link_libraries(editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets raytracer)

target_include_directories(editor PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)

set_target_properties(editor
        PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER editor.johansolbakken.no
        MACOSX_BUNDLE_BUNDLE_VERSION 1
        MACOSX_BUNDLE_SHORT_VERSION_STRING 1.0
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(editor)
endif ()
