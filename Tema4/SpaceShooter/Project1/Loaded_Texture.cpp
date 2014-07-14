#include "Loaded_Texture.h"

void Loaded_Texture::set_texture_id(GLuint& texture_id){
	this->texture_id = texture_id;
}

void Loaded_Texture::set_texture_name(char* name){
	this->texture_name = name;
}

void Loaded_Texture::set_height(int height){
	this->height = height;
}

void Loaded_Texture::set_width(int width){
	this->width = width;
}

GLuint Loaded_Texture::get(){
	return texture_id;
}

