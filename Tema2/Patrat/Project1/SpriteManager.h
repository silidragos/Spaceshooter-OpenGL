#ifndef SPRITEMANAGER_H__
#define SPRITEMANAGER_H__

#include "Sprite.h"

#define NMAX 200

class SpriteManager{
private:
	vector<Sprite*> sprites;


public:
	void addSprite(Sprite*);
	void removeSprite();
	Sprite* getSprite();

	void drawAll(vector<vector<GLuint>>& elements, GLuint ebo[NMAX], GLuint textures[NMAX]);


};

#endif