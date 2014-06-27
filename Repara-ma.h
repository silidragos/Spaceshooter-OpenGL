
class Entity
{
	int id;
	int varsta=0;

public:

	static std::vector<Entity*> all_Entities;


	static void InitializeEntities();
	static void RemoveEntity(Entity *ent);

	virtual void Update(float dt)
	{
		varsta++;
	}

	int  GetVarsta(){ return varsta; }
	void SetVarsta(int v) { varsta = v; };

	void Die()
	{
		RemoveEntity(this);
	}

};
