#include "Camera.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <glfw/glfw3.h>

Camera::Camera(float screenWidth, float screenHeight)
	: m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{

}

void Camera::lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
	m_position = position;
	m_forward = glm::normalize(target - position);
	m_up = up;

	process();
}

glm::mat4 Camera::getViewProjectionMatrix() const
{
	return m_viewProjection;
}

void Camera::processInputs(GLFWwindow* window)
{
	constexpr float speed = 0.1f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_position += m_forward * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_position -= m_forward * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_position += glm::normalize(glm::cross(m_forward, m_up)) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_position -= glm::normalize(glm::cross(m_forward, m_up)) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_position += m_up * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_position -= m_up * speed;
	}

	static bool firstClick = true;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if (firstClick) {
			glfwSetCursorPos(window, (m_screenWidth / 2), (m_screenHeight / 2));
			firstClick = false;
		}

		double mouseX, mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		constexpr float sensitivity = 100.f;
		float rotX = sensitivity * (float)(mouseY - (m_screenHeight / 2)) / m_screenHeight;
		float rotY = sensitivity * (float)(mouseX - (m_screenWidth / 2)) / m_screenWidth;

		glm::vec3 newForward = glm::rotate(m_forward, glm::radians(-rotX), glm::normalize(glm::cross(m_forward, m_up)));

		if (abs(glm::angle(newForward, m_up) - glm::radians(90.f)) <= glm::radians(85.f))
		{
			m_forward = newForward;
		}

		m_forward = glm::rotate(m_forward, glm::radians(-rotY), m_up);

		glfwSetCursorPos(window, (m_screenWidth / 2), (m_screenHeight / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		firstClick = true;
	}

	process();
}

glm::vec3 Camera::getPosition() const
{
	return m_position;
}

void Camera::process()
{
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	view = glm::lookAt(m_position, m_position + m_forward, m_up);
	projection = glm::perspective(glm::radians(60.f), m_screenWidth / m_screenHeight, 0.1f, 100.f);

	m_viewProjection = projection * view;
}
