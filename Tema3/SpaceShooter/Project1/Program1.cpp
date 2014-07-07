#include "SpriteManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"


string LoadFileToString(const char* filepath){
	string fileData;
	ifstream stream(filepath, ios::in);

	if (stream.is_open()){
		string line = "";
		while (getline(stream, line)){
			fileData += '\n' + line;
		}
		stream.close();
	}

	return fileData;
}
GLuint compileShaders(char* pixelShaders, char* vertexShaders){

	string vertexSourceStr = LoadFileToString(vertexShaders);
	string fragmentSourceStr = LoadFileToString(pixelShaders);
	const GLchar* vertexSource = vertexSourceStr.c_str();
	const GLchar* fragmentSource = fragmentSourceStr.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	return shaderProgram;

}
int main() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);

	if (!window){
		fprintf(stderr, "Window couldn't be created!\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();


	//Initialize GLEW
	if (glewInit() != GLEW_OK){
		fprintf(stderr, "Glew is gone!\n");
		glfwTerminate();
		return -1;
	}

	//Enable alpha channel
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnable(GL_BLEND);  
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	vector<float> vertices;
	

	GLuint ebo[NMAX];
	vector<vector<GLuint>> elements;

	//Test -- Create new sprites
	SpriteManager* spriteMan = new SpriteManager();
	Enemy* spr2[5];

	srand(time(NULL));

	
	//Creates Enemy ships
	for (int i = 0; i < 5; ++i)
	{
		spr2[i] = new Enemy(-1.0f, -0.8f, i*0.2f, (i + 1)*0.2f, vertices, elements, rand()%2);

		spriteMan->addSprite(spr2[i]);
		
	}

	//Add player
	Player* player = new Player(-0.1f, 0.1f, -1.0f, -0.8f, vertices, elements);
	spriteMan->addSprite(player);


	//EndTest

	GLuint shaderProgram = compileShaders("pixelShader.glsl", "vertexShader.glsl");

	spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
	
	//Add textures
	TextureManager* t = new TextureManager();
	GLuint enTex = t->getTexture("bug.png");

	GLuint blastTex = t->getTexture("blast.png");
	//Texturile trebuie afisate in ordinea in care sunt in elements!!!
	
	for (int i = 0; i < 5; ++i){
		spr2[i]->addTexture(enTex);
	}

	player->addTexture(t,"fighter.png");


	bool flag1 = true;
	bool flag2 = true;
	Player* pl2;

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

	//Camera Transformations
	glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f,-1.0f,1.0f);
	GLint uniProj = glGetUniformLocation(shaderProgram, "orto");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
	
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::lookAt(pos, target, up);
	GLint uniView = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
	
	Projectile* blast;
	GLfloat lastShoot = 0.0f;
	int k = 6;

	while (!glfwWindowShouldClose(window)){

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat time = (GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC;

		//Create Projectile
		if (glfwGetKey(window, GLFW_KEY_SPACE) && time-lastShoot>0.5f){
			lastShoot = time;
			blast = new Projectile(player->getPozX(), player->getPozY(),vertices, elements);
			blast->addTexture(blastTex);
			k++;
			spriteMan->addSprite(blast);
			flag1 = false;
			
			spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
			glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		}
		
		//ERROR ON TEXTURES!
		if (time >= 0.0f && flag2){
			cout << "bum";
			flag2 = false;
			spriteMan->removeSprite(player,vertices,elements);

			spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
			glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		}
	
		spriteMan->drawAll(elements, ebo,shaderProgram,window,vertices,uniTrans);
	
		
	}

	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(elements.size(), ebo);
	glDeleteVertexArrays(1, &vao);

}