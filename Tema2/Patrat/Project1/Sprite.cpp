#include"Sprite.h"

void Sprite::FlipTexture(unsigned char* image_data, int x, int y, int n)
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


Sprite::Sprite(float lowX, float highX, float lowY, float highY, vector<float> &mainVector, vector<vector<GLuint>>& elements){
	int l = mainVector.size()/5;

	//Top Left
	vertices.push_back(lowX);
	vertices.push_back(highY);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
	//Top Right
	vertices.push_back(highX);
	vertices.push_back(highY);
	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	//Bottom Right
	vertices.push_back(highX);
	vertices.push_back(lowY);
	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);
	//Bottom Left
	vertices.push_back(lowX);
	vertices.push_back(lowY);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	pozInVectPrinc = mainVector.size();
	pozInEl = elements.size();

	for (int i = 0; i < vertices.size(); ++i)
		mainVector.push_back(vertices[i]);
	
	vector<GLuint> aux;
	//Complete Elements
	aux.push_back(l);
	aux.push_back(l + 1);
	aux.push_back(l + 2);

	aux.push_back(l + 2);
	aux.push_back(l + 3);
	aux.push_back(l);

	elements.push_back(aux);


}
void Sprite::addTexture(char* filepath,GLuint texture,int i){
	glGenTextures(1, &texture);

	glActiveTexture(GL_TEXTURE0+i);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	int x, y, n;

	int force_channels = 4;
	unsigned char* image = stbi_load(filepath, &x, &y, &n, force_channels);

	FlipTexture(image, x, y, n);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
void Sprite::freeMemory(vector<float> &mainVector, vector<vector<GLuint>>& elements){
	elements.erase(elements.begin() + pozInEl);
	mainVector.erase(mainVector.begin() + pozInVectPrinc, mainVector.begin() + pozInVectPrinc + 20);
	delete this;
}
int Sprite::getPozInEL(){
	return pozInEl;
}
int Sprite::getPozInVectPrinc(){
	return pozInVectPrinc;
}
void Sprite::correctValues(vector<float> &mainVector, vector<vector<GLuint>>& elements,GLuint textures[NMAX]){
	pozInEl -= 1;
	for (int i = 0; i < elements[pozInEl].size(); ++i){
		elements[pozInEl][i] -= 4;
		//textures[pozInEl] = textures[pozInEl+1];
	}
	pozInVectPrinc -= 20;
}