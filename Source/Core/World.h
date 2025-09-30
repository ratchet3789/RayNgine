#pragma once

#include "Nodes/Node.h"
#include <chrono>

#define WORLD_ROOT "WorldRoot"

class World
{
public:
	World();
	virtual ~World();

	Node* _WorldRoot;
	std::string WorldName;

	// Player based spawning of T Node
	template<typename T>
	T* SpawnNode(Node* Parent, std::string Name, Transform _Transform)
	{
		T* _Node = new T(Name, _Transform);
		if (!Parent)
		{
			const char* _NM = typeid(T).name();

			if (strstr(_NM, WORLD_ROOT) == nullptr)
			{
				_WorldRoot->AddChild(_Node);
			}
			else
			{
				_WorldRoot = _Node;
			}
		}
		else
		{
			Parent->AddChild(_Node);
		}

		BeginPlayQueue.push_back(_Node);
		ActiveNodes.push_back(_Node);
		return _Node;
	}

	// Level Loader spawning of T Node
	template<typename T>
	T* SpawnJsonNode(Node* Parent, rapidjson::GenericValue<rapidjson::UTF8<>>& Data)
	{
		// Check for Malformed JSON
		const char* Name;
		Transform _Transform;

		T* _Node = new T(Name, _Transform);
		if (!Parent)
		{
			const char* _NM = typeid(T).name();

			if (strstr(_NM, WORLD_ROOT) == nullptr)
			{
				_WorldRoot->AddChild(_Node);
			}
			else
			{
				_WorldRoot = _Node;
			}
		}
		else
		{
			Parent->AddChild(_Node);
		}

		BeginPlayQueue.push_back(_Node);
		ActiveNodes.push_back(_Node);
		return _Node;
	}

	void Activate(Node* InactiveNode);
	void Deactivate(Node* ActiveNode);

	void Tick();

	void AddToDestroyQueue(Node* _Node);
	void AddToEnabledQueue(Node* _Node);
	void AddToDisabledQueue(Node* _Node);

	void ProcessBeginPlay();
	void ProcessEnabled();
	void ProcessDisabled();
	void ProcessDestroyed();
	void RecursivelyMarkForDeletion(Node* _Node);
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