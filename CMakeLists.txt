cmake_minimum_required(VERSION 3.13)

project(OpenGLTemplate)

add_executable(${PROJECT_NAME} WIN32 main.cpp ${CMAKE_SOURCE_DIR}/simpledrawtext.h ${imgui_SRC})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
if (CMAKE_GENERATOR MATCHES "Visual Studio")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)
endif()
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/imgui)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glad/include)

#--- Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

set(imgui_SRC 
"${CMAKE_SOURCE_DIR}/vendors/imgui/imconfig.h",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imgui.cpp",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imgui.h",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_demo.cpp",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_draw.cpp",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_impl_glfw.cpp",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_impl_glfw.h",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_impl_opengl3.cpp",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_impl_opengl3.h",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_internal.h",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_tables.cpp",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_widgets.cpp",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imstb_rectpack.h",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imstb_textedit.h",
"${CMAKE_SOURCE_DIR}/vendors/imgui/imstb_truetype.h")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("${CMAKE_SOURCE_DIR}/vendors/glfw")

target_link_libraries(${PROJECT_NAME} glfw)