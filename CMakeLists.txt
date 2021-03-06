#[[
This file is part of waft
Copyright (C) 2020 Christopher Gundler <christopher@gundler.de>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
#]]

cmake_minimum_required(VERSION 3.15)
project(waft)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif ()

set(Qt5_Components Widgets Multimedia Test)
find_package(Qt5 COMPONENTS ${Qt5_Components} REQUIRED)

list(TRANSFORM Qt5_Components PREPEND "Qt5::")
add_library(waft_src src/model/Ellipse.cpp src/model/Ellipse.h src/view/AnnotationWidget.cpp src/view/AnnotationWidget.h src/model/Samples.h src/model/samples/Files.cpp src/model/samples/Files.h src/model/Sample.cpp src/model/Sample.h src/view/util/FileList.cpp src/view/util/FileList.h src/model/Samples.cpp src/view/InputPage.cpp src/view/InputPage.h src/view/Wizard.cpp src/view/Wizard.h src/view/AnnotationPage.cpp src/view/AnnotationPage.h src/view/OutputPage.cpp src/view/OutputPage.h src/view/util/FileSelector.h src/view/util/FileSelector.cpp src/model/samples/SavedAnnotations.cpp src/model/samples/SavedAnnotations.h src/view/inputs/Tsv.cpp src/view/inputs/Tsv.h src/view/inputs/Input.h src/view/inputs/MultiInput.cpp src/view/inputs/MultiInput.h src/view/inputs/Images.cpp src/view/inputs/Images.h src/view/util/AspectRatioWidget.cpp src/view/util/AspectRatioWidget.h)
target_link_libraries(waft_src ${Qt5_Components})

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    MESSAGE(STATUS "Build tests")
    add_executable(waft src/main.cpp src/Tests.cpp src/Tests.h)
    add_definitions(-DBUILD_TESTING)
    target_link_libraries(waft waft_src)
    add_test(NAME WaftTest COMMAND waft)
endif ()

# Set the platform-dependent flags
if (WIN32)
    set(Executable_Flags "WIN32")
elseif (APPLE)
    set(Executable_Flags "MACOSX_BUNDLE")
endif ()

add_executable(waft ${Executable_Flags} src/main.cpp)
target_link_libraries(waft waft_src)

# Deploy additional files on Windows and macOS
get_target_property(QMake_Executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(Qt_Bin_Dir "${QMake_Executable}" DIRECTORY)
if (WIN32)
    find_program(Win_Deploy_Executable windeployqt HINTS "${Qt_Bin_Dir}")

    add_custom_command(TARGET waft POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E
            env PATH="${Qt_Bin_Dir}" "${Win_Deploy_Executable}"
            --verbose 1
            $<$<CONFIG:Debug>:--no-compiler-runtime>
            $<IF:$<CONFIG:Debug>,--debug,--release>
            \"$<TARGET_FILE:waft>\"
            COMMENT "Deploying Qt for Microsoft Windows..."
            )
elseif (APPLE)
    find_program(Mac_Deploy_Executable macdeployqt HINTS "${Qt_Bin_Dir}")

    add_custom_command(TARGET waft POST_BUILD
            COMMAND "${Mac_Deploy_Executable}" "$<TARGET_FILE_DIR:waft>/../.." -always-overwrite
            COMMENT "Deploying Qt for macOS..."
            )
endif ()