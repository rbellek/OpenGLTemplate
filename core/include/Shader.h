#pragma once

#include <string>
#include <vector>

enum class SHADER_TYPE {
	VERTEX, FRAGMENT
};

class Shader {
public:
	void load(std::string code);
	void loadFromFile(std::string fileName);
	void compile();
	void use();
	unsigned int GetShader() const;
	static Shader CreateShader(const SHADER_TYPE type);
private:
	Shader(const SHADER_TYPE type);
	void destroy();

	std::string m_code;
	SHADER_TYPE m_type;
	unsigned int m_shader;
	static std::vector<Shader> m_shaders;
};