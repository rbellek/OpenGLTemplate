#pragma once

#include <glad/glad.h>
#include <iostream>

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram()
	{
		m_shaderProgram = glCreateProgram();
	}

	~ShaderProgram()
	{
		glDeleteProgram(m_shaderProgram);
	}

	void attachShader(const Shader& shader) {
		glAttachShader(m_shaderProgram, shader.GetShader());
	}

	void link() {
		glLinkProgram(m_shaderProgram);

		int  success;
		char infoLog[512];
		glGetProgramiv(m_shaderProgram, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::PROGARM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}

	void use() const {
		glUseProgram(m_shaderProgram);
	}

private:
	GLuint m_shaderProgram;
};

