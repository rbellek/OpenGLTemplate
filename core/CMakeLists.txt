cmake_minimum_required(VERSION 3.18)

project(core)

add_library(${PROJECT_NAME} 
	include/App.h 
	include/Shader.h 
	include/ShaderProgram.h 
	include/VertexBuffer.h 
	include/IndexBuffer.h 
	include/Mesh.h 
	include/Camera.h
	include/Texture.h
	src/App.cpp 
	src/ShaderProgram.cpp 
	src/Shader.cpp 
	src/VertexBuffer.cpp
	src/IndexBuffer.cpp
	src/Mesh.cpp
	src/Camera.cpp
	src/Texture.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/imgui)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/imgui/backends)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glad/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/stb)
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glew/include)

target_link_libraries(${PROJECT_NAME} gui assimp glfw glad ${OpenGL_LIBRARIES})