#include "App.h"

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

	const double fpsLimit = 1.0 / 60.0;
	double lastUpdateTime = 0;  // number of seconds since the last loop
	double lastFrameTime = 0;   // number of seconds since the last frame

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_window))
	{
		const double now = glfwGetTime();
		double deltaTime = now - lastUpdateTime;

		if ((now - lastFrameTime) >= fpsLimit)
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			render();

			/* Poll for and process events */
			glfwPollEvents();

			/* Swap front and back buffers */
			glfwSwapBuffers(m_window);

			// only set lastFrameTime when you actually draw something
			lastFrameTime = now;
		}
		// set lastUpdateTime every iteration
		lastUpdateTime = now;
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

	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, 8. / 6, 1, 50);
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);

	return true;
}

void App::render()
{
}
