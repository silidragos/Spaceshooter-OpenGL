#ifndef ANIMMANAGER_H__
#define ANIMMANAGER_H__
#include<vector>
#include<map>
#include<string>
class Animatie;

class AnimManager{
private:
	std::map<std::string,Animatie*> animatii;
	std::map<std::string, bool> animState;
	float timePerFrame;
	float lastAnim;


public:
	AnimManager();
	void setTimePerFrame(float);
	void addAnim(const char*,Animatie*);
	void startAnim(const char* nume);
	void stopAnim(const char* nume);
	void playActiveAnim(float time, std::vector<float> &mainVector);


};


#endif