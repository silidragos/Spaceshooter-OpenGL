#include "Sprite.h"

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

vector<Sprite*> sprites;

void addSprite(Sprite* spr){
sprites.push_back(spr);}
void removeSprite(vector<float> &mainVector, vector<vector<GLuint>>& elements){

	elements.erase(elements.end()-1);
	mainVector.erase(mainVector.end() - 20, mainVector.end());
	sprites.erase(sprites.end() - 1);
}
void drawAll(vector<vector<GLuint>>& elements, GLuint ebo[NMAX], GLuint& shaderProgram, GLFWwindow* window, vector<float>& vertices, GLint uniTrans){

for (int i = 0; i < elements.size(); ++i){
	sprites[i]->movement(window, vertices, uniTrans);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);

	glDrawElements(GL_TRIANGLES, elements[i].size(), GL_UNSIGNED_INT, 0);
	}	
}
void reGenBuffers(GLuint vbo, GLuint ebo[NMAX], vector<vector<GLuint>>& elements, vector<float>& vertices, GLuint& shaderProgram){
	glGenBuffers(1, &vbo);
	glGenBuffers(elements.size(), ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);

	for (int i = 0; i < elements.size(); ++i){
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements[i].size()*sizeof(GLuint), &elements[i][0], GL_STATIC_DRAW);
	}

	shaderProgram = compileShaders("pixelShader.glsl", "vertexShader.glsl");

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}


int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "OpenGL", nullptr, nullptr);

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
		fprintf(stderr, "Glew is gone!\n");
		glfwTerminate();
		return -1;
	}

	//Enable alpha channel
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnable(GL_BLEND);  
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	vector<float> vertices;
	
	GLuint ebo[NMAX];
	vector<vector<GLuint>> elements;

	Sprite* s = new Sprite(-1.0f, -0.9f, -1.0f, -0.9f, vertices, elements);
	addSprite(s);

	//EndTest
	GLuint texture;
	GLuint shaderProgram = compileShaders("pixelShader.glsl", "vertexShader.glsl");

	reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
	glGenTextures(1, &texture);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	int x, y, n;

	int force_channels = 4;
	unsigned char* image = stbi_load("unnamed.png", &x, &y, &n, force_channels);

	FlipTexture(image, x, y, n);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texture);
	glUniform1i(glGetUniformLocation(shaderProgram, "basic_texture"),0);

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

	srand(time(NULL));

	string strFPS;
	float fps = 0;
	float lastSec = 0.0f;
	float randY;
	int randSgn;
	int count = 0;
	while (!glfwWindowShouldClose(window)){

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat time = (GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC;
		if (time - lastSec < 1.0f){
			fps++;
		}
		else{
			strFPS.clear();
			strFPS = to_string(fps);
			strFPS = "openGL " + strFPS;
			glfwSetWindowTitle(window, strFPS.c_str());

			cout << fps << " " << time << endl;
			fps = 0;
			lastSec = time;
		}
		

		if (glfwGetKey(window, GLFW_KEY_KP_ADD)){

			randY = (rand() % 99) / 100.0f;
			randSgn = rand() % 2;
			cout << "Rand-" << randY << endl;

			s = new Sprite(0.0f, 0.1f,randSgn - randY - 0.1f, randSgn - randY,vertices, elements);
			cout << ++count << endl;
			addSprite(s);
		}

		if (glfwGetKey(window, GLFW_KEY_MINUS) && count>0){
			removeSprite(vertices,elements);
			cout << --count << endl;
		}
		reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);

		drawAll(elements, ebo, shaderProgram, window, vertices, uniTrans);
		
	}
	sprites.clear();

	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(elements.size(), ebo);
	glDeleteVertexArrays(1, &vao);

}