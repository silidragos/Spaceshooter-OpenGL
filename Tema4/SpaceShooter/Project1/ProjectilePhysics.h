#ifndef PROJECTILE_PHY_H__
#define PROJECTILE_PHY_H__
#include "Entity.h"

class ProjectilePhysics :public Physics{
private:
	float speed;

public:
	ProjectilePhysics(GLint uniTrans);
	bool movement(GLFWwindow* window,float dt);

	float getPozX(float highX, float highY){ return 0; }
	float getPozY(float highX, float highY){ return 0; }
};

#endif