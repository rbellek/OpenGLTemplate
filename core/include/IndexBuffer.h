#pragma once

class IndexBuffer
{
	friend class Mesh;
private:
	IndexBuffer();
public:
	void load(unsigned int* indices, size_t size);

	void use();

	void draw();
private:
	unsigned int m_IBO;
	unsigned int m_VAO;
};