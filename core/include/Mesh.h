#pragma once

#include <string>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Mesh {
public:
	Mesh();
	void importFrom(std::string file);
	void render();
	void translate(glm::vec3 dir);
	void rotate(glm::vec3 dir, float angle);
	void scale(glm::vec3 dir);

	glm::mat4 getModel() const;
	void reset();

	glm::vec3 leftBottom, rightTop;
private:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	unsigned int m_indexCount;
	glm::mat4 m_model;
};