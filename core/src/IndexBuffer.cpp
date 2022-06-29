#include "IndexBuffer.h"

#include <glad/glad.h>

IndexBuffer::IndexBuffer()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_IBO);
}

void IndexBuffer::load(unsigned int* indices, size_t size) {
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void IndexBuffer::use() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void IndexBuffer::draw() {
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
