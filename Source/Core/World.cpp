//
// Created by addic on 2025/09/16.
//

#include "World.h"
#include "../Debugging/Logger.h"

void World::Activate(Node *InactiveNode)
{
	if (std::find(ActiveNodes.begin(), ActiveNodes.end(), InactiveNode) != ActiveNodes.end())
	{
		g_Logger.LogWarning("Node %s was not inactive.", InactiveNode->GetName());
		return;
	}

	auto NodeIndex = std::find(InactiveNodes.begin(), InactiveNodes.end(), InactiveNode);
	if (NodeIndex == InactiveNodes.end())
	{
		g_Logger.LogError("Node %s does not exist in either Inactive or Active Nodes. What did you do?!", InactiveNode->GetName());
		return;
	}

	InactiveNodes.erase(NodeIndex);
	ActiveNodes.push_back(InactiveNode);

}

void World::Deactivate(Node *ActiveNode)
{
	if (std::find(InactiveNodes.begin(), InactiveNodes.end(), ActiveNode) != ActiveNodes.end())
	{
		g_Logger.LogWarning("Node %s was not active.", ActiveNode->GetName());
		return;
	}

	auto NodeIndex = std::find(ActiveNodes.begin(), ActiveNodes.end(), ActiveNode);
	if (NodeIndex == ActiveNodes.end())
	{
		g_Logger.LogError("Node %s does not exist in either Inactive or Active Nodes. What did you do?!", ActiveNode->GetName());
		return;
	}

	ActiveNodes.erase(NodeIndex);
	InactiveNodes.push_back(ActiveNode);
}

void World::Tick()
{
	ProcessBeginPlay();
	ProcessEnabled();
	ProcessDisabled();

	std::chrono::time_point<Clock> Now = Clock::now();
	std::chrono::duration<float> Delta = Now - LastTime;

	float DT = Delta.count();

	for (int i=0;i< ActiveNodes.size(); i++)
	{
		if (ActiveNodes[i]->CanTick())
			ActiveNodes[i]->Tick(DT);
	}

	ProcessDestroyed();
	FinalizeDestroyed();
}

void World::AddToDestroyQueue(Node *_Node)
{
	DestroyingQueue.push_back(_Node);
}

void World::AddToEnabledQueue(Node *_Node)
{
	EnabledQueue.push_back(_Node);
}

void World::AddToDisabledQueue(Node *_Node)
{
	DisabledQueue.push_back(_Node);
}

void World::ProcessBeginPlay()
{
}

void World::ProcessEnabled()
{
	for (Node* n : EnabledQueue)
	{
		Activate(n);
	}
}

void World::ProcessDisabled()
{
	for (Node* n : EnabledQueue)
	{
		Deactivate(n);
	}
}

void World::ProcessDestroyed()
{
	for (Node* n : DestroyingQueue)
	{
		RecursivelyMarkForDeletion(n);
	}
	DestroyingQueue.clear();
}

void World::RecursivelyMarkForDeletion(Node *_Node)
{
	for (Node* child : _Node->Children)
	{
		RecursivelyMarkForDeletion(child);
	}
	_Node->OnDestroy();
	DeleteQueue.push_back(_Node);
}

void World::FinalizeDestroyed()
{
	for (Node* n : DeleteQueue)
	{
		delete n;
	}
	DeleteQueue.clear();
}

template<typename T>
T* World::SpawnNode(Node *Parent, const char* Name)
{
	T* Node = new T(Name);
	if (!Parent)
		WorldRoot->AddChild(Node);
	else
		Parent->AddChild(Node);

	ActiveNodes.push_back(Node);
	return Node;
}

World g_World;