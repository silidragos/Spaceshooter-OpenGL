#ifndef PLAYER_PHY_H__
#define PLAYER_PHY_H__
#include "Entity.h"

class PlayerPhysics :public Physics{
private:
	float speed;
	glm::mat4 transXP, transXM, transYP, transYM;

public:
	PlayerPhysics(GLint uniTrans);
	bool movement(GLFWwindow* window,float dt);

	float getPozX(float highX, float highY);
	float getPozY(float highX, float highY);

};

#endif