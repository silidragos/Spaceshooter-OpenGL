#include "Player.h"

bool Player::Movement(GLFWwindow* window, vector<float>& vertices){
	int x;
	int y;
	bool ok = true;
	speed = 0.5f/200.0f;

	if (glfwGetKey(window, GLFW_KEY_LEFT)){
		cout << "Stanga\n";
	
		for (int i = 0; i < 4; ++i){
			x = getPozInVectPrinc() + 5 * i;
			vertices[x] += -speed;
		}

		ok=true;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)){
		cout << "Dreapta\n";

		for (int i = 0; i < 4; ++i){
			x = getPozInVectPrinc() + 5 * i;
			vertices[x] += speed;
		}
		ok=true;
	}
	if (glfwGetKey(window, GLFW_KEY_UP)){
		cout << "Sus\n";

		for (int i = 0; i < 4; ++i){
			y = getPozInVectPrinc() + 5 * i+1;
			vertices[y] += speed;
		}
		ok = true;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)){
		cout << "Jos\n";

		for (int i = 0; i < 4; ++i){
			y = getPozInVectPrinc() + 5 * i + 1;
			vertices[y] += -speed;
		}
		ok=true;
	}

	return ok;
}