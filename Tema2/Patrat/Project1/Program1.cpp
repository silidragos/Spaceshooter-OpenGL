

#include "Sprite.h"

#define NMAX 200


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
void FlipTexture(unsigned char* image_data, int x, int y, int n)
{
	//flip texture
	int width_in_bytes = x * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = y / 2;

	for (int row = 0; row < half_height; row++) {
		top = image_data + row * width_in_bytes;
		bottom = image_data + (y - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}

}
int main() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);

	if (!window){
		fprintf(stderr, "Window couldn't be created!\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	//Initialize GLEW
	if (glewInit() != GLEW_OK){
		fprintf(stderr, "Glew is gone, man!\n");
		glfwTerminate();
		return -1;
	}

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	vector<float> vertices;
	

	GLuint ebo[NMAX];
	vector<vector<GLuint>> elements;

	//Test -- Create new sprites

	Sprite* spr1 = new Sprite(0.8f, 1.0f, 0.8f, 1.0f, vertices, elements);
	Sprite* spr2 = new Sprite(0.0f, 0.2f, 0.0f, 0.2f, vertices, elements);
	//EndTest

	
	glGenBuffers(elements.size(), ebo);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);

	for (int i = 0; i < elements.size(); ++i){
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements[i].size()*sizeof(GLuint), &elements[i][0], GL_STATIC_DRAW);
	}


	GLuint shaderProgram = compileShaders("pixelShader.glsl", "vertexShader.glsl");

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	GLuint textures[NMAX];
	glGenTextures(elements.size(), &textures[0]);

	//Add textures
	spr1->addTexture("bug.png",textures[0]);
	spr2->addTexture("fighter.png", textures[1]);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	while (!glfwWindowShouldClose(window)){

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0; i < elements.size(); ++i){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			glDrawElements(GL_TRIANGLES, elements[i].size(), GL_UNSIGNED_INT, 0);

		}
	}

	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

}