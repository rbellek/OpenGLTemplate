#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
public:
	Camera(float screenWidth, float screenHeight);
	void lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 getViewProjectionMatrix() const;

	void processInputs(struct GLFWwindow* window);
	glm::vec3 getPosition() const;
private:
	void process();

	float m_screenWidth;
	float m_screenHeight;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	glm::mat4 m_viewProjection;
};