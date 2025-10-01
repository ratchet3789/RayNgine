#include "World.h"
#include "../Debugging/Logger.h"
#include "Nodes/World/WorldRoot.h"

World::World()
{
}

World::~World()
{
	for (Node *WorldNode: ActiveNodes) { delete WorldNode; }
	for (Node *WorldNode: InactiveNodes) { delete WorldNode; }
}

void World::Activate(Node *InactiveNode)
{
	if (std::find(ActiveNodes.begin(), ActiveNodes.end(), InactiveNode) != ActiveNodes.end())
	{
		g_Logger.LogWarning("Node %s was not inactive.", InactiveNode->GetName().c_str());
		return;
	}

	auto NodeIndex = std::find(InactiveNodes.begin(), InactiveNodes.end(), InactiveNode);
	if (NodeIndex == InactiveNodes.end())
	{
		g_Logger.LogError("Node %s does not exist in either Inactive or Active Nodes. What did you do?!",
		                  InactiveNode->GetName().c_str());
		return;
	}

	InactiveNodes.erase(NodeIndex);
	ActiveNodes.push_back(InactiveNode);
}

void World::Deactivate(Node *ActiveNode)
{
	if (std::find(InactiveNodes.begin(), InactiveNodes.end(), ActiveNode) != ActiveNodes.end())
	{
		g_Logger.LogWarning("Node %s was not active.", ActiveNode->GetName().c_str());
		return;
	}

	auto NodeIndex = std::find(ActiveNodes.begin(), ActiveNodes.end(), ActiveNode);
	if (NodeIndex == ActiveNodes.end())
	{
		g_Logger.LogError("Node %s does not exist in either Inactive or Active Nodes. What did you do?!",
		                  ActiveNode->GetName().c_str());
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

	for (int i = 0; i < ActiveNodes.size(); i++)
	{
		if (ActiveNodes[i]->CanTick())
			ActiveNodes[i]->Tick(DT);
	}

	LastTime = Now;

	ProcessDestroyed();
	FinalizeDestroyed();
}

void World::AddToDestroyQueue(Node *WorldNode)
{
	if (WorldNode != nullptr)
	{
		if (std::find(DestroyingQueue.begin(), DestroyingQueue.end(), WorldNode) == DestroyingQueue.end())
		{
			DestroyingQueue.push_back(WorldNode);
		}
	}
}

void World::AddToEnabledQueue(Node *WorldNode)
{
	if (WorldNode != nullptr)
	{
		EnabledQueue.push_back(WorldNode);
	}
}

void World::AddToDisabledQueue(Node *WorldNode)
{
	if (WorldNode != nullptr)
	{
		DisabledQueue.push_back(WorldNode);
	}
}

void World::ProcessBeginPlay()
{
	for (Node *n: BeginPlayQueue)
	{
		n->BeginPlay();
	}
	BeginPlayQueue.clear();
}

void World::ProcessEnabled()
{
	for (Node *n: EnabledQueue)
	{
		Activate(n);
	}
}

void World::ProcessDisabled()
{
	for (Node *n: EnabledQueue)
	{
		Deactivate(n);
	}
}

void World::ProcessDestroyed()
{
	for (Node *n: DestroyingQueue)
	{
		RecursivelyMarkForDeletion(n);
	}
	DestroyingQueue.clear();
}

void World::RecursivelyMarkForDeletion(Node *WorldNode)
{
	for (Node *child: WorldNode->Children)
	{
		RecursivelyMarkForDeletion(child);
	}
	WorldNode->OnDestroy();
	DeleteQueue.push_back(WorldNode);
}

void World::FinalizeDestroyed()
{
	for (Node *n: DeleteQueue)
	{
		delete n;
	}
	DeleteQueue.clear();
}

void World::Create()
{
	if (g_pWorld)
	{
		delete g_pWorld;
	}

	g_pWorld = new World();
}

World *World::Get()
{
	return g_pWorld;
}

World *g_pWorld;
