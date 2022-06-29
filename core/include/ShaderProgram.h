#pragma once

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
	unsigned int m_shaderProgram;
};

