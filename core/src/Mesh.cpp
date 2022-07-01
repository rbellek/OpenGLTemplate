#include "Mesh.h"
#include "Mesh.h"
#include "Mesh.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

#include <vector>

Mesh::Mesh()
	: m_model(1.0f)
{

}

void Mesh::importFrom(std::string file)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// probably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(file,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene) {
		//DoTheErrorLogging(importer.GetErrorString());
		return;
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	std::vector<unsigned int> indices;
	m_indexCount = 0;
	for (int j = 0; j < scene->mMeshes[0]->mNumFaces; j++) {
		m_indexCount += scene->mMeshes[0]->mFaces[j].mNumIndices;
		for (int i = 0; i < scene->mMeshes[0]->mFaces[j].mNumIndices; i++)
			indices.push_back(scene->mMeshes[0]->mFaces[j].mIndices[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	}



	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	constexpr int count = 6;
	std::vector<float> vertices_and_normals(scene->mMeshes[0]->mNumVertices * count);
	for (int i = 0; i < scene->mMeshes[0]->mNumVertices; i++) {
		vertices_and_normals[i * count] = scene->mMeshes[0]->mVertices[i].x;
		vertices_and_normals[i * count + 1] = scene->mMeshes[0]->mVertices[i].y;
		vertices_and_normals[i * count + 2] = scene->mMeshes[0]->mVertices[i].z;

		if (scene->mMeshes[0]->HasNormals())
		{
			vertices_and_normals[i * count + 3] = scene->mMeshes[0]->mNormals[i].x;
			vertices_and_normals[i * count + 4] = scene->mMeshes[0]->mNormals[i].y;
			vertices_and_normals[i * count + 5] = scene->mMeshes[0]->mNormals[i].z;
		}
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_and_normals.size(), vertices_and_normals.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (const void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Mesh::render()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Mesh::translate(glm::vec3 dir)
{
	m_model = glm::translate(m_model, dir);
}

void Mesh::rotate(glm::vec3 dir, float angle)
{
	m_model = glm::rotate(m_model, glm::radians(angle), dir);
}

void Mesh::scale(glm::vec3 dir)
{
	m_model = glm::scale(m_model, dir);
}

glm::mat4 Mesh::getModel() const
{
	return m_model;
}

void Mesh::reset()
{
	m_model = glm::mat4(1.0f);
}
