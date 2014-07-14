#include "EnemyPhysics.h"

#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtc\type_ptr.hpp"

#include<time.h>

EnemyPhysics::EnemyPhysics(GLint uniTrans,int t) :Physics(uniTrans){
	//Set type
	switch (t){
	case (0) : enemyType = LINIAR;
		break;
	case (1) : enemyType = SINUSOIDAL;
		break;
	}
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

}

bool EnemyPhysics::movement(GLFWwindow* window){
	int x;
	int y;
	bool ok = true;
	speed = 0.5f/5;
	GLfloat time = (GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC;

	switch (enemyType){
	case(LINIAR) : {
					   glm::mat4 transPart = glm::translate(glm::mat4(1.0f), glm::vec3(sin(time) /500.0f, 0.0f, 0.0f));
					   glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
					   trans = transPart*trans;
	}
		break;
	case(SINUSOIDAL) : {
						   glm::mat4 transPart = glm::translate(glm::mat4(1.0f), glm::vec3(sin(time) / 500.0f, sin(time * 10) / 5000.0f, 0.0f));
						   glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
						   trans = trans * transPart;
	}
		break;
	}

	return ok;
}