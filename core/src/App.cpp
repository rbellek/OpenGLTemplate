#include "App.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Mesh.h"
#include "Camera.h"

App::App(std::string title, uint32_t width, uint32_t height)
	: m_title(title),
	m_width(width),
    m_height(height),
    m_window(nullptr)
{
	init();
}

bool App::Run()
{
	const double fpsLimit = 1.0 / 60.0;
    //double lastUpdateTime = 0;  // number of seconds since the last loop
	double lastFrameTime = 0;   // number of seconds since the last frame

	Mesh m;
	m.importFrom("assets/models/box.obj");



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_window))
	{
		const double now = glfwGetTime();
        //double deltaTime = now - lastUpdateTime;

		if ((now - lastFrameTime) >= fpsLimit)
		{
			/* Render here */
			glClearColor(0.f, 0.f, 0.f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			render();
			m.render();

			//vb.draw();
			//m_gui.render();

			/* Poll for and process events */
			glfwPollEvents();

			/* Swap front and back buffers */
			glfwSwapBuffers(m_window);

			// only set lastFrameTime when you actually draw something
			lastFrameTime = now;
		}
		// set lastUpdateTime every iteration
        //lastUpdateTime = now;
	}

	glfwDestroyWindow(m_window);
	glfwTerminate();

	return true;
}

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

bool App::init()
{
	glfwSetErrorCallback(glfw_error_callback);
	/* Initialize the library */
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			// make sure the viewport matches the new window dimensions; note that width and 
			// height will be significantly larger than specified on retina displays.
			glViewport(0, 0, width, height);
		});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

    //glMatrixMode(GL_PROJECTION);
    //gluPerspective(45, 8. / 6, 1, 50);
    //gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
    //glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);

    // Main loop
	m_gui.init(m_window);

	glClearColor(0, 0, 0, 1);

	return true;
}

void App::render()
{
}

GLFWwindow* App::getWindow() const
{
	return m_window;
}
