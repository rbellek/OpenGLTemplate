#pragma once

#include <iostream>

#include "Shader.h"

#include <glm/mat4x4.hpp>

class ShaderProgram
{
public:
	ShaderProgram();

	~ShaderProgram();

	void attachShader(const Shader& shader);

	void link();

	void use() const;

	void setMat4(std::string name, glm::mat4 mat);


private:
	unsigned int m_shaderProgram;
};

