
#ifndef SPRITE_H__
#define SPRITE_H__

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include "stb_image.h"

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class Sprite{
private:
	vector<float> vertices;
	int pozInVectPrinc;
	int pozInEl = 0;


	void FlipTexture(unsigned char* image_data, int x, int y, int n);
public:
	Sprite(float lowX, float highX, float lowY, float highY, vector<float> &mainVector,vector<vector<GLuint>>& elements);
	void addTexture(char* filepath, GLuint textures);
	void freeMemory(vector<float> &mainVector, vector<vector<GLuint>>& elements);
	
	int getPozInEL();
	void correctValues(vector<float> &mainVector, vector<vector<GLuint>>& elements);		//corrects pozInEL and pozInVectPrinc after another Sprite was deleted
};

#endif