cmake_minimum_required(VERSION 3.18)

project(core)

add_library(${PROJECT_NAME} 
	src/App.cpp 
	include/App.h 
	include/Shader.h 
	src/Shader.cpp 
	include/ShaderProgram.h 
	src/ShaderProgram.cpp 
	include/VertexBuffer.h 
	src/VertexBuffer.cpp
	"${CMAKE_SOURCE_DIR}/vendors/glad/src/glad.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/imgui)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/imgui/backends)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glad/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glm)
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glew/include)

target_link_libraries(${PROJECT_NAME} gui assimp glfw ${OpenGL_LIBRARIES})