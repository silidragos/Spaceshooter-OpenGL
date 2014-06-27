//#include "stdafx.h"
#include <stdio.h>
#include <vector>
#include <time.h>

#include "Repara-ma.h"

using namespace std;

#define NUMBER_OF_ENTITIES 128

#define COUNTER_STOP 1000
#define VARSTA_MOARTE 100
#define _TCHAR char

vector<Entity*> Entity::all_Entities;

enum E_ENTITY_TYPE
{
	E_ENTITY_NONE,
	E_ENTITY_GODZILLA,
	E_ENTITY_ALEX,
	E_ENTITY_MASINA,

	E_NUM_ENTITY_TYPE
};





class Nimic : public Entity
{
public:
	void Update(float dt)
	{
		Entity::Update(dt);
		printf("\n");
	}

};
class Godzilla : public Entity
{
public:
	void Update(float dt)
	{
		Entity::Update(dt);
		printf("ROAR!\n");
	}
};

class Alex : public Entity
{
public:
	void Update(float dt)
	{
		Entity::Update(dt);
		printf("PYTHON!\n");
	}

};

class Masina : public Entity
{
public:
	void Update(float dt)
	{
		Entity::Update(dt);
		printf("VRUM VRUM \n");
	}

};

void Entity::RemoveEntity(Entity *ent)
{
	std::vector<Entity*>::iterator it = find(all_Entities.begin(), all_Entities.end(), ent);
	if (it != all_Entities.end())
	{
		Entity::all_Entities.erase(it);
	}
	
}

void Entity::InitializeEntities()
{
	srand(time(NULL)); 
	
	Entity::all_Entities.resize(NUMBER_OF_ENTITIES);
	
	for (int i = 0; i < NUMBER_OF_ENTITIES; i++)
	{

		int entity_type = rand() % E_NUM_ENTITY_TYPE;
		Entity * newEntity = NULL;
		switch ((E_ENTITY_TYPE)entity_type)
		{
			case E_ENTITY_NONE:
			{
							  newEntity = new Nimic();
							  break;
			}
			case E_ENTITY_GODZILLA:
			{
							  newEntity = new Godzilla();
							  break;
			}
			case E_ENTITY_ALEX:
			{
						      newEntity = new Alex();
							  break;
			}
			case E_ENTITY_MASINA:
			{
							  newEntity = new Masina();
							  break;
			}
		}
		newEntity->SetVarsta(0);
		Entity::all_Entities[i] = newEntity;
	}
}

int main()
{
	Entity::InitializeEntities();
	
	int counter = 0;
	while (true)
	{
		counter++;
		int i = 0;
		int size = Entity::all_Entities.size();
		for (; i < size; i++)
		{
			Entity::all_Entities[i]->Update(0.0f);
		}

		for (i = 0; i < size; i++)
		{
			if (Entity::all_Entities[i]->GetVarsta() > VARSTA_MOARTE)
			{
				Entity::all_Entities[i]->Die();
				counter++;
				size--;
			}
		}

		if (counter > COUNTER_STOP)
		{
			break;
		}
	}

	return 0;
}

