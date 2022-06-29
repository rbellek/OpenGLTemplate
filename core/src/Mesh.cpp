#include "Mesh.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <glad/glad.h>

#include <vector>

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

	unsigned int indices2[] = {
	0, 3, 1,
	1, 3, 2,
	2, 3, 0,
	0, 1, 2
	};

	GLfloat vertices2[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

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
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	}



	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	std::vector<float> vertices;
	for (int i = 0; i < scene->mMeshes[0]->mNumVertices; i++) {
		vertices.push_back(scene->mMeshes[0]->mVertices[i].x);
		vertices.push_back(scene->mMeshes[0]->mVertices[i].y);
		vertices.push_back(scene->mMeshes[0]->mVertices[i].z);
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

}

void Mesh::render()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}