#ifndef PROJECTILE_H__
#define PROJECTILE_H__

#include "SpriteManager.h"


class Projectile : public Sprite {
private:
	float speed;
	glm::mat4 trans;

public:
	Projectile(float pozX, float pozY, vector<float> &mainVector, vector<vector<GLuint>>& elements) 
			:Sprite(pozX-0.1f, pozX+0.1f,
				pozY-0.1f,pozY+0.1f, mainVector, elements) {
		cout << pozX << " " << pozY << endl;
		trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		speed = 0.5f / 400.0f;
	}
	bool movement(GLFWwindow* window, vector<float> &vertices, GLint uniTrans);



};

#endif