#include "SpriteManager.h"

#include "Entity.h"

#include "PlayerPhysics.h"
#include "EnemyPhysics.h"
#include "ProjectilePhysics.h"


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
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

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
	vector<Entity*> EnEnt;
	vector<Sprite*> spr2;
	spr2.resize(5);
	EnEnt.resize(5);
	

	srand(time(NULL));

	
	//Creates Enemy ships
	for (int i = 0; i < 5; ++i)
	{
		spr2[i] = new Sprite(-1.0f+i*0.2f, -1.0f+(i + 1)*0.2f, 0.6, 0.8f, vertices, elements);
		spriteMan->addSprite(spr2[i]);
		
	}

	//EndTest

	GLuint shaderProgram = compileShaders("pixelShader.glsl", "vertexShader.glsl");

	spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);

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


	//

	//Enemy Entities
	for (int i = 0; i < 5; ++i){
		EnEnt[i] = new Entity(spr2[i], new EnemyPhysics(uniTrans, rand() % 2));
		spriteMan->addEntity(EnEnt[i]);

		EnEnt[i]->physics->setAABB(EnEnt[i]->sprite->getLowX(), EnEnt[i]->sprite->getHighX(), EnEnt[i]->sprite->getLowY(), EnEnt[i]->sprite->getHighY());
	}

	//Add player
	Sprite* player = new Sprite(-0.1f, 0.1f, -1.0f, -0.8f, vertices, elements);
	spriteMan->addSprite(player);
	Entity* playerEnt = new Entity(player, new PlayerPhysics(uniTrans));
	spriteMan->addEntity(playerEnt);
	playerEnt->physics->setAABB(playerEnt->sprite->getLowX(), playerEnt->sprite->getHighX(), playerEnt->sprite->getLowY(), playerEnt->sprite->getHighY());

	
	//Add textures
	TextureManager* t = new TextureManager();
	GLuint enTex = t->getTexture("bug.png");

	GLuint blastTex = t->getTexture("blast.png");
	//Texturile trebuie afisate in ordinea in care sunt in elements!!!
	
	
	
	for (int i = 0; i < 5; ++i){
		spr2[i]->addTexture(enTex);
	}
	player->addTexture(t, "fighter.png");
	
	
	//Variables used in while
	bool flag1 = false;
	bool flag2 = true;
	Sprite* blast;
	Entity* projEnt;
	GLfloat lastShoot = 0.0f;
	int k = 6;

	spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

	while (!glfwWindowShouldClose(window)){

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat time = (GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC;

		//Create Projectile
		if (glfwGetKey(window, GLFW_KEY_SPACE) && time-lastShoot>0.5f){
			lastShoot = time;
			blast = new Sprite(playerEnt->physics->getPozX(playerEnt->sprite->getHighX(), playerEnt->sprite->getHighY())-0.2f, 
				playerEnt->physics->getPozX(playerEnt->sprite->getHighX(), playerEnt->sprite->getHighY()),
				playerEnt->physics->getPozY(playerEnt->sprite->getHighX(), playerEnt->sprite->getHighY()) -0.1f,
				playerEnt->physics->getPozY(playerEnt->sprite->getHighX(), playerEnt->sprite->getHighY()) + 0.1f, 
				vertices, elements);
			blast->addTexture(blastTex);
			k++;
			spriteMan->addSprite(blast);

			projEnt = new Entity(blast, new ProjectilePhysics(uniTrans));
			spriteMan->addEntity(projEnt);
			//Make AABB tests
			flag1 = true;
			
			projEnt->physics->setAABB(projEnt->sprite->getLowX(), projEnt->sprite->getHighX(), projEnt->sprite->getLowY(), projEnt->sprite->getHighY());

			spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
			glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		}
		else if (time - lastShoot>0.5f){
			flag1 = false;
		}
		
		//DELETE SPECIFIC STUFF
		/*if (time >= 2.0f && flag2){
			cout << "bum";
			flag2 = false;
			spriteMan->removeSprite(spr2[2],vertices,elements);
			EnEnt.erase(EnEnt.begin()+2);

			spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
			glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		}*/

		if (flag1){
			for (int i = 0; i < spr2.size(); ++i)
			if (projEnt->physics->AABBvsAABB(EnEnt[i]->physics->getAABB())){
				spriteMan->removeSprite(spr2[i], vertices, elements);
				spr2.erase(spr2.begin() + i);
				EnEnt.erase(EnEnt.begin() + i);

				spriteMan->removeSprite(blast, vertices, elements);
				delete projEnt;

				spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
				glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
				
			}
		}
		
		
		spriteMan->drawAll(elements, ebo,shaderProgram,window,vertices,uniTrans);
	
		
	}

	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(elements.size(), ebo);
	glDeleteVertexArrays(1, &vao);

}