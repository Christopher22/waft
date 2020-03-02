cmake_minimum_required(VERSION 3.15)
project(waft)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif ()

set(Qt5_Components Widgets Multimedia)
find_package(Qt5 COMPONENTS ${Qt5_Components} REQUIRED)

list(TRANSFORM Qt5_Components PREPEND "Qt5::")
add_executable(waft src/main.cpp src/model/Ellipse.cpp src/model/Ellipse.h src/view/AnnotationWidget.cpp src/view/AnnotationWidget.h src/view/util/AspectRatioPixmapLabel.cpp src/view/util/AspectRatioPixmapLabel.h src/model/Samples.h src/model/samples/Files.cpp src/model/samples/Files.h src/model/Sample.cpp src/model/Sample.h src/view/InputWidget.cpp src/view/InputWidget.h src/model/Samples.cpp src/view/InputPage.cpp src/view/InputPage.h src/view/Wizard.cpp src/view/Wizard.h src/view/AnnotationPage.cpp src/view/AnnotationPage.h src/view/OutputPage.cpp src/view/OutputPage.h src/view/util/FileSelector.h src/view/util/FileSelector.cpp)
target_link_libraries(waft ${Qt5_Components})

IF (WIN32)
    # On Windows, deploy all required DLLs automatically
    get_target_property(QMake_Executable Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(Qt_Bin_Dir "${QMake_Executable}" DIRECTORY)
    find_program(Win_Deploy_Executable windeployqt HINTS "${Qt_Bin_Dir}")

    add_custom_command(TARGET waft POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E
            env PATH="${Qt_Bin_Dir}" "${Win_Deploy_Executable}"
            --verbose 0
            --no-compiler-runtime
            $<IF:$<CONFIG:Debug>,--debug,--release>
            \"$<TARGET_FILE:waft>\"
            COMMENT "Deploying Qt..."
            )

endif ()