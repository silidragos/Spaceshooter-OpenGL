#ifndef LOADED_TEXTURE_H__
#define LOADED_TEXTURE_H__

#include"Sprite.h"

class Loaded_Texture{
private:
	GLuint texture_id;
	char* texture_name;
	int height, width;

public:
	void set_texture_id(GLuint&);
	void set_texture_name(char*);
	void set_height(int);
	void set_width(int);
	GLuint get();
	

};


#endif