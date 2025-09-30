#include "World.h"
#include "../Debugging/Logger.h"
#include "Nodes/World/WorldRoot.h"

World::World() { }

World::~World()
{
	for (Node* _Node : ActiveNodes) { delete _Node; }
	for (Node* _Node : InactiveNodes) { delete _Node; }
}

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

	LastTime = Now;

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
	for (Node* n : BeginPlayQueue)
	{
		n->BeginPlay();
	}
	BeginPlayQueue.clear();
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

void World::Create()
{
	if (g_pWorld)
	{
		delete g_pWorld;
	}

	g_pWorld = new World();
}

World* World::Get()
{
	return g_pWorld;
}

World* g_pWorld;
