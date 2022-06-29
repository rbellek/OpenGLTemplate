#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

Camera::Camera(float screenWidth, float screenHeight)
	: m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{

}

void Camera::lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);

	view = glm::lookAt(position, target, up);
	projection = glm::perspective(glm::radians(60.f), m_screenWidth / m_screenHeight, 0.1f, 100.f);

	m_viewProjection = projection * view;
}

glm::mat4 Camera::getViewProjectionMatrix() const
{
	return m_viewProjection;
}
