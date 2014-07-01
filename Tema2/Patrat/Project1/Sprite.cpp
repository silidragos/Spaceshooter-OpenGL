#include"Sprite.h"


Sprite::Sprite(float lowX, float highX, float lowY, float highY, char* filepath, vector<float> &mainVector, vector<GLuint>& elements){
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
	

	


	for (int i = 0; i < vertices.size(); ++i)
		mainVector.push_back(vertices[i]);
	

	//Complete Elements
	elements.push_back(l);
	elements.push_back(l + 1);
	elements.push_back(l + 2);


	elements.push_back(l + 2);
	elements.push_back(l + 3);
	elements.push_back(l);

}