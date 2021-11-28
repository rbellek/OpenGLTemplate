#include "App.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

App::App(std::string title, uint32_t width, uint32_t height)
	: m_title(title), 
	m_window(nullptr),
	m_width(width),
	m_height(height)
{
}

bool App::Run()
{
	if (!init())
		return false;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return true;
}

bool App::init()
{
	/* Initialize the library */
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to load OpenGL and its extensions" << std::endl;
		return EXIT_FAILURE;
	}

	glClearColor(0.4f, 0.3f, 0.4f, 0.0f);

	return true;
}

void App::render()
{
}
