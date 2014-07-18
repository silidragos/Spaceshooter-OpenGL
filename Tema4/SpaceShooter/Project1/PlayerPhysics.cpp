#include "PlayerPhysics.h"

#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtc\type_ptr.hpp"

#include"AnimManager.h"

#include<iostream>
using namespace std;


PlayerPhysics::PlayerPhysics(GLint uniTrans,AnimManager* anim):Physics(uniTrans),eAnimType(NONE),animManager(anim){
	speed = 0.5f*3;
	
}

bool PlayerPhysics::movement(GLFWwindow* window,float dt){
	glm::vec3 dir = glm::vec3(0.0f, 0.0f, 0.0f);
	bool ok = false;

	if (glfwGetKey(window, GLFW_KEY_LEFT)){
		dir.x += -dt*speed;

		if (eAnimType != LEFT){
			animManager->stopAnim("Right");
			animManager->stopAnim("Idle");
			animManager->startAnim("Left");
			eAnimType = LEFT;
		}
		ok = true;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)){
		dir.x += dt*speed;

		if (eAnimType != RIGHT){
			animManager->stopAnim("Idle");
			animManager->stopAnim("Left");
			animManager->startAnim("Right");
			eAnimType = RIGHT;
		}

		ok = true;
	}
	if (glfwGetKey(window, GLFW_KEY_UP)){
		dir.y += dt*speed;
		
		if (eAnimType != IDLE){
			animManager->stopAnim("Right");
			animManager->stopAnim("Left");
			animManager->startAnim("Idle");
			eAnimType = IDLE;

		}
		
		ok = true;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)){
		dir.y += -dt*speed;
		

		if (eAnimType != IDLE){
			animManager->stopAnim("Right");
			animManager->stopAnim("Left");
			animManager->startAnim("Idle");
			eAnimType = IDLE;
		}
	

		ok = true;
	}
	if (ok == true){
		trans = trans*glm::translate(glm::mat4(1.0f), dir);
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

	}
	//Idle
	else 
	if (ok == false){
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
	
		if (eAnimType != IDLE){
			animManager->stopAnim("Right");
			animManager->stopAnim("Left");
			animManager->startAnim("Idle");
			eAnimType = IDLE;
		}

	}
	return ok;
}

float PlayerPhysics::getPozX(float highX,float highY){
	return (trans*glm::vec4(highX, highY, 1.0f, 1.0f)).x;
}
float PlayerPhysics::getPozY(float highX, float highY){
	return (trans*glm::vec4(highX, highY, 1.0f, 1.0f)).y;
}