#pragma once

#include <iostream>

#include "Shader.h"

#include <glm/mat4x4.hpp>

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(std::string fileName);

	~ShaderProgram();

	void attachShader(const Shader& shader);

	void link();

	void use() const;

	void setVec3(std::string name, glm::vec3 vec);
	void setMat4(std::string name, glm::mat4 mat);


private:
	void init();

	unsigned int m_shaderProgram;
};

