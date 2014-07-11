#ifndef PHYSICS_H__
#define PHYSICS_H__

#include"Sprite.h"

struct AABB{
	glm::vec2 min;
	glm::vec2 max;
};

class Physics{
protected:
	glm::mat4 trans;
	GLint uniTrans;

	AABB aabb;
public:
	Physics(GLint uniTrans);
	virtual bool movement(GLFWwindow*) = 0;
	virtual float getPozX(float, float) = 0;
	virtual float getPozY(float, float) = 0;

	bool AABBvsAABB(AABB other);

	void setAABB(float, float, float, float);
	AABB getAABB();

};


#endif