#include"Sprite.h"

Sprite::Sprite(float lowX, float highX, float lowY, float highY, vector<float> &mainVector, vector<vector<GLuint>>& elements){
	this->highX = highX;
	this->highY = highY;
	this->lowX = lowX;
	this->lowY = lowY;

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

void Sprite::addTexture(TextureManager* t,char* filename){
	texture = t->getTexture(filename);
}
void Sprite::addTexture(GLuint& tex){
	texture = tex;
}

GLint Sprite::getTexture(){
	return texture;
}
void Sprite::freeMemory(vector<float> &mainVector, vector<vector<GLuint>>& elements){
	elements.erase(elements.begin() + pozInEl);
	mainVector.erase(mainVector.begin() + pozInVectPrinc, mainVector.begin() + pozInVectPrinc + 20);
}
void Sprite::correctValues(vector<float>& mainVector, vector<vector<GLuint>>&elements){
	pozInEl--;
	for (int i = 0; i < 6; ++i) elements[pozInEl][i] -= 4;
	pozInVectPrinc -= 20;
	
}

int Sprite::getPozInEL(){
	return pozInEl;
}
int Sprite::getPozInVectPrinc(){
	return pozInVectPrinc;
}

float Sprite::getHighX(){
	return highX;
}
float Sprite::getHighY(){
	return highY;
}
float Sprite::getLowX(){
	return lowX;
}
float Sprite::getLowY(){
	return lowY;
}

void Sprite::setUV(vector<float> &mainVector, float lowX, float highX, float lowY, float highY){
	mainVector[pozInVectPrinc + 3] = lowX;
	mainVector[pozInVectPrinc + 4] = highY;

	mainVector[pozInVectPrinc + 5 + 3] = highX;
	mainVector[pozInVectPrinc + 5 + 4] = highY;

	mainVector[pozInVectPrinc + 10 + 3] = highX;
	mainVector[pozInVectPrinc + 10 + 4] = lowY;

	mainVector[pozInVectPrinc + 15 + 3] = lowX;
	mainVector[pozInVectPrinc + 15 + 4] = lowY;
}