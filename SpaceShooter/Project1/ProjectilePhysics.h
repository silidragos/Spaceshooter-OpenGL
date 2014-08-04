#ifndef PROJECTILE_PHY_H__
#define PROJECTILE_PHY_H__
#include "Entity.h"

class ProjectilePhysics :public Physics{
private:
	float speed;
	glm::vec3 dir;

public:
	ProjectilePhysics(GLint uniTrans);
	bool movement(GLFWwindow* window,float dt);

	void setDir(float x, float y, float z);
	void setSpeed(float s);

	float getPozX(float highX, float highY){ return 0; }
	float getPozY(float highX, float highY){ return 0; }
	glm::mat4 getTrans(){ return trans; }
};

#endif