#include "SpriteManager.h"

#include "Entity.h"

#include "PlayerPhysics.h"
#include "EnemyPhysics.h"
#include "ProjectilePhysics.h"

#include"XML.h"
#include"Anim.h"
#include"AnimManager.h"
#include"CameraTransform.h"

#include"utils.h"
#include"Text2D.h"
#include"pauseGUI.h"
#include"Options.h"


#include<iostream>
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtc\type_ptr.hpp"
#include<time.h>

int min(float a, float b){
	return(a < b) ? a : b;
}

GLFWwindow* window;

vector<float> vertices;
vector<vector<GLuint>> elements;

GLuint vbo;
GLuint ebo[NMAX];

GLuint shaderProgram;

SpriteManager* spriteMan = new SpriteManager();
AnimManager* animManager = new AnimManager();

GLuint uniTrans;
Entity* playerEnt;
vector<Entity*> EnEnt;
vector<Sprite*> spr2;
vector<Sprite*> blast;
vector<Entity*> projEnt;
vector<Entity*> enemyProjEnt;
GLuint enBlastTex;

vector<float> blastLifeTime;
vector<float> enemyBlastLifeTime;
float blastLife = 1.3f;
int scor = 0;
int lives = 3;
glm::mat4 trans;

const int nrOfRobots = 25;
bool shakeCamera = false;

void update(float dt){
	for (unsigned int i = 0; i < elements.size();++i)
	if (spriteMan->entities[i]->gotEntity())
		spriteMan->entities[i]->physics->movement(window, dt);

	//Check collisions - Enemy -Player
	for (unsigned int i = 0; i < spr2.size(); ++i){
			//Check Collision
		if (EnEnt[i]->physics->AABBvsAABB(playerEnt->physics->getAABB())){
			spriteMan->removeSprite(spr2[i], vertices, elements);
			spr2.erase(spr2.begin() + i);
			EnEnt.erase(EnEnt.begin() + i);

			scor++;
			lives--;
			shakeCamera = true;
			break;

			}
		}


	//Check collisions - Blast - Enemy
	for (unsigned int j = 0; j < projEnt.size(); j++)
	for (unsigned int i = 0; i < spr2.size(); ++i)
	if (projEnt[j]->physics->AABBvsAABB(EnEnt[i]->physics->getAABB())){
		spriteMan->removeSprite(spr2[i], vertices, elements);
		spr2.erase(spr2.begin() + i);
		EnEnt.erase(EnEnt.begin() + i);

		spriteMan->removeSprite(projEnt[j]->sprite, vertices, elements);
		projEnt.erase(projEnt.begin() + j);
		blastLifeTime.erase(blastLifeTime.begin() + j);

		spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

		scor++;
		shakeCamera = true;
		break;
	}
	//Check collisions - Blast - Player
	for (unsigned int j = 0; j < enemyProjEnt.size(); j++)
	if (enemyProjEnt[j]->physics->AABBvsAABB(playerEnt->physics->getAABB())){
		
		spriteMan->removeSprite(enemyProjEnt[j]->sprite, vertices, elements);
		enemyProjEnt.erase(enemyProjEnt.begin() + j);
		enemyBlastLifeTime.erase(enemyBlastLifeTime.begin() + j);

		spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

		lives--;
		break;
	}


	//Destroy old Blasts
	bool blastDestroyed = false;
	for (unsigned int i = 0; i < blastLifeTime.size(); i++){
		blastLifeTime[i] += dt;
		if (blastLifeTime[i] >= blastLife){
			spriteMan->removeSprite(projEnt[i]->sprite, vertices, elements);
			projEnt.erase(projEnt.begin() + i);
			blastLifeTime.erase(blastLifeTime.begin() + i);
			blastDestroyed = true;
		}
	}
	for (unsigned int i = 0; i < enemyBlastLifeTime.size(); i++){
		enemyBlastLifeTime[i] += dt;
		if (enemyBlastLifeTime[i] >= blastLife+1.0f){
			spriteMan->removeSprite(enemyProjEnt[i]->sprite, vertices, elements);
			enemyProjEnt.erase(enemyProjEnt.begin() + i);
			enemyBlastLifeTime.erase(enemyBlastLifeTime.begin() + i);
			blastDestroyed = true;
		}
	}
	if (blastDestroyed){
		spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
	}

}

void update(){


}

int main() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Read options from XML
	loadOptions("options.xml");

	int windowWidth = 800;
	int windowHeight = 600;

	getResolution(windowWidth, windowHeight);

	window = glfwCreateWindow(windowWidth,windowHeight, "OpenGL", nullptr, nullptr);

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

	glGenBuffers(1, &vbo);
	

	//Test -- Create new sprites
	spr2.resize(nrOfRobots);
	EnEnt.resize(nrOfRobots);
	
	//Add background
	Sprite* BG = new Sprite(-100.0f, 100.0f, -100.0f, 100.0f, vertices, elements);

	Entity* BGEntity = new Entity(BG, NULL);
	spriteMan->addSprite(BG);
	spriteMan->addEntity(BGEntity);

	srand(time(NULL));

	//Creates Enemy ships Sprites

	for (int i = 0; i <nrOfRobots; ++i)
	{
		float pozX = 1 - rand() % 3;
		float pozY = rand() % 100;

		spr2[i] = new Sprite(-1.0+0.2f*(i%5),-1.0+ 0.2f*(i%5)+0.2f,1.0f*(i/5),1.0f*(i/5)+0.2f, vertices, elements);
		spriteMan->addSprite(spr2[i]);
	}

	//EndTest

	shaderProgram = compileShaders( "pixelShader.glsl", "vertexShader.glsl");

	//Translations
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

	// Set up projection
		glm::mat4 view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 2.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
		);
	GLint uniView = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
	
	
	//glm::mat4 proj = glm::perspective(45.0f, 800.0f / 600.0f, 0.0f, 100.0f);
	glm::mat4 proj = glm::ortho(-1.0f,1.0f,-1.0f,1.0f,0.0f,100.0f);
	GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	//Get Red tint for HEATING
	GLint uniTintRed = glGetUniformLocation(shaderProgram, "reddish");

	//Enemy Entities

	for (int i = 0; i < nrOfRobots; ++i){
		int randomType = rand() % 2;
		EnEnt[i] = new Entity(spr2[i], new EnemyPhysics(uniTrans, randomType));
		spriteMan->addEntity(EnEnt[i]);

		EnEnt[i]->physics->setAABB(EnEnt[i]->sprite->getLowX() + 0.04f, EnEnt[i]->sprite->getHighX() - 0.04f, EnEnt[i]->sprite->getLowY() + 0.06f, EnEnt[i]->sprite->getHighY() - 0.06f);
	}

	//Add player
	Sprite* player = new Sprite(-0.1f, 0.1f, -1.0f, -0.8f, vertices, elements);
	spriteMan->addSprite(player);
	playerEnt = new Entity(player, new PlayerPhysics(uniTrans,animManager));
	spriteMan->addEntity(playerEnt);
	playerEnt->physics->setAABB(playerEnt->sprite->getLowX(), playerEnt->sprite->getHighX(), playerEnt->sprite->getLowY(), playerEnt->sprite->getHighY());

	//Add textures
	TextureManager* t = new TextureManager();
	GLuint enTex = t->addTexture("bug.png",'c');
	GLuint blastTex = t->addTexture("blast.png",'c');
	GLuint bgTex = t->addTexture("stars.png",'r');
	GLuint fontTex = t->addTexture("Font.png", 'c');
	enBlastTex = t->addTexture("BugBlast.png", 'c');

	GLuint newGameTex = t->addTexture("NewGame.png", 'c');
	GLuint resumeTex = t->addTexture("Resume.png", 'c');
	GLuint optionsTex = t->addTexture("Options.png", 'c');
	GLuint exitTex = t->addTexture("Exit.png", 'c');
	//Texturile trebuie afisate in ordinea in care sunt in elements!!!

	for (int i = 0; i <nrOfRobots; ++i){
		spr2[i]->addTexture(enTex);
	}

	char* playerImg = new char[32];
	strcpy(playerImg,getPlayerImg().c_str());
	player->addTexture(t->getTexture(playerImg));

	BG->addTexture(t->getTexture("stars.png"));

	BG->setUV(vertices, 0.0f, 100.0f, 0.0f, 100.0f);
	BG->setInBackground(vertices);


	//Initialize stuff
	initializeText(windowWidth,windowHeight);
	initPauseGUI(windowWidth,windowHeight);

	float propHeight = windowHeight / 600.0f;
	float propWidth = windowWidth / 800.0f;
	addGUIAABB(windowHeight,300*propHeight, 450*propWidth, 200, 50);
	addGUIAABB(windowHeight, 300 * propHeight, 375 * propWidth, 200, 50);
	addGUIAABB(windowHeight, 300 * propHeight, 300 * propWidth, 200, 50);


	spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

	//Loading Animations
	animManager->setTimePerFrame(0.2f);

	//Player
	vector<Dict_Entry*> loadedSprites;
	getXml(t,loadedSprites,"player.xml");

	Animatie* anim = new Animatie();
	anim->setSprite(player);
	for (int i = 0; i < 13; i++)
		anim->addDictEntry(loadedSprites[i]);

	Animatie* animLeft = new Animatie();
	animLeft->setSprite(player);
	for (int i = 16; i < 18; ++i){
		animLeft->addDictEntry(loadedSprites[i]);
	}
	animLeft->setLoop(false);

	Animatie* animRight = new Animatie();
	animRight->setSprite(player);
	for (int i = 18; i < 20; ++i){
		animRight->addDictEntry(loadedSprites[i]);
	}
	animRight->setLoop(false);


	spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);

	animManager->addAnim("Idle", anim);
	animManager->startAnim("Idle");

	animManager->addAnim("Left", animLeft);
	animManager->addAnim("Right", animRight);


	//Variables used in while
	GLfloat lastShoot = 0.0f;
	float lastAnim = 0.0f;
	float lastFrame = 0.0f;

	//Check How much time a Blast should last
	float dt;

	float cameraPosX = 0.0f;
	float cameraPosY = 0.0f;
	float lastPosX=0.0f, lastPosY=0.0f;
	bool shouldMove = false;
	bool isPause = true;
	bool isEscPressed = false;

	double accumulator = 0.0f;
	double rest = 0.01f;

	const float maxHeat = 8.0f;
	const float coolingRate = 0.2f;
	const float coolingTime = 0.1f;
	bool overHeated = false;
	float heatRate = 0.0f;
	float lastCoolTime = 0.0f;

	const float shakeTime = 0.15f;
	float shakeStart = 0.0f;

	GLuint firstButTex = newGameTex;

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);


	while (!glfwWindowShouldClose(window)){

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat time = (GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC;

		dt = time - lastFrame;
		lastFrame = time;

		if (dt > 0.25f){
			dt = 0.25f;
		}

		accumulator += dt;

		while (accumulator >= rest){
			if (!isPause)
			update(rest);

			accumulator -= rest;
		}
		
		//New game
		if (spr2.size() == 0){
			char text[256];
			sprintf_s(text, "WINNER!!");
			DrawText(text, fontTex, 250, windowHeight - 300, 40);
			sprintf_s(text, "Score: %i", scor);
			DrawText(text, fontTex, 250, windowHeight - 350, 20);

			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

			continue;
		}

		//Game over
		if (lives == 0){
			char text[256];
			sprintf_s(text, "You Lost!!");
			DrawText(text, fontTex, 250, windowHeight - 300, 40);
			sprintf_s(text, "Score: %i", scor);
			DrawText(text, fontTex, 250, windowHeight - 350, 20);

			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

			continue;
		}

		if ((glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) && isEscPressed) {
			isEscPressed = false;
		}

		if ((glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS && !isEscPressed) && isPause){
			isPause = false;
			isEscPressed = true;

			continue;
		}
		else if ((glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS && !isEscPressed) || isPause){
			isPause = true;

			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			isEscPressed = true;

			char text[256];
			sprintf_s(text, "Space shooter!!");
			DrawText(text, fontTex, 125 * propHeight, 550 * propHeight, 40);

			drawGUI(firstButTex, 300 * propHeight, 450 * propWidth, 200, 50);
			drawGUI(optionsTex, 300 * propHeight, 375 * propWidth, 200, 50);
			drawGUI(exitTex, 300 * propHeight, 300*propWidth, 200, 50);

			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			

			bool shouldExit = false;
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)){
				switch (CheckClicks(window)){
				case(0) : {
							  //Resume
							  isPause = false;
							  firstButTex = resumeTex;
				}
					break;
				case(1) : {
							  //Options
				}
					break;
				case(2) : {
							  //Exit
							  shouldExit = true;
				}
					break;
				default:{
							//Bad Click
				}
				}
			}
			if (shouldExit) break;
			continue;
		}

		
		//Create Projectile
		if (time - lastCoolTime >= coolingTime && heatRate>0.0f){

			heatRate -= coolingRate;
			lastCoolTime = time;

			cout << "Restoring!\n";
			cout << heatRate << endl;

			if (heatRate <= 0.0f) overHeated = false;
		}


		if (heatRate <= maxHeat && !overHeated){
			float playerHighPozX = playerEnt->physics->getPozX(playerEnt->sprite->getHighX(), playerEnt->sprite->getHighY());
			float playerHighPozY = playerEnt->physics->getPozY(playerEnt->sprite->getHighX(), playerEnt->sprite->getHighY());
			if (glfwGetKey(window, GLFW_KEY_SPACE) && time - lastShoot > 0.2f){
				heatRate++;
				if (heatRate > 10) heatRate = 10;

				cout << "Heat increased!\n";
				lastShoot = time;
				Sprite* sBlast = new Sprite(playerHighPozX - 0.2f,
					playerHighPozX,
					playerHighPozY - 0.1f,
					playerHighPozY + 0.1f,
					vertices, elements);
				sBlast->addTexture(blastTex);
				spriteMan->addSprite(sBlast);
				blast.push_back(sBlast);
				blastLifeTime.push_back(0.0f);

				ProjectilePhysics* projPhy = new ProjectilePhysics(uniTrans);
				Entity* sProjEnt = new Entity(sBlast, projPhy);
				projEnt.push_back(sProjEnt);
				projPhy->setDir(0.0f, 1.0f, 0.0f);

				spriteMan->addEntity(sProjEnt);

				sProjEnt->physics->setAABB(sProjEnt->sprite->getLowX() + 0.06f, sProjEnt->sprite->getHighX() - 0.06f, sProjEnt->sprite->getLowY() + 0.06f, sProjEnt->sprite->getHighY() - 0.06f);

				spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
				glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
			}
		}
		else // Player overHeated
		{
			overHeated = true;
		}
		//Enemy shooting
		int shootingPause = 1.0f;
		if (glfwGetTime() - lastShoot > shootingPause && spr2.size()>0){

			int enemyShooting = rand() % min(spr2.size(),5);
			float enemyLowPozX = EnEnt[enemyShooting]->physics->getPozX(EnEnt[enemyShooting]->sprite->getLowX(), EnEnt[enemyShooting]->sprite->getLowY());
			float enemyLowPozY = EnEnt[enemyShooting]->physics->getPozY(EnEnt[enemyShooting]->sprite->getLowX(), EnEnt[enemyShooting]->sprite->getLowY());
				Sprite* sBlast = new Sprite(enemyLowPozX - 0.05f,
				enemyLowPozX+0.05f,
				enemyLowPozY-0.05f,
				enemyLowPozY + 0.05f,
				vertices, elements);

			sBlast->addTexture(enBlastTex);
			spriteMan->addSprite(sBlast);

			enemyBlastLifeTime.push_back(0.0f);

			ProjectilePhysics* projPhy = new ProjectilePhysics(uniTrans);
			Entity* sProjEnt = new Entity(sBlast, projPhy);

			enemyProjEnt.push_back(sProjEnt);
			projPhy->setDir(0.0f,-1.0,0.0f);
			projPhy->setSpeed(0.8f);

			spriteMan->addEntity(sProjEnt);

			sProjEnt->physics->setAABB(sProjEnt->sprite->getLowX() + 0.06f, sProjEnt->sprite->getHighX() - 0.06f, sProjEnt->sprite->getLowY() + 0.06f, sProjEnt->sprite->getHighY() - 0.06f);

			spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);
			glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

			lastShoot = glfwGetTime();
		}
		


		animManager->playActiveAnim(time, vertices);
		spriteMan->reGenBuffers(vbo, ebo, elements, vertices, shaderProgram);


		//Camera Projection/View

	//Interpolation	
		float pozX = playerEnt->physics->getPozX(playerEnt->sprite->getHighX(), playerEnt->sprite->getHighY());
		float pozY = playerEnt->physics->getPozY(playerEnt->sprite->getHighX(), playerEnt->sprite->getHighY());
		pozY += 0.75f;
		if ((abs(pozY - lastPosY) > 0.5f)||shouldMove){
			shouldMove = moveCameraTo(cameraPosX, cameraPosY, cameraPosX, pozY);
			lastPosX = pozX;
			lastPosY = pozY;
		}

		
		float randAngle = 0.0f;
		//Shake
		if (shakeCamera){
			randAngle = (30 - (rand() % 60)) / 1000.0f;
			cout << randAngle << endl;
			if (shakeStart == 0.0f)
				shakeStart = glfwGetTime();
		}
		//Stop shake
		if (glfwGetTime() - shakeStart > shakeTime){
			shakeStart = 0.0f;
			shakeCamera = false;
		}

		glm::mat4 view = glm::lookAt(
			glm::vec3(cameraPosX+randAngle,cameraPosY+randAngle, 2.0f),
			glm::vec3(cameraPosX, cameraPosY, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
			);
		
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));


		//Draw
		spriteMan->drawAll(elements, ebo,shaderProgram,window,vertices,uniTrans,uniTintRed,heatRate,dt);
		
		char text[256];
		sprintf_s(text, "Score : %i", scor);
		DrawText(text, fontTex, 10, windowHeight-50, 20);

		sprintf_s(text, "Lives : %i", lives);
		DrawText(text, fontTex, 10, windowHeight - 100, 20);

		sprintf_s(text, "Time : %.1f sec", glfwGetTime());
		DrawText(text, fontTex, 10, 10, 20);

		if (overHeated){
			DrawText("Overheated!!", fontTex, windowWidth/2-175, windowHeight/2-25, 35);
		}
	}

	//Free memory
	delete playerEnt;
	for (int i = 0; i < EnEnt.size(); ++i) delete EnEnt[i];
	
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(elements.size(), ebo);
	glDeleteVertexArrays(1, &vao);

}