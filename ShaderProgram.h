#pragma once

#include <glad/glad.h>
#include <iostream>

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();

	~ShaderProgram();

	void attachShader(const Shader& shader);

	void link();

	void use() const;

private:
	GLuint m_shaderProgram;
};

