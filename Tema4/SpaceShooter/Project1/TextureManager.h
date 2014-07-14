#ifndef TEXMAN_H__
#define TEXMAN_H__

#include<string>
#include<vector>

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#define NMAX 200

using namespace std;

class TextureManager{
private:
	string names[100];
	GLuint textures[100];


	int position;

	void FlipTexture(unsigned char* image_data, int x, int y, int n);
public:
	TextureManager();
	GLuint& addTexture(char* filename);
	GLuint& addTexture(const char* filename,int& x,int&y);
	GLuint& getTexture(char* filename);

};

#endif