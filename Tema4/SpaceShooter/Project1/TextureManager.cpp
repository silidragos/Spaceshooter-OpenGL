#include"TextureManager.h"

#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<iostream>
#include<fstream>

#include<time.h>

#include "utils.h"

TextureManager::TextureManager(){
	position = 0;
}
GLuint& TextureManager::addTexture(char* filename,char wrap){
	names[position] = filename;
	glGenTextures(1, &textures[position]);

	glActiveTexture(GL_TEXTURE0 + position);
	glBindTexture(GL_TEXTURE_2D, textures[position]);

	int x, y, n;

	int force_channels = 4;
	unsigned char* image = stbi_load(filename, &x, &y, &n, force_channels);

	FlipTexture(image, x, y, n);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	if (wrap == 'c'){
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else if (wrap = 'r'){
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	position++;
	return textures[position-1];
}


GLuint& TextureManager::addTexture(const char* filename, int& x, int&y){
	names[position] = filename;
	glGenTextures(1, &textures[position]);

	glActiveTexture(GL_TEXTURE0 + position);
	glBindTexture(GL_TEXTURE_2D, textures[position]);

	int n;

	int force_channels = 4;
	unsigned char* image = stbi_load(filename, &x, &y, &n, force_channels);

	FlipTexture(image, x, y, n);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	position++;

	return textures[position - 1];
}
GLuint& TextureManager::getTexture(char* filename){
	for (int i = 0; i < position; ++i){
		if (names[i] == filename){
			return textures[i];
		}
	}
	return addTexture(filename,'c');

}