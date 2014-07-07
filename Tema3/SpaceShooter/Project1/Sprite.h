
#ifndef SPRITE_H__
#define SPRITE_H__


#include "TextureManager.h"


class Sprite{
private:
	vector<float> vertices;
	int pozInVectPrinc;
	int pozInEl;
	GLuint texture;

public:
	Sprite(float lowX, float highX, float lowY, float highY, vector<float> &mainVector,vector<vector<GLuint>>& elements);
	void freeMemory(vector<float> &mainVector, vector<vector<GLuint>>& elements);
	void correctValues(vector<float>& mainVector, vector<vector<GLuint>>&elements);

	void addTexture(TextureManager* t,char* filename);
	void addTexture(GLuint& tex);
	GLint getTexture();

	int getPozInEL();
	int getPozInVectPrinc();
	
	virtual bool movement(GLFWwindow* window, vector<float> &vertices, GLint uniTrans)=0;
};

#endif