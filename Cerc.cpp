#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>

#include<cmath>

#include <string>
#include <fstream>
#include <vector>
#define MAXSIDES 360
#define PI 3.14159265358

using namespace std;


string LoadFileToString(const char* filepath){
	string fileData;
	ifstream stream(filepath, ios::in);

	if (stream.is_open()){
		string line = "";
		while (getline(stream, line)){
			fileData += '\n' + line;
		}
		stream.close();
	}

	return fileData;
}

GLuint LoadShaders(const char* vertShaderPath, const char* fragShaderPath){

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	string vertShaderSource = LoadFileToString(vertShaderPath);
	string fragShaderSource = LoadFileToString(fragShaderPath);

	const char* rawVertShaderSource = vertShaderSource.c_str();
	const char* rawFragShaderSource = fragShaderSource.c_str();

	glShaderSource(vertShader, 1, &rawVertShaderSource, NULL);
	glShaderSource(fragShader, 1, &rawFragShaderSource, NULL);

	glCompileShader(vertShader);
	glCompileShader(fragShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	return program;

}

void generateVertArray(GLfloat verts[3*MAXSIDES], int nrOfSides){
	
	verts[0] = verts[1] = verts[2] = 0.0f;
	for (int i = 1; i <= nrOfSides; ++i){
		verts[i * 3] = .5*cosf(2.0*PI*i/ nrOfSides);
		verts[i * 3+1] = .5*sinf(2.0*PI*i / nrOfSides);
		verts[i * 3 + 2] =0.0f;
	}
}

void generateElements(GLuint elements[3*MAXSIDES],int nrOfSides){
	for (int i = 0; i < nrOfSides-1; ++i){
		elements[i * 3] = 0;
		elements[i * 3 + 1] = i+1;
		elements[i * 3 + 2] = i+2;
	}
	elements[(nrOfSides-1) * 3] = 0;
	elements[(nrOfSides - 1) * 3 + 1] = nrOfSides;
	elements[(nrOfSides - 1) * 3 + 2] = 1;

	
	
}

int main() {

	int nrOfSides = 50;

	if (glfwInit() == false){
		//did not succeed
		fprintf(stderr, "GLFW failed to initialize!");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create the window
	GLFWwindow* window;
	window = glfwCreateWindow(640, 640, "My OPENGL", NULL, NULL);


	if (!window){
		fprintf(stderr, "Things went bad!");
		glfwTerminate();
		return -1;
	}

	//Make the window primary
	glfwMakeContextCurrent(window);

	glewExperimental = true;

	//Initialize GLEW
	if (glewInit() != GLEW_OK){
		fprintf(stderr, "Glew is gone, man!");
		glfwTerminate();
		return -1;
	}

	//generate Vertex ARRAY
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	static GLfloat verts[3*MAXSIDES];

	generateVertArray(verts, nrOfSides);
	
	//Generate a program to process the shaders
	GLuint program = LoadShaders("vertexShader.glsl", "pixelShader.glsl");

	//Vertex BUFFERS
	//Generate VBO
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*3*nrOfSides, verts, GL_STATIC_DRAW);
	
	GLuint elements[MAXSIDES];

	generateElements(elements, nrOfSides);

	GLuint eboID;
	glGenBuffers(1,&eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	do{
		//Clear the buffer after coloring the background
		glClear(GL_COLOR_BUFFER_BIT);

		//Enable the array. Bind the buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//Use the shader program
		glUseProgram(program);

		//Draw the triangle
		glDrawElements(GL_TRIANGLES,(nrOfSides+1)*3, GL_UNSIGNED_INT, 0);
	
		
		//Disable array
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (!glfwWindowShouldClose(window));



	return 0;
}