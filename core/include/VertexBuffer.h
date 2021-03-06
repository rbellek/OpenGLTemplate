#pragma once

class VertexBuffer
{
	friend class Mesh;
private:
	VertexBuffer();
public:
	void load(float* vertices, size_t size);

	void use();

	void draw();
private:
	unsigned int m_VBO;
	unsigned int m_VAO;
};

