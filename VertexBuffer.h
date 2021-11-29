#pragma once

class VertexBuffer
{
public:
	VertexBuffer();

	void load(float* vertices, size_t size);

	void use();

	void draw();
private:
	unsigned int m_VBO;
	unsigned int m_VAO;
};

