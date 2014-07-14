
#ifndef SPRITE_H__
#define SPRITE_H__


#include "TextureManager.h"


class Sprite{
private:
	vector<float> vertices;
	int pozInVectPrinc;
	int pozInEl;
	GLuint texture;
	
	float highX, highY,lowX,lowY;
public:
	Sprite(float lowX, float highX, float lowY, float highY, vector<float> &mainVector,vector<vector<GLuint>>& elements);
	void freeMemory(vector<float> &mainVector, vector<vector<GLuint>>& elements);
	void correctValues(vector<float>& mainVector, vector<vector<GLuint>>&elements);

	void setUV(vector<float> &mainVector, float lowX, float highX, float lowY, float highY);

	void addTexture(TextureManager* t,char* filename);
	void addTexture(GLuint& tex);
	GLint getTexture();

	int getPozInEL();
	int getPozInVectPrinc();

	float getHighX();
	float getHighY();
	float getLowX();
	float getLowY();
};

#endif