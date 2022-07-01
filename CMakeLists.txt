cmake_minimum_required(VERSION 3.18)

project(SampleApp)

#--- Find OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
else()
    message(ERROR " OPENGL not found!")
endif(OPENGL_FOUND)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("${CMAKE_SOURCE_DIR}/vendors/glfw")
add_subdirectory("${CMAKE_SOURCE_DIR}/vendors/glad")

add_subdirectory(gui)

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
#set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) 

add_subdirectory("${CMAKE_SOURCE_DIR}/vendors/assimp")

add_subdirectory(core)

add_executable(${PROJECT_NAME} main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
if (CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endif()


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glm)



#--- Find GLEW
#if(NOT WIN32)
#find_package(GLEW REQUIRED)
#if(GLEW_FOUND)
#include_directories(${GLEW_INCLUDE_DIRS})
#link_libraries(${GLEW_LIBRARIES})
#else()
#    message(ERROR "GLEW not found!")
#endif(GLEW_FOUND)
#endif()


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


target_link_libraries(${PROJECT_NAME} core gui)