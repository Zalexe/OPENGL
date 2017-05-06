#pragma once
#include<iostream>
#include<sstream>
#include <fstream>
#include <string>
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>

using namespace std;

class Shader
{
public:
	GLuint Program;
	Shader(const GLchar*,const GLchar*);
	~Shader();
	void USE();
};

