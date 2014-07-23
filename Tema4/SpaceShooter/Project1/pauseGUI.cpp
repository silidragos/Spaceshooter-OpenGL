#include"pauseGUI.h"

#include<vector>

#include"utils.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


unsigned int GUIVertexBufferID;
unsigned int GUIUVBufferID;
unsigned int GUITextureID;
unsigned int GUIShaderID;
unsigned int GUIUniformID;

unsigned int GUIresID;

float scrWidth, scrHeight;

void initPauseGUI(int width,int height){
	
	scrWidth = width;
	scrHeight = height;

	glGenBuffers(1, &GUIVertexBufferID);
	glGenBuffers(1, &GUIUVBufferID);

	GUIShaderID = compileShaders("TextPixelShader.glsl", "TextVertexShader.glsl");
	GUIUniformID = glGetUniformLocation(GUIShaderID, "basic_texture");


	GUIresID = glGetUniformLocation(GUIShaderID, "resolution");



}

void drawGUI(GLuint& textureID, float x, float y, float width,float height){
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;

	glm::vec2 vertex_up_left = glm::vec2(x, y + height);
	glm::vec2 vertex_up_right = glm::vec2(x + width, y + height);
	glm::vec2 vertex_down_right = glm::vec2(x + width, y);
	glm::vec2 vertex_down_left = glm::vec2(x , y);

	vertices.push_back(vertex_up_left);
	vertices.push_back(vertex_down_left);
	vertices.push_back(vertex_up_right);

	vertices.push_back(vertex_down_right);
	vertices.push_back(vertex_up_right);
	vertices.push_back(vertex_down_left);


	glm::vec2 uv_up_left = glm::vec2(0, 1);
	glm::vec2 uv_up_right = glm::vec2(1, 1);
	glm::vec2 uv_down_right = glm::vec2(1,0);
	glm::vec2 uv_down_left = glm::vec2(0,0);

	UVs.push_back(uv_up_left);
	UVs.push_back(uv_down_left);
	UVs.push_back(uv_up_right);

	UVs.push_back(uv_down_right);
	UVs.push_back(uv_up_right);
	UVs.push_back(uv_down_left);

	glBindBuffer(GL_ARRAY_BUFFER, GUIVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, GUIUVBufferID);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

	// Bind shader
	glUseProgram(GUIShaderID);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(GUIUniformID, 0);
	//Set resolution
	glUniform2f(GUIresID, scrWidth,scrHeight);


	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, GUIVertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, GUIUVBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}


struct AABB{
	float xmin, xmax;
	float ymin, ymax;
};

vector<AABB> buttons;

void addGUIAABB(int windowHeight, float x, float y, float width, float height){
	AABB newBut;
	newBut.xmin = x;
	newBut.xmax = x + width;
	newBut.ymin = windowHeight-y - height;
	newBut.ymax = windowHeight - y;
	buttons.push_back(newBut);

}

int CheckClicks(GLFWwindow* window){
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	for (int i = 0; i < buttons.size(); ++i){
		if (((xpos - buttons[i].xmin)>=0.0f)&&((xpos - buttons[i].xmin) < (buttons[i].xmax - buttons[i].xmin)) &&
			(((ypos - buttons[i].ymin)>=0.0f)&&(ypos - buttons[i].ymin) < (buttons[i].ymax - buttons[i].ymin)))
			return i;
	}
	return -1;
}