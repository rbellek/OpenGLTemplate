#include "ShaderProgram.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram()
{
	m_shaderProgram = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_shaderProgram);
}

void ShaderProgram::attachShader(const Shader& shader) {
	glAttachShader(m_shaderProgram, shader.GetShader());
}

void ShaderProgram::link() {
	glLinkProgram(m_shaderProgram);

	int  success;
	char infoLog[512];
	glGetProgramiv(m_shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGARM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

void ShaderProgram::use() const {
	glUseProgram(m_shaderProgram);
}

void ShaderProgram::setMat4(std::string name, glm::mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
