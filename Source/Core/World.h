//
// Created by addic on 2025/09/16.
//

#ifndef SHOOTER_RAYLIB_WORLD_H
#define SHOOTER_RAYLIB_WORLD_H

#include "Nodes/Node.h"
#include <chrono>

class World
{
public:
	Node* WorldRoot;
	std::string WorldName;

	template<typename T>
	T* SpawnNode(Node* Parent, std::string Name);

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
};

extern World g_World;
#endif //SHOOTER_RAYLIB_WORLD_H