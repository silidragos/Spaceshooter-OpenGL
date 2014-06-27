#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include<fstream>
#include<string>
#include<iostream>


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

GLuint compileShaders(char* pixelShaders, char* vertexShaders){

	string vertexSourceStr = LoadFileToString(vertexShaders);
	string fragmentSourceStr = LoadFileToString(pixelShaders);
	const GLchar* vertexSource = vertexSourceStr.c_str();
	const GLchar* fragmentSource = fragmentSourceStr.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	return shaderProgram;

}

int main() {


	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(window);


	glewExperimental = GL_TRUE;
	glewInit();


	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	GLuint vbo;
	glGenBuffers(1, &vbo);

	float vertices[] = {
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 
		0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 
		-0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 
		
		0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		+0.5f, 1.0f, 0.0f, 1.0f, 0.0f
		
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	GLuint elements[] = {
		0, 1, 2,
		3, 4 ,5
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);



	GLuint shaderProgram = compileShaders("pixelShader.glsl", "vertexShader.glsl");


	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));



	while (!glfwWindowShouldClose(window)){

		glfwSwapBuffers(window);
		glfwPollEvents();


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);


	}

	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

}