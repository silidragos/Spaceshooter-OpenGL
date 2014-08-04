#ifndef ENEMY_PHY_H__
#define ENEMY_PHY_H__
#include "Entity.h"

class EnemyPhysics :public Physics{
private:
	float speed;
	enum Type{ LINIAR, SINUSOIDAL };
	Type enemyType;


public:
	EnemyPhysics(GLint uniTrans,int type);
	bool movement(GLFWwindow* window,float dt);

	float getPozX(float x, float y);
	float getPozY(float x, float y);
	glm::mat4 EnemyPhysics::getTrans();
};

#endif