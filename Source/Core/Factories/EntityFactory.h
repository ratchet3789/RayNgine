#include <cstdint>
#include <queue>
#ifndef EntityFactory_H
#define EntityFactory_H

#if _WIN32
#pragma once
#endif

struct UniqueEntity
{
	UniqueEntity() : _ID(0), _Gen(0) {}
	UniqueEntity(int ID, int Gen) : _ID(ID), _Gen(Gen) {}

	uint16_t _ID;
	uint16_t _Gen;
	
	bool operator==(const UniqueEntity& other) const { return _ID == other._ID && _Gen == other._Gen;}
	bool operator!=(const UniqueEntity& other) const { return !(_ID == other._ID && _Gen == other._Gen); }
};

class EntityFactory
{
	EntityFactory();
	~EntityFactory();

	UniqueEntity CreateEntity(); // Gives a UID + Current Generation and then marks as alive
	void DestroyEntity(UniqueEntity& _Entity); // Marks dead, recycles ID
	__forceinline const bool IsAlive(UniqueEntity& _Entity) const; // Checks ID validity + generation
	void Clear(); // Wipes all entities

private:
	std::queue<uint32_t> RecycledIDs;
	std::vector<int32_t> Generations;
	std::vector<uint8_t> AliveFlags;
	uint32_t NextIdCounter{0};
};

#endif //EntityFactory_H