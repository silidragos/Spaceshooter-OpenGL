#include"TextureManager.h"

void TextureManager::FlipTexture(unsigned char* image_data, int x, int y, int n)
{
	//flip texture
	int width_in_bytes = x * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = y / 2;

	for (int row = 0; row < half_height; row++) {
		top = image_data + row * width_in_bytes;
		bottom = image_data + (y - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}
}

TextureManager::TextureManager(){
	position = 0;
}
GLuint TextureManager::addTexture(char* filename){
	names[position] = filename;
	glGenTextures(1, &textures[position]);

	glActiveTexture(GL_TEXTURE0 + position);
	glBindTexture(GL_TEXTURE_2D, textures[position]);

	int x, y, n;

	int force_channels = 4;
	unsigned char* image = stbi_load(filename, &x, &y, &n, force_channels);

	FlipTexture(image, x, y, n);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	position++;
	return textures[position-1];
}
GLuint TextureManager::getTexture(char* filename){
	for (int i = 0; i < position; ++i){
		if (names[i] == filename){
			return textures[i];
		}
	}
	return addTexture(filename);

}