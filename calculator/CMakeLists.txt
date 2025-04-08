cmake_minimum_required(VERSION 3.14)
project(QtCalculator)

set(CMAKE_CXX_STANDARD 17)

# Enable Qt meta-object compiler
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Qml REQUIRED)

add_executable(calculator
    main.cpp
    calculator.cpp
    calculator.h
)

target_link_libraries(calculator Qt5::Widgets Qt5::Qml)
