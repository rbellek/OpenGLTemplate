#pragma once

#include <string>

class Mesh {
public:
	void importFrom(std::string file);
	void render();

private:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	unsigned int m_indexCount;
};