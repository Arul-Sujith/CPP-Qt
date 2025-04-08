cmake_minimum_required(VERSION 3.14)
project(DockHexApp)

set(CMAKE_CXX_STANDARD 17)

# Enable Qt MOC, RCC, and UIC processing
set(CMAKE_AUTOMOC ON)         # ✅ Automatically run moc
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Add sources and headers
set(SOURCES
    main.cpp
    MainWindow.cpp
    HexDumpWidget.cpp
)

set(HEADERS
    MainWindow.h
    HexDumpWidget.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
