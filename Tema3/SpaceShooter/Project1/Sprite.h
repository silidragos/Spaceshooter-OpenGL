
#ifndef SPRITE_H__
#define SPRITE_H__

#define NMAX 200

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include<time.h>

using namespace std;

class Sprite{
private:
	vector<float> vertices;
	int pozInVectPrinc;
	int pozInEl;


	void FlipTexture(unsigned char* image_data, int x, int y, int n);
public:
	Sprite(float lowX, float highX, float lowY, float highY, vector<float> &mainVector,vector<vector<GLuint>>& elements);
	void addTexture(char* filepath, GLuint textures,int);
	void freeMemory(vector<float> &mainVector, vector<vector<GLuint>>& elements);
	
	int getPozInEL();
	int getPozInVectPrinc();
	
	virtual bool movement(GLFWwindow* window, vector<float> &vertices, GLint uniTrans)=0;
};

#endif