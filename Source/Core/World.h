//
// Created by addic on 2025/09/16.
//

#ifndef SHOOTER_RAYLIB_WORLD_H
#define SHOOTER_RAYLIB_WORLD_H

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

	template<typename T>
	T* SpawnNode(Node* Parent, std::string Name, NodeTransform Transform)
	{
		T* _Node = new T(Name, Transform);
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
#endif //SHOOTER_RAYLIB_WORLD_H