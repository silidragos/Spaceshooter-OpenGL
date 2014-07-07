#include"SpriteManager.h"


GLuint SpriteManager::compileShaders(char* pixelShaders, char* vertexShaders){

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
string SpriteManager::LoadFileToString(const char* filepath){
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
void SpriteManager::addSprite(Sprite* spr){
	sprites.push_back(spr);
}
void SpriteManager::drawAll(vector<vector<GLuint>>& elements, GLuint ebo[NMAX], GLuint& shaderProgram, GLFWwindow* window, vector<float>& vertices, GLint uniTrans){

	for (int i = 0; i < elements.size(); ++i){
   		sprites[i]->movement(window, vertices, uniTrans);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, sprites[i]->getTexture());
		glUniform1i(glGetUniformLocation(shaderProgram, "basic_texture"), i);
		glDrawElements(GL_TRIANGLES, elements[i].size(), GL_UNSIGNED_INT, 0);
	}

}

void SpriteManager::removeSprite(Sprite* spr, vector<float> &mainVector, vector<vector<GLuint>>& elements){
	int pozSpr = spr->getPozInEL();
	for (int i = 0; i < sprites.size(); ++i){
		if (sprites[i] == spr){
			sprites.erase(sprites.begin() + i);
			spr->freeMemory(mainVector, elements);
			for (int i = 0; i < sprites.size(); ++i){
				if (sprites[i]->getPozInEL()>pozSpr){
					sprites[i]->correctValues(mainVector, elements);
				}
			}
			break;
		}
	}
}

void SpriteManager::reGenBuffers(GLuint vbo, GLuint ebo[NMAX], vector<vector<GLuint>>& elements, vector<float>& vertices,GLuint& shaderProgram){
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