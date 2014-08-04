#include "Entity.h"

Entity::Entity(Sprite* s,Physics* p){
	sprite = s;
	physics = p;
}
bool Entity::gotEntity(){
	if (physics != NULL) return true;
	return false;
}
