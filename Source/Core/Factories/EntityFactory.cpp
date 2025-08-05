#include "EntityFactory.h"

UniqueEntity EntityFactory::CreateEntity()
{
	UniqueEntity Entity{};
	if (!RecycledIDs.empty())
	{
		int Id = RecycledIDs.front();
		Entity = UniqueEntity(Id, Generations[Id]);
		RecycledIDs.pop();
		AliveFlags[Id] = true;
	}
	else
	{
		int Id = NextIdCounter++;
		Generations.push_back(0);
		AliveFlags.push_back(true);
		Entity = UniqueEntity(Id, 0);
	}
	return Entity;
}

void EntityFactory::DestroyEntity(UniqueEntity& _Entity)
{
	AliveFlags[_Entity._ID] = false;
	Generations[_Entity._ID]++;
	RecycledIDs.push(_Entity._ID);
}

const bool EntityFactory::IsAlive(UniqueEntity& _Entity) const
{
	return AliveFlags[_Entity._ID] && Generations[_Entity._ID] == _Entity._Gen;
}

void EntityFactory::Clear()
{
}
