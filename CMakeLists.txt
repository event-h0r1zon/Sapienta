cmake_minimum_required(VERSION 3.10)
project(Velaris) # Give your project a name

# Need C++17 for a modern project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
)

add_executable(velaris
    velaris/src/main.cpp
    velaris/src/render/VectorRendererWidget.cpp
    velaris/src/ui/MainWindow.cpp
)

target_include_directories(velaris
    PRIVATE
        ~/libs/eigen-5.0.0
        velaris/include
)
target_link_libraries(velaris PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)