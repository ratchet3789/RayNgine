#ifndef EntityFactory_H
#define EntityFactory_H

#if _WIN32
#pragma once
#endif

#include <cstdint>
#include <queue>
#include <bitset>
#include <array>

#define MAX_ENTITIES 5000
using Entity = uint32_t;
using Signature = std::bitset<MAX_ENTITIES>;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity CreateEntity(); // Gives a UID + Current Generation and then marks as alive
	void DestroyEntity(Entity _Entity); // Marks dead, recycles ID
	void Clear(); // Wipes all entities

	Signature GetSignature(Entity _Entity);
	void SetSignature(Entity _Entity, Signature _Signature);

private:
	std::queue<Entity> Entities;
	std::array<Signature, MAX_ENTITIES> Signatures;
	uint32_t LivingEntityCount{0};
};
extern EntityManager g_EntityFactory;

#endif //EntityFactory_H