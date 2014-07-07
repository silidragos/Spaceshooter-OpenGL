#ifndef TEXMAN_H__
#define TEXMAN_H__
#include "Sprite.h"

class TextureManager{
private:
	GLuint textures[100];
	string names[100];

public:

	GLuint* addTexture(char* filename);
	GLuint* getTexture(char* filename);


};

#endif