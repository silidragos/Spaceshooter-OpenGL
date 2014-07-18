#ifndef PLAYER_PHY_H__
#define PLAYER_PHY_H__
#include "Entity.h"

class AnimManager;

class PlayerPhysics :public Physics{
private:
	float speed;
	AnimManager* animManager;

	enum EAnimationTypePlayer
	{
		NONE,
		IDLE,
		RIGHT,
		LEFT
	};

	EAnimationTypePlayer eAnimType;

public:
	PlayerPhysics(GLint uniTrans,AnimManager*);
	bool movement(GLFWwindow* window,float dt);

	float getPozX(float highX, float highY);
	float getPozY(float highX, float highY);

};

#endif