#include "Enemy.h"

Enemy::Enemy(float lowX, float highX, float lowY, float highY, vector<float> &mainVector, vector<vector<GLuint>>& elements, Type t) :Sprite(lowX, highX, lowY, highY, mainVector, elements){
	enemyType = t;
}

bool Enemy::Movement(GLFWwindow* window, vector<float>& vertices, float time){
	int x;
	int y;
	bool ok = true;
	speed = 0.5f / 200.0f;

	switch (enemyType){
	case(LINIAR) : {
					   for (int i = 0; i < 4; ++i){
						   x = getPozInVectPrinc() + 5 * i;
						   vertices[x] += 2*sin(time)/1000;
					   }
	}
		break;
	case(SINUSOIDAL) : {
						   for (int i = 0; i < 4; ++i){
							   x = getPozInVectPrinc() + 5 * i;
							   vertices[x] += 2 * sin(time) / 1000;

							   y = getPozInVectPrinc() + 5 * i + 1;
							   vertices[y] += sin(time*7) / 1000;

						   }
	}
		break;



	}


	return ok;
}