//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "..\Shader.h"
#include <SOIL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;
bool paintQuad = false;
float mixStuff;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


mat3 Matriz;

void DrawVao(GLuint programID, GLuint VAO) {
	//establecer el shader
	glUseProgram(programID);

	//pitar el VAO
	glBindVertexArray(VAO);
	if (!paintQuad) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

}

void main() {
	mixStuff = 0.0f;
	//initGLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);
	//TODO

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);


	//create a window
	//TODO
	GLFWwindow* window;



	window = glfwCreateWindow(WIDTH, HEIGHT, "Primera ventana", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	//set GLEW and inicializate
	//TODO

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		std::cout << "Error al inicializar glew" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	int screenWithd, screenHeight;
	glfwGetFramebufferSize(window, &screenWithd, &screenHeight);
	//set function when callback
	//TODO
	glfwSetKeyCallback(window, key_callback);

	//set windows and viewport
	//TODO
	glViewport(0, 0, screenWithd, screenHeight);
	glClear(GL_COLOR_BUFFER_BIT);

	//fondo
	glClearColor(1.0,0.0, 1.0, 1.0);


	//TODO


	//cargamos los shader

	//Shader shader = Shader("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");

	Shader shader = Shader("./src/textureVertex.vertexshader", "./src/textureFragment.fragmentshader");

	//GLuint programID = shader.Program;

	//GLuint programID = LoadShaders("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");

	// Definir el buffer de vertices
	//Reserva de memoria

	//GLfloat traingleVertex[] = {
	//-0.5f,-0.5f,0,
	//0.5f,0.5f,0,
	//-0.5f,0.5f,0,
	//0.5f,-0.5f,0
	//};

	//VBO
	//GLfloat VertexBufferObject[] = {
	//	0.5f,  0.5f, 0.0f,  // Top Right
	//	0.5f, -0.5f, 0.0f,  // Bottom Right
	//	-0.5f, -0.5f, 0.0f,  // Bottom Left
	//	-0.5f,  0.5f, 0.0f   // Top Left 
	//};

	GLfloat VertexBufferObject[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};


	//Numbuffer = cantidad de buffers a generar;

	//Borrado
	//glDeleteBuffers(GLsizei n, const GLuint* ids);

	//-VBO

	//EBO

	//GLuint IndexBufferObject[]{
	//	0,1,2,
	//	1,3,0 };
	GLuint IndexBufferObject[]{
		2,0,3,
		2,1,0

	};
	//-EBO


	// Definir el EBO

	// Crear los VBO, VAO y EBO

	GLuint VAO, EBO, VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); {

		glGenBuffers(1, &VBO);
		//Se enlaza el buffer para poder usarlo
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//Se pasan los datos
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_DYNAMIC_DRAW);


		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_DYNAMIC_DRAW);


		//Propiedades

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 8 *3 * sizeof(GL_FLOAT), (GLvoid*)(6 *3* sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(3);


		//LIMPIA LOS BUFFERS DE VERTICES

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}glBindVertexArray(0);



	//reservar memoria para el VAO, VBO y EBO



	//Establecer el objeto
	//Declarar el VBO y el EBO

	//Enlazar el buffer con openGL

	//Establecer las propiedades de los vertices

	//liberar el buffer

	//liberar el buffer de vertices


	//GLint loc = glGetUniformLocation(shader.Program, "time");


	GLuint texture1, texture2;




	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int widthTex, heightTex;
	//widthTex = heightTex = 512;
	unsigned char* image = SOIL_load_image("./src/001.jpg", &widthTex, &heightTex, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthTex, heightTex, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int widthTex2, heightTex2;

	unsigned char* image2 = SOIL_load_image("./src/002.jpg", &widthTex2, &heightTex2, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthTex2, heightTex2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	SOIL_free_image_data(image2);

	glBindTexture(GL_TEXTURE_2D, 0);


	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{


		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions

		/*if (loc != -1)
		{
		glUniform1f(loc, glfwGetTime());
		}*/

		glfwPollEvents();



		//Establecer el color de fondo
		glClear(GL_COLOR_BUFFER_BIT);


		GLint locTex = glGetUniformLocation(shader.Program, "ourTexture");
		GLint locTex2 = glGetUniformLocation(shader.Program, "ourTexture2");
		GLint loc = glGetUniformLocation(shader.Program, "mixStuff");
		shader.USE();
		
		glUniform1f(loc, mixStuff);


		//glClearColor(0, 1, 0, 0);

		//DrawVao(shader.Program,VAO);
		//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_INT, 0);


		//glBindVertexArray(0);

		//glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(locTex,0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(locTex2, 1);


		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		
		//pintar con lineas
		//pintar con triangulos


		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// liberar la memoria de los VAO, EBO y VBO

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//TODO, comprobar que la tecla pulsada es escape para cerrar la aplicación y la tecla w para cambiar a modo widwframe
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		paintQuad = !paintQuad;
	}

	if (key == GLFW_KEY_UP&&action == GLFW_PRESS) {
		if (mixStuff<1)		mixStuff += 0.1f;
	}
	if (key == GLFW_KEY_DOWN&&action == GLFW_PRESS) {
		if (mixStuff>0.1)		mixStuff -= 0.1f;
	}

	if (key == GLFW_KEY_RIGHT&&action == GLFW_PRESS) {
		//Matriz= glm::rotate(Matriz,90.0f,vec3(1.0,0.0,0.0));
	}
	if (key == GLFW_KEY_LEFT&&action == GLFW_PRESS) {
		//Matriz= glm::rotate(Matriz, -90.0f, vec3(1.0, 0.0, 0.0));
	}
}
