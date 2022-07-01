#pragma once

#include <string>

class Texture {
public:
	Texture(std::string fileName);
	void bind();
	void unbind();
	void destroy();

	unsigned int getId() const;
private:
	unsigned int m_id;
};