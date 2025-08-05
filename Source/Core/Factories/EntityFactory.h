#include <cstdint>
#include <queue>
#ifndef EntityFactory_H
#define EntityFactory_H

#if _WIN32
#pragma once
#endif

#define MAX_ENTITIES 5000

//https://austinmorlan.com/posts/entity_component_system/#the-entity

struct Entity
{
	Entity() : _ID(0), _Gen(0) {}
	Entity(int ID, int Gen) : _ID(ID), _Gen(Gen) {}

	uint16_t _ID;
	uint16_t _Gen;
	
	bool operator==(const Entity& other) const { return _ID == other._ID && _Gen == other._Gen;}
	bool operator!=(const Entity& other) const { return !(_ID == other._ID && _Gen == other._Gen); }
};

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	Entity CreateEntity(); // Gives a UID + Current Generation and then marks as alive
	void DestroyEntity(Entity& _Entity); // Marks dead, recycles ID
	void Clear(); // Wipes all entities

	__forceinline const bool IsAlive(Entity& _Entity) const; // Checks ID validity + generation

private:
	std::queue<uint32_t> RecycledIDs;
	std::vector<int32_t> Generations;
	std::vector<uint8_t> AliveFlags;
	uint32_t NextIdCounter{0};
};
extern EntityFactory g_EntityFactory;

#endif //EntityFactory_H