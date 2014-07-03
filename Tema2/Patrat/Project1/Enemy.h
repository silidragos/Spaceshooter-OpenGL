#ifndef ENEMY_H__
#define ENEMY_H__

#include "SpriteManager.h"

class Enemy : public Sprite {
public:
	enum Type{ LINIAR, SINUSOIDAL };

private:
	float speed = 0.5f;
	Type enemyType;
public:
	
	

	Enemy(float lowX, float highX, float lowY, float highY, vector<float> &mainVector, vector<vector<GLuint>>& elements, Type t);
	bool Movement(GLFWwindow* window, vector<float> &vertices, float time);



};


#endif 