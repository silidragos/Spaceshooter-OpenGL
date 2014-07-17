#include"CameraTransform.h"

bool moveCameraTo(float& cameraX,float& cameraY, float targetX, float targetY){
	if (abs(targetX - cameraX)>0.1f || abs(targetY - cameraY)>0.1f){
		cameraX = 0.99f*cameraX +0.01f *targetX;
		cameraY = 0.99f*cameraY +0.01f *targetY;
		return true;
	}
	return false;
}