#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <fstream>

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

int main() {

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
	window = glfwCreateWindow(640, 480, "My OPENGL", NULL, NULL);


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

	GLfloat verts[] = {
		//  X     Y     Z   R    G     B    A
		0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.8f, -0.8f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	};

	//Generate a program to process the shaders
	GLuint program = LoadShaders("vertexShader.glsl", "pixelShader.glsl");
	

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	// connect the xyz to the "vPosition" attribute of the vertex shader
	GLint posAtr = glGetAttribLocation(program, "vp");
	GLint colAtr = glGetAttribLocation(program, "vColor");


	//Vertex BUFFERS
	//Generate VBO
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(program, "vp");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	do{
		//Clear the buffer after coloring the background
		glClear(GL_COLOR_BUFFER_BIT);

		//Use the shader program
		glUseProgram(program);

		//Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Disable array
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (!glfwWindowShouldClose(window));



	return 0;
}