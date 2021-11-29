#include "Shader.h"

#include <iostream>

std::vector<Shader> Shader::m_shaders;

Shader::Shader(const SHADER_TYPE type) : m_type(type), m_shader(0)
{
}

void Shader::load(std::string code)
{
	m_code = code;
}

void Shader::compile()
{
	m_shader = glCreateShader(m_type == SHADER_TYPE::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

	const char* src = m_code.c_str();
	glShaderSource(m_shader, 1, &src, NULL);
	glCompileShader(m_shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(m_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << (m_type == SHADER_TYPE::VERTEX ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::destroy()
{
	glDeleteShader(m_shader);
}

void Shader::use()
{
}

GLuint Shader::GetShader() const
{
	return m_shader;
}
