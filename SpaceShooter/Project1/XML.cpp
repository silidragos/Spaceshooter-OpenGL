#include "Sprite.h"
#include"Loaded_Texture.h"
#include "TextureManager.h"

#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_utils.hpp"

#include <map>

#include"XML.h"


void getXml(TextureManager* t, vector<Dict_Entry*>& loadedSprites,char* filepath){
	rapidxml::file<> xmlFile(filepath); // Default template is char
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	rapidxml::xml_node<> *pRoot = doc.first_node();

	rapidxml::xml_attribute<> *img = pRoot->first_attribute("imagePath");
	assert(img);
	char *imageName = img->value();

	Loaded_Texture* needed_img = NULL;
	// find image in Loaded textures
	/*std::map<std::string, Loaded_Texture*>::iterator fnd = loadedTextures.find(imageName);
	
	if (fnd == loadedTextures.end()) // did not find image
	{*/
		std::string locationTex(imageName);
		//locationTex.append(imageName);
		int width, height;
		GLuint texture = t->addTexture(locationTex.c_str(), width, height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


		//Create new Texture
		needed_img = new Loaded_Texture();
		needed_img->set_texture_id(texture);
		needed_img->set_texture_name(imageName);
		needed_img->set_height(height);
		needed_img->set_width(width);

		std::pair<std::string, Loaded_Texture*> ins_t(imageName, needed_img);
	/*}
	else
	{
		needed_img = fnd->second;
	}*/

	for (rapidxml::xml_node<> *pNode = pRoot->first_node("SubTexture"); pNode; pNode = pNode->next_sibling())
	{
		Dict_Entry * new_entry = new Dict_Entry();
		rapidxml::xml_attribute<> *spr_name = pNode->first_attribute("name");
		strcpy(new_entry->sprite_name, spr_name->value());
		rapidxml::xml_attribute<> *spr_x = pNode->first_attribute("x");
		assert(spr_x);
		new_entry->x = atof(spr_x->value());

		rapidxml::xml_attribute<> *spr_y = pNode->first_attribute("y");
		assert(spr_y);
		new_entry->y = atof(spr_y->value());

		rapidxml::xml_attribute<> *spr_w = pNode->first_attribute("width");
		assert(spr_w);
		new_entry->width = atof(spr_w->value());

		rapidxml::xml_attribute<> *spr_h = pNode->first_attribute("height");
		assert(spr_h);
		new_entry->height = atof(spr_h->value());

		new_entry->refTex = needed_img->get();

		std::pair<std::string, Dict_Entry * > ins(new_entry->sprite_name, new_entry);
		
		//Big Vector with all of them
		loadedSprites.push_back(new_entry);
	}
	doc.clear();
}