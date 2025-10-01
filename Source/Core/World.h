#pragma once

#include "Nodes/Node.h"
#include <chrono>

#define WORLD_ROOT "WorldRoot"

class World
{
public:
	World();
	virtual ~World();

	// WorldRoot is a requirement for the World itself to exist
	Node* _WorldRoot;
	// The levels name
	std::string WorldName;

	// Player based spawning of T Node
	template<typename T>
	T* SpawnNode(Node* Parent, std::string Name, Transform _Transform)
	{
		T* WorldNode = new T(Name, _Transform);
		if (!Parent)
		{
			const char* _NM = typeid(T).name();

			if (strstr(_NM, WORLD_ROOT) == nullptr)
			{
				_WorldRoot->AddChild(WorldNode);
			}
			else
			{
				_WorldRoot = WorldNode;
			}
		}
		else
		{
			Parent->AddChild(WorldNode);
		}

		BeginPlayQueue.push_back(WorldNode);
		ActiveNodes.push_back(WorldNode);
		return WorldNode;
	}

	// Level Loader spawning of T Node (I wouldn't use this but hey, I'm not your parent.)
	template<typename T>
	T* SpawnJsonNode(Node* Parent, rapidjson::GenericValue<rapidjson::UTF8<>>& Data)
	{
		// Check for Malformed JSON
		const char* Name;
		Transform _Transform;

		T* WorldNode = new T(Name, _Transform);
		if (!Parent)
		{
			const char* _NM = typeid(T).name();

			if (strstr(_NM, WORLD_ROOT) == nullptr)
			{
				_WorldRoot->AddChild(WorldNode);
			}
			else
			{
				_WorldRoot = WorldNode;
			}
		}
		else
		{
			Parent->AddChild(WorldNode);
		}

		BeginPlayQueue.push_back(WorldNode);
		ActiveNodes.push_back(WorldNode);
		return WorldNode;
	}

	void Activate(Node* InactiveNode);
	void Deactivate(Node* ActiveNode);

	void Tick();

	void AddToDestroyQueue(Node* WorldNode);
	void AddToEnabledQueue(Node* WorldNode);
	void AddToDisabledQueue(Node* WorldNode);

	void ProcessBeginPlay();
	void ProcessEnabled();
	void ProcessDisabled();
	void ProcessDestroyed();
	void RecursivelyMarkForDeletion(Node* WorldNode);
	void FinalizeDestroyed();

	// Singleton
	static void Create();
	static World* Get();

private:
	std::vector<Node*> ActiveNodes;
	std::vector<Node*> InactiveNodes;
	std::vector<Node*> KeyPressedQueue;

	using Clock = std::chrono::high_resolution_clock;
	std::chrono::time_point<Clock> LastTime = Clock::now();

	// our object queues
	std::vector<Node*> DestroyingQueue;
	std::vector<Node*> DeleteQueue;

	std::vector<Node*> EnabledQueue;
	std::vector<Node*> DisabledQueue;
	std::vector<Node*> BeginPlayQueue;
};

extern World* g_pWorld;