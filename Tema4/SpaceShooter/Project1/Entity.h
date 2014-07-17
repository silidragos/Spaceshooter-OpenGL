#ifndef ENTITY_H__
#define ENTITY_H__
#include "Sprite.h"
#include"Physics.h"


class Entity{
private:


public:
	Sprite* sprite;
	Physics* physics;
	//methods
public:
	Entity(Sprite* s,Physics* p);
	bool gotEntity();
	~Entity(){
		delete sprite;
		delete physics;
	}
};

#endif