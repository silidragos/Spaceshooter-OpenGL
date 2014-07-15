#include"Anim.h"
#include"Sprite.h"

#include"XML.h"
#include<iostream>

Animatie::Animatie(){
	currentFrame = 0;
	loop = true;
}

void Animatie::addDictEntry(Dict_Entry* f){
	frames.push_back(f);
}

bool Animatie::nextFrame(vector<float> &mainVector){
	//Change UV-s using frames[currentFrame];
	float lowX, lowY, highX, highY; 
	highX = frames[currentFrame]->x / 1024.0f;
	lowY = frames[currentFrame]->y / 512.0f;
	lowX = (frames[currentFrame]->x + frames[currentFrame]->width) / 1024.0f;
	highY = (frames[currentFrame]->y + frames[currentFrame]->height) /512.0f;
	

	s->setUV(mainVector, lowX, highX, lowY, highY);
	
	if (loop && (currentFrame == frames.size() - 1)){
		currentFrame = 0;
		return true;
	}
	else if (currentFrame < (frames.size() - 1)){
		currentFrame++;
		return true;
	}
	return false;
	
}

void Animatie::setSprite(Sprite* s){
	this->s = s;
}