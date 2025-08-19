#ifndef Entity_H
#define Entity_H

#if _WIN32
#pragma once
#endif

#include <cassert>

#include "../Factories/EntityManager.h"
#include <cstdint>
#include <unordered_map>

#define VALIDATE_ENTITY() \
	{ \
	assert(mEntityToIndexMap.find(_Entity) == mEntityToIndexMap.end() && "Component added to same entity more than once"); \
	}

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity _Entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
	void InsertData(Entity _Entity, T Component)
	{
		VALIDATE_ENTITY()
		
		size_t NewIndex = mSize;
		mEntityToIndexMap[_Entity] = NewIndex;
		mIndexToEntityMap[NewIndex] = _Entity;
		mComponentArray[NewIndex] = Component;
		++mSize;
	}

	void RemoveData(Entity _Entity)
	{
		VALIDATE_ENTITY()

		// Copy element at end into deleted elements place to maintain density
		size_t IndexOfRemovedEntity = mEntityToIndexMap[_Entity];
		size_t IndexOfLastElement = mSize -1;
		mComponentArray[IndexOfRemovedEntity] = mComponentArray[IndexOfLastElement];

		// Update our maps to point to the new locations
		Entity EntityOfLastElement = mIndexToEntityMap[IndexOfLastElement];
		mEntityToIndexMap[EntityOfLastElement] = IndexOfRemovedEntity;
		mIndexToEntityMap[IndexOfRemovedEntity] = EntityOfLastElement;

		mEntityToIndexMap.erase(_Entity);
		mIndexToEntityMap.erase(IndexOfLastElement);

		--mSize;
	}
	
	T& GetData(Entity _Entity)
	{
		VALIDATE_ENTITY()

		return mComponentArray[mEntityToIndexMap[_Entity]];
	}
	
	void EntityDestroyed(Entity _Entity) override
	{
		if (mEntityToIndexMap.find(_Entity) != mEntityToIndexMap.end())
		{
			RemoveData(_Entity);
		}
	}

private:
	// The packed array of components (of Generic Type T), set to a specified
	// maximum amount, matchin hte maximum number of entities allowed to exist
	// simultaneously, so that each entity has a unique spot.
	std::array<T, MAX_ENTITIES> mComponentArray;

	// Map from an entity ID to an array index
	std::unordered_map<Entity, size_t> mEntityToIndexMap;

	// Map from an array index to an entity ID.
	std::unordered_map<size_t, Entity> mIndexToEntityMap;

	// Total size of valid entries in the array
	size_t mSize;	
};
#endif //Entity_H
