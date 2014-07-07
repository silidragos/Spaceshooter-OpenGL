#ifndef PLAYER_H__
#define PLAYER_H__

#include "SpriteManager.h"

class Player : public Sprite {
private:
	float speed;
	float highX;
	float highY;

	glm::mat4 transXP,transXM,transYP,transYM;
	glm::mat4 trans;
public:
	Player(float lowX, float highX, float lowY, float highY, vector<float> &mainVector, vector<vector<GLuint>>& elements) :Sprite(lowX, highX, lowY, highY, mainVector, elements) {
		this->highX = highX;
		this->highY = highY;

		speed = 0.5f / 400.0f;
		trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		transXP = glm::translate(glm::mat4(1.0f), glm::vec3(speed, 0.0f, 0.0f));
		transYP = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, speed, 0.0f));
		transXM = glm::translate(glm::mat4(1.0f), glm::vec3(-speed, 0.0f, 0.0f));
		transYM = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -speed, 0.0f));
	}
	bool movement(GLFWwindow* window, vector<float> &vertices,GLint uniTrans);
	float getPozX();
	float getPozY();


};


#endif 