#include"AnimManager.h"
#include"Anim.h"

AnimManager::AnimManager(){
	lastAnim = 0.0f;
}

void AnimManager::addAnim(const char* nume, Animatie* anim){
	std::string name(nume);
	animatii[name] = anim;
	animState[name] = false;
}

void AnimManager::setTimePerFrame(float t){
	timePerFrame = t;
}

void AnimManager::startAnim(const char* nume){
	std::string name(nume);
	animState[name] = true;
	animatii[name]->setIsWorking(true);
}

void AnimManager::stopAnim(const char* nume){
	std::string name(nume);
	animState[name] = false;
	animatii[name]->stop();
}

void AnimManager::playActiveAnim(float time, std::vector<float> &mainVector){
	if (time - lastAnim >= timePerFrame){
		std::map<std::string, Animatie*>::iterator it;
		for (it = animatii.begin(); it != animatii.end(); it++){
			if (animState[it->first] == true){
				it->second->nextFrame(mainVector);
				animState[it->first] = it->second->getIsWorking();
			}
		}
		lastAnim = time;
	}
}

