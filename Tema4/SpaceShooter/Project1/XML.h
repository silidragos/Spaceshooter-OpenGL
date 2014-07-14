#include"Sprite.h"
class TextureManager;


struct Dict_Entry{
	char sprite_name[30];
	int x;
	int y;
	int width;
	int height;

	GLuint refTex;
};

void getXml(TextureManager* t,vector<Dict_Entry*>& loadedSprites);
