#include"SpriteManager.h"

#include<iostream>
#include<fstream>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


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
void SpriteManager::addEntity(Entity* e){
	entities.push_back(e);
}
void SpriteManager::drawAll(vector<vector<GLuint>>& elements, GLuint ebo[NMAX], GLuint& shaderProgram, GLFWwindow* window, vector<float>& vertices, GLint uniTrans,GLint uniTint,float tintValue,float dt){
	glUniform3f(uniTint, (tintValue / 15.0f + 0.9f)*(tintValue / 15.0f + 0.9f), 1.0f, 1.0f);

	for (int i = 0; i < elements.size(); ++i){
		glm::mat4 trans;
		if (!entities[i]->gotEntity())
		trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		else trans = entities[i]->physics->getTrans();

		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, entities[i]->sprite->getTexture());
		glUniform1i(glGetUniformLocation(shaderProgram, "basic_texture"), i);
		
		glDrawElements(GL_TRIANGLES, elements[i].size(), GL_UNSIGNED_INT, 0);
	}

}

void SpriteManager::removeSprite(Sprite* spr, vector<float> &mainVector, vector<vector<GLuint>>& elements){
	int pozSpr = spr->getPozInEL();
	for (int i = 0; i < sprites.size(); ++i){
		if (sprites[i] == spr){
			sprites[i]->freeMemory(mainVector, elements);
			sprites.erase(sprites.begin() + i);
			entities.erase(entities.begin() + i);
			
			for (int i = 0; i < sprites.size(); ++i){
				if (sprites[i]->getPozInEL()>pozSpr){
					sprites[i]->correctValues(mainVector, elements);
				}
			}

			//elements.erase(elements.end()-1);
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