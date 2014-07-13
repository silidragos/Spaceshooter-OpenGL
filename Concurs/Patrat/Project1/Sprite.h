#ifndef SPRITE_H__
#define SPRITE_H__

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
#include<stdlib.h>

#include<time.h>

#define NMAX 200

using namespace std;


class Sprite{
private:
	int pozInVectPrinc;
	int pozInEl;
	float speed;
	vector<float> vertices;
	glm::mat4 trans;

public:
	Sprite(float lowX, float highX, float lowY, float highY, vector<float> &mainVector, vector<vector<GLuint>>& elements);
	void freeMemory(vector<float> &mainVector, vector<vector<GLuint>>& elements);

	int getPozInEL();
	int getPozInVectPrinc();

	bool movement(GLFWwindow* window, vector<float> &vertices, GLint uniTrans);
};

#endif