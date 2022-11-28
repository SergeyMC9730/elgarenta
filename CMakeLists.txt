cmake_minimum_required(VERSION 3.5)

project(elgarenta)

add_library(libimgui imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/imgui.cpp imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp)
add_library(libelgarenta elgarenta.cpp)

target_link_libraries(libimgui GL glfw)
target_link_libraries(libelgarenta PUBLIC libimgui pthread dl)

add_executable(example_square example_square.cpp)
add_executable(example_pipeline example_pipeline.cpp bmp.c)

include_directories(example_square PRIVATE imgui imgui/backends ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(example_square PUBLIC libelgarenta)
target_link_libraries(example_pipeline PUBLIC libelgarenta)