#include "Enemy.h"

Enemy::Enemy(float lowX, float highX, float lowY, float highY, vector<float> &mainVector, vector<vector<GLuint>>& elements, Type t) :Sprite(lowX, highX, lowY, highY, mainVector, elements){
	enemyType = t;
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

bool Enemy::movement(GLFWwindow* window, vector<float>& vertices, GLint uniTrans){
	int x;
	int y;
	bool ok = true;
	speed = 0.5f / 200.0f;
	GLfloat time = (GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC;
	
	switch (enemyType){
	case(LINIAR) : {
					   glm::mat4 transPart = glm::translate(glm::mat4(1.0f), glm::vec3(sin(time)/3000.0f, 0.0f, 0.0f));
					   glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
					   trans = transPart*trans;
	}
		break;
	case(SINUSOIDAL) : {
						   glm::mat4 transPart = glm::translate(glm::mat4(1.0f), glm::vec3(sin(time) / 3000.0f,sin(time*10) / 5000.0f, 0.0f));
						   glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
						   trans = trans * transPart;
	}
		break;
	}

	return ok;
}