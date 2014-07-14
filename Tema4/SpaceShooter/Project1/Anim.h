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
	int currentFrame;

public:
	Animatie();
	void setSprite(Sprite*s);
	void addDictEntry(Dict_Entry*);
	bool nextFrame(std::vector<float> &mainVector);



};

#endif