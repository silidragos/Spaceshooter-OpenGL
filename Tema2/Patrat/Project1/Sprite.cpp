#include"Sprite.h"


Sprite::Sprite(float lowX, float highX, float lowY, float highY, char* filepath, vector<float> &mainVector, vector<GLuint>& elements){
	//Bottom Left
	vertices.push_back(lowX);
	vertices.push_back(lowY);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	//Bottom Right
	vertices.push_back(highX);
	vertices.push_back(lowY);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);
	//Top Right
	vertices.push_back(highX);
	vertices.push_back(highY);
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	//Top Left
	vertices.push_back(lowX);
	vertices.push_back(highY);
	vertices.push_back(0.0f);
	vertices.push_back(1.0f);


	for (int i = 0; i < vertices.size(); ++i)
		mainVector.push_back(vertices[i]);
}