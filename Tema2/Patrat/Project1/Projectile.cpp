#include"Projectile.h"

bool Projectile::movement(GLFWwindow* window, vector<float> &vertices, GLint uniTrans){

	trans *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0, speed, 0.0f));
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
	return true;

}