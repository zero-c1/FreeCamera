cmake_minimum_required(VERSION 3.22)

project(FreeCamera VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_BUILD_TYPE Debug)

set(glfw3_DIR ${CMAKE_SOURCE_DIR}/3rdparty/glfw-3.4/install/lib/cmake/glfw3)
find_package(glfw3 REQUIRED)

add_executable(imgui_demo)

target_sources(imgui_demo PRIVATE
    src/main.cpp
    src/Camera.cpp
    src/PyramidView.cpp
    src/Shader.cpp
    src/utils.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/glad/src/glad.c
)

target_include_directories(imgui_demo PRIVATE "${CMAKE_SOURCE_DIR}/3rdparty/imgui")
target_include_directories(imgui_demo PRIVATE "${CMAKE_SOURCE_DIR}/3rdparty/imgui/backends")
target_include_directories(imgui_demo PRIVATE "${CMAKE_SOURCE_DIR}/3rdparty/glfw-3.4/install/include")
target_include_directories(imgui_demo PRIVATE "${CMAKE_SOURCE_DIR}/3rdparty/glad/include")
target_include_directories(imgui_demo PRIVATE "${CMAKE_SOURCE_DIR}/3rdparty/glm-1.0.1-light")

target_compile_definitions(imgui_demo PRIVATE GLFW_INCLUDE_NONE)

target_link_libraries(imgui_demo PRIVATE glfw)