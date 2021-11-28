#include "Shader.h"

#include <GL/glew.h>

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

	glShaderSource(vertexShader, 1, (const GLchar* const*)m_code.c_str(), NULL);
	glCompileShader(vertexShader);
}

void Shader::use()
{
}
