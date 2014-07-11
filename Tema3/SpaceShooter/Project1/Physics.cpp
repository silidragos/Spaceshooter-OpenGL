#include "Physics.h"

Physics::Physics(GLint uniTrans){
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	this->uniTrans = uniTrans;
}

void Physics::setAABB(float lowX, float highX, float lowY, float highY){
	aabb.min.x = lowX;
	aabb.max.x = highX;
	aabb.min.y = lowY;
	aabb.max.y = highY;
}

AABB Physics::getAABB(){
	AABB a;
	glm::vec4 pozXY = trans*glm::vec4(aabb.max.x, aabb.max.y, 0.0f,1.0f);
	glm::vec4 pozxy = trans*glm::vec4(aabb.min.x, aabb.min.y, 0.0f, 1.0f);
	
	a.max.x = pozXY.x;
	a.max.y = pozXY.y;
	a.min.x = pozxy.x;
	a.min.y = pozxy.y;

	return a;
}

bool Physics::AABBvsAABB(AABB b)
{
	AABB a = getAABB();
	// Exit with no intersection if found separated along an axis
	if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
	if (a.max.y < b.min.y || a.min.y > b.max.y) return false;

	// No separating axis found, therefor there is at least one overlapping axis
	return true;
}