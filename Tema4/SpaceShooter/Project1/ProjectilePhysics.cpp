#include"ProjectilePhysics.h"

#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtc\type_ptr.hpp"

ProjectilePhysics::ProjectilePhysics(GLint uniTrans) :Physics(uniTrans){
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	speed = 0.5f / 100.0f;
}

bool ProjectilePhysics::movement(GLFWwindow* window){
	trans *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0, speed, 0.0f));
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
	return true;
}

