#include "Player.h"

bool Player::movement(GLFWwindow* window, vector<float>& vertices,GLint uniTrans){
	int x;
	int y;
	bool ok = false;
	
	
	if (glfwGetKey(window, GLFW_KEY_LEFT)){
		//cout << "Stanga\n";
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		trans = trans*transXM;
		ok=true;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)){
		//cout << "Dreapta\n";

		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		trans = trans*transXP;
		ok = true;
	}
	if (glfwGetKey(window, GLFW_KEY_UP)){
	//	cout << "Sus\n";

		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		trans = trans*transYP;
		ok = true;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)){
		//cout << "Jos\n";
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		trans = trans*transYM;
		ok = true;
	}
	if (ok == false){
		cout << "f\n";
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans)); 
		
	}

	return ok;
}