#pragma once

#include "Mesh.h"
#include <SOIL.h>

#include <..\include\assimp\Importer.hpp>
#include <..\assimp\scene.h>
#include <..\assimp\postprocess.h>

class Model {
private:

	vector<Mesh> meshes;
	string directory;

public:
	Model::Model();
	Model::Model(GLchar* path);
	void Model::Draw(Shader shader, GLint drawMode);
	void Model::loadModel(string path);
	void Model::processNode(aiNode* node, const aiScene* scene);
	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	GLint Model::TextureFromFile(const char* path, string directory);

};