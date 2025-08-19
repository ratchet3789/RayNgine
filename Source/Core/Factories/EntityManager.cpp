#include "EntityManager.h"

#include <cassert>

EntityManager::EntityManager()
{
	for (Entity _Ent = 0; _Ent < MAX_ENTITIES; _Ent++)
	{
		Entities.push(_Ent);
	}
}

EntityManager::~EntityManager()
{
	Clear();
}

Entity EntityManager::CreateEntity()
{
	assert(LivingEntityCount < MAX_ENTITIES);

	Entity _Ent = Entities.front();
	Entities.pop();
	LivingEntityCount++;
	
	return _Ent;
}

void EntityManager::DestroyEntity(Entity _Entity)
{
	assert(_Entity < LivingEntityCount);

	Signatures[_Entity].reset();
	Entities.push(_Entity);
	LivingEntityCount--;	
}

void EntityManager::Clear()
{
	Entities.empty();
	for (Entity _Ent = 0; _Ent < MAX_ENTITIES; _Ent++)
	{
		Entities.push(_Ent);
	}

	Signatures.empty();
	Signatures = std::array<Signature, MAX_ENTITIES>();

	LivingEntityCount = 0;
}

Signature EntityManager::GetSignature(Entity _Entity)
{
	assert(_Entity < LivingEntityCount);

	return Signatures[_Entity];
}

void EntityManager::SetSignature(Entity _Entity, Signature _Signature)
{
	assert(_Entity < LivingEntityCount);

	Signatures[_Entity] = _Signature;
}

EntityManager g_EntityFactory;
