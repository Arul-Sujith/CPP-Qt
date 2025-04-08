cmake_minimum_required(VERSION 3.14)
project(CutterMock)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

# Find Qt5
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Find Capstone
find_package(PkgConfig REQUIRED)
pkg_check_modules(CAPSTONE REQUIRED capstone)

# Executable and sources
add_executable(CutterMock
    main.cpp
    MainWindow.cpp MainWindow.h
    Disassembler.cpp Disassembler.h
    DisassemblyView.cpp DisassemblyView.h
    DisassemblyHighlighter.cpp DisassemblyHighlighter.h
)

# Include Capstone headers
target_include_directories(CutterMock PRIVATE ${CAPSTONE_INCLUDE_DIRS})

# Link Qt5 and Capstone libraries
target_link_libraries(CutterMock Qt5::Widgets ${CAPSTONE_LIBRARIES})
