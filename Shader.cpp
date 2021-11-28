#include "Shader.h"

#include <glad/glad.h>

Shader::Shader()
{
}

Shader::Shader(std::string code) : m_code(code)
{

}

void Shader::load(std::string code)
{
	m_code = code;
}

void Shader::compile()
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const char* src = m_code.c_str();
	glShaderSource(vertexShader, 1, &src, NULL);
	glCompileShader(vertexShader);
}

void Shader::use()
{
}
