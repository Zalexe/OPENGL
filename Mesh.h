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