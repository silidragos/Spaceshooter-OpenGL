#include "Player.h"

bool Player::movement(GLFWwindow* window, vector<float>& vertices,GLint uniTrans){
	bool ok = false;
	
	if (glfwGetKey(window, GLFW_KEY_LEFT)){
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		trans = trans*transXM;
		ok=true;
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
float Player::getPozX(){
	return (trans*glm::vec4(highX, highY, 1.0f,1.0f)).x;
}
float Player::getPozY(){
	return (trans*glm::vec4(highX, highY, 1.0f, 1.0f)).y;
}