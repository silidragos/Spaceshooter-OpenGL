#ifndef UTILS_H__
#define UTILS_H__


#include <string>
using namespace std;

void FlipTexture(unsigned char* image_data, int x, int y, int n);

string LoadFileToString(const char* filepath);

GLuint compileShaders(char* pixelShaders, char* vertexShaders);
#endif