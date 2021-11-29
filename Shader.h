#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>

enum class SHADER_TYPE {
	VERTEX, FRAGMENT
};

class Shader {
public:
	void load(std::string code);
	void compile();
	void use();
	GLuint GetShader() const;
	static Shader CreateShader(const SHADER_TYPE type) {
		Shader shader{ type };
		m_shaders.push_back(shader);
		return shader;
	}
private:
	Shader(const SHADER_TYPE type);
	void destroy();

	std::string m_code;
	SHADER_TYPE m_type;
	GLuint m_shader;
	static std::vector<Shader> m_shaders;
};