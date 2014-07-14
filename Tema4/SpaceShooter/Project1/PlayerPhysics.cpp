#include "PlayerPhysics.h"
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtc\type_ptr.hpp"

PlayerPhysics::PlayerPhysics(GLint uniTrans):Physics(uniTrans){
	speed = 0.5f / 100.0f;
	transXP = glm::translate(glm::mat4(1.0f), glm::vec3(speed, 0.0f, 0.0f));
	transYP = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, speed, 0.0f));
	transXM = glm::translate(glm::mat4(1.0f), glm::vec3(-speed, 0.0f, 0.0f));
	transYM = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -speed, 0.0f));
}

bool PlayerPhysics::movement(GLFWwindow* window){
	bool ok = false;

	if (glfwGetKey(window, GLFW_KEY_LEFT)){
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		trans = trans*transXM;
		ok = true;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)){
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		trans = trans*transXP;
		ok = true;
	}
	if (glfwGetKey(window, GLFW_KEY_UP)){
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		trans = trans*transYP;
		ok = true;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)){
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		trans = trans*transYM;
		ok = true;
	}
	//Idle
	if (ok == false){
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
	}
	return ok;
}

float PlayerPhysics::getPozX(float highX,float highY){
	return (trans*glm::vec4(highX, highY, 1.0f, 1.0f)).x;
}
float PlayerPhysics::getPozY(float highX, float highY){
	return (trans*glm::vec4(highX, highY, 1.0f, 1.0f)).y;
}