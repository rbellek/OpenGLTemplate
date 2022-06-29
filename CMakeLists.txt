cmake_minimum_required(VERSION 3.13)

project(SampleApp)

add_subdirectory(gui)

add_library(OpenGLTemplate App.cpp App.h Shader.h Shader.cpp ShaderProgram.h ShaderProgram.cpp VertexBuffer.h VertexBuffer.cpp vendors/glad/src/glad.c)

target_link_libraries(OpenGLTemplate gui)

add_executable(${PROJECT_NAME} main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
if (CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)
endif()
target_include_directories(OpenGLTemplate PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(OpenGLTemplate PRIVATE ${CMAKE_SOURCE_DIR}/vendors/)
target_include_directories(OpenGLTemplate PRIVATE ${CMAKE_SOURCE_DIR}/vendors/imgui)
target_include_directories(OpenGLTemplate PRIVATE ${CMAKE_SOURCE_DIR}/vendors/imgui/backends)
target_include_directories(OpenGLTemplate PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glad/include)
target_include_directories(OpenGLTemplate PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glm)
#target_include_directories(OpenGLTemplate PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glew/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glm)

#--- Find OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
target_link_libraries(OpenGLTemplate ${OpenGL_LIBRARIES})
else()
    message(ERROR " OPENGL not found!")
endif(OPENGL_FOUND)

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

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("${CMAKE_SOURCE_DIR}/vendors/glfw")

target_link_libraries(OpenGLTemplate glfw)

link_directories(${OpenGL_LIBRARY_DIRS})
if(WIN32)
# target_link_libraries(OpenGLTemplate ${CMAKE_SOURCE_DIR}/vendors/glew/lib/Release/x64/glew32s.lib)
target_link_libraries(OpenGLTemplate opengl32.lib)
target_link_libraries(OpenGLTemplate glu32.lib)
endif()

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
#set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) 

add_subdirectory("${CMAKE_SOURCE_DIR}/vendors/assimp")

target_link_libraries(${PROJECT_NAME} OpenGLTemplate gui assimp)