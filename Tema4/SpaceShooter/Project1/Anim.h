#ifndef ANIM_H__
#define ANIM

struct Dict_Entry;
class Sprite;

#include<vector>

class Animatie{
private:
	Sprite* s;
	std::vector<Dict_Entry*> frames;
	bool loop;
	bool isWorking = false;
	int currentFrame;

public:
	Animatie();
	void setIsWorking(bool);
	bool getIsWorking();
	void setLoop(bool);
	void setSprite(Sprite*s);
	void addDictEntry(Dict_Entry*);
	bool nextFrame(std::vector<float> &mainVector);
	void stop();



};

#endif