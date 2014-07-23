#ifndef PAUSEGUI_H__
#define PAUSEGUI_H__

#include"Sprite.h"

class TextureManager;
class SpriteManager;

void initPauseGUI(int width, int height);
void drawGUI(GLuint& textureID, float x, float y, float width, float height);
void addGUIAABB(int windowHeight,float x, float y, float width, float height);

int CheckClicks(GLFWwindow* window);
#endif