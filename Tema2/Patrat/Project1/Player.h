#ifndef PLAYER_H__
#define PLAYER_H__

#include "SpriteManager.h"

class Player : public Sprite {
private:
float speed = 0.5f;

public:
	Player(float lowX, float highX, float lowY, float highY, vector<float> &mainVector, vector<vector<GLuint>>& elements) :Sprite(lowX, highX, lowY, highY, mainVector, elements) {}
	bool Movement(GLFWwindow* window, vector<float> &vertices);



};


#endif 