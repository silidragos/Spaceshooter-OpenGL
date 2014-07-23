#include"Options.h"

#include<string>
#include<fstream>
#include<sstream>
#include<stdlib.h>

#include"rapidxml.hpp"
#include"rapidxml_utils.hpp"
#include"rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;



struct Options{
	int width;
	int height;

	string playerImg;
	string playerXml;

};

Options options;

void loadOptions(char* filepath){
	
	std::ifstream file(filepath);

	xml_document<> doc;
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<>* pNode;
	pNode = doc.first_node()->first_node();
	char* width = pNode->first_attribute()->value();
	char* height = pNode->first_attribute()->next_attribute()->value();
	pNode = pNode->next_sibling();
	string playerImg = pNode->first_attribute()->value();
	string playerXml = pNode->first_attribute()->next_attribute()->value();
	
	options.playerImg = playerImg;
	options.playerXml = playerXml;

	options.width = atoi(width);
	options.height = atoi(height);
}

void getResolution(int &width, int& height){
	width = options.width;
	height = options.height;
}

string getPlayerImg(){
	return options.playerImg;
}