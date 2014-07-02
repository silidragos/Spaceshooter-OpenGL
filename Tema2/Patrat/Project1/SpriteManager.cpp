#include"SpriteManager.h"

void SpriteManager::addSprite(Sprite* spr){
	sprites.push_back(spr);
}

void SpriteManager::drawAll(vector<vector<GLuint>>& elements, GLuint ebo[NMAX], GLuint textures[NMAX]){

	for (int i = 0; i < elements.size(); ++i){
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glDrawElements(GL_TRIANGLES, elements[i].size(), GL_UNSIGNED_INT, 0);
	}

}