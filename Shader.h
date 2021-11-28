#pragma once

#include <string>

class Shader {
public:
	Shader();
	Shader(std::string code);
	void load(std::string code);
	void compile();
	void use();
private:
	std::string m_code;
};