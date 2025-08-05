#include "EntityFactory.h"

EntityFactory::EntityFactory()
{
	
}

EntityFactory::~EntityFactory()
{
	Clear();
}

Entity EntityFactory::CreateEntity()
{
	Entity _Entity{};
	if (!RecycledIDs.empty())
	{
		int Id = RecycledIDs.front();
		_Entity = Entity(Id, Generations[Id]);
		RecycledIDs.pop();
		AliveFlags[Id] = true;
	}
	else
	{
		int Id = NextIdCounter++;
		Generations.push_back(0);
		AliveFlags.push_back(true);
		_Entity = Entity(Id, 0);
	}
	return _Entity;
}

void EntityFactory::DestroyEntity(Entity& _Entity)
{
	AliveFlags[_Entity._ID] = false;
	Generations[_Entity._ID]++;
	RecycledIDs.push(_Entity._ID);
}

const bool EntityFactory::IsAlive(Entity& _Entity) const
{
	return AliveFlags[_Entity._ID] && Generations[_Entity._ID] == _Entity._Gen;
}

void EntityFactory::Clear()
{
	AliveFlags.clear();
	Generations.clear();
	std::queue<uint32_t>().swap(RecycledIDs);
	NextIdCounter = 0;
}

EntityFactory g_EntityFactory;