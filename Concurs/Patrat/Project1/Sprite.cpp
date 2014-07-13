#include"Sprite.h"

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

	trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	speed = 0.5f / 100.0f;

}

void Sprite::freeMemory(vector<float> &mainVector, vector<vector<GLuint>>& elements){
	elements.erase(elements.begin() + pozInEl);
	mainVector.erase(mainVector.begin() + pozInVectPrinc, mainVector.begin() + pozInVectPrinc + 20);
}
int Sprite::getPozInEL(){
	return pozInEl;
}
int Sprite::getPozInVectPrinc(){
	return pozInVectPrinc;
}

bool Sprite::movement(GLFWwindow* window, vector<float>& vertices, GLint uniTrans){
	int x;
	int y;
	GLfloat time = (GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC;
	glm::mat4 transPart = glm::translate(glm::mat4(1.0f), glm::vec3(sin(time*10) / 25.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
	trans = transPart*trans;
	

	return true;
}