//#include "stdafx.h"
#include <stdio.h>
#include <vector>
#include <time.h>
#include <assert.h>




using namespace std;

#define MAX_NAME 256
#define MAX_NUMBER_OF_ENTITIES 1024

#define MAX_COUNT 1024

//#define _SAVE_MODE
#define _LOAD_MODE

#define FILE_NAME "DATA.bin"


class Entity_Data{
private:
	int age;
	int flags;
	float position_x;
	float position_y;
	short id;
	char  name[MAX_NAME];

public:
	Entity_Data()
	{
		age = rand() % 100;
		flags = rand() % 16;
		position_x = (float)(rand() % 1000);
		position_y = (float)(rand() % 1000);
		id = rand();
		strcpy_s(name, "Entitate");
		}
};

#ifdef _SAVE_MODE
void SaveEntityData(const Entity_Data * data, int count, FILE *fout)
{
	fwrite(data, sizeof(Entity_Data), count, fout);
}
#endif

#ifdef _LOAD_MODE
void LoadEntityData(Entity_Data * data,int count,  FILE *fin)
{
	fread(data, sizeof(Entity_Data), count, fin);
}
#endif

int main()
{
	srand(time(NULL));

	for (int j = 0; j < MAX_COUNT; j++)
	{
		Entity_Data vec_in[MAX_NUMBER_OF_ENTITIES];
		Entity_Data vec_out[MAX_NUMBER_OF_ENTITIES];
#ifdef _SAVE_MODE
		FILE *fout = fopen(FILE_NAME, "wb");

		SaveEntityData(vec_in, MAX_NUMBER_OF_ENTITIES, fout);
		fclose(fout);
#endif
#ifdef _LOAD_MODE
		FILE *fin = fopen(FILE_NAME, "rb");

		LoadEntityData(vec_out, MAX_NUMBER_OF_ENTITIES, fin);
		fclose(fin);
#endif

	}
	return 0;
}
