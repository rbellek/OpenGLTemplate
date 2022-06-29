project(gui VERSION 1.0.0)

add_library(${PROJECT_NAME} 
gui.h
gui.cpp
${CMAKE_SOURCE_DIR}/vendors/imgui/imgui.cpp
${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_demo.cpp
${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_draw.cpp
${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_tables.cpp
${CMAKE_SOURCE_DIR}/vendors/imgui/imgui_widgets.cpp
${CMAKE_SOURCE_DIR}/vendors/imgui/backends/imgui_impl_glfw.cpp
${CMAKE_SOURCE_DIR}/vendors/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendors/imgui)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendors/imgui/backends)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})