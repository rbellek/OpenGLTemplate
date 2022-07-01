#include "Texture.h"

#define STBI_NO_HDR
#include <stb_image.h>
#include <glad/glad.h>
#include <assert.h>

Texture::Texture(std::string fileName)
{
	int w, h, c;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(("assets/textures/" + fileName).c_str(), &w, &h, &c, 0);
	assert(bytes);
	glGenTextures(1, &m_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy()
{
	glDeleteTextures(1, &m_id);
}

unsigned int Texture::getId() const
{
	return m_id;
}


