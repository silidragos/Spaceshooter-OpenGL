#ifndef SPRITEMANAGER_H__
#define SPRITEMANAGER_H__

#include "Sprite.h"

class SpriteManager{
private:
	vector<Sprite*> sprites;


	//Methods
	string LoadFileToString(const char* filepath);
	GLuint compileShaders(char* pixelShaders, char* vertexShaders);
public:

	void addSprite(Sprite*);
	void addSprite(float lowX, float highX, float lowY, float highY, vector<float> &mainVector, vector<vector<GLuint>>& elements);
	void removeSprite(Sprite*, vector<float> &mainVector, vector<vector<GLuint>>& elements,GLuint textures[NMAX]);
	void reGenBuffers(GLuint vbo, GLuint ebo[NMAX], vector<vector<GLuint>>& elements, vector<float>& vertices, GLuint& shaderProgram);
	Sprite* getSprite();

	void drawAll(vector<vector<GLuint>>& elements, GLuint ebo[NMAX], GLuint textures[NMAX], GLuint& shaderProgram, GLFWwindow* window, vector<float>& vertices, GLint uniTrans);


};

#endif