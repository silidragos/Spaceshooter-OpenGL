
#ifndef SPRITE_H__
#define SPRITE_H__

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class Sprite{
private:
	vector<float> vertices;
	int pozInVectPrinc;

public:
	Sprite(float lowX, float highX, float lowY, float highY, char* filepath,vector<float> &mainVector,vector<GLuint>& elements);


};

#endif