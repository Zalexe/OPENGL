#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Shader.h"
#include <GL\glew.h>

#include <gtc\matrix_transform.hpp>
#include <glm.hpp>
#include <..\include\assimp\types.h>

using namespace std;
using namespace glm;

struct Vertex{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};

struct Texture {

	GLuint id;
	string type;
	aiString path;

};
class Mesh{
private:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	GLuint VAO, EBO, VBO;
	public:
		 Mesh::Mesh(vector<Vertex> vert, vector<GLuint> ind, vector<Texture> text);
		void Mesh::setupMesh();
		int Mesh::size();
		void Mesh::Draw(Shader MeshShader, GLint DrawMode);


};