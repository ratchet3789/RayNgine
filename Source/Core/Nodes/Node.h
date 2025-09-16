#ifndef RAYLIBFPS_NODE_H
#define RAYLIBFPS_NODE_H

//#include <raymath.h>
#include <raylib.h>

#include <vector>
#include "../IDAllocator.h"


#define DECLARE_NODE_CLASS(name) \
	static const char* StaticNodeClassName() { return #name; } \
	virtual const char* GetNodeClassName() const { return #name; }

struct NodeTransform
{
	Vector3 Location{0, 0, 0};
	Quaternion Rotation{0, 0, 0, 0};
	Vector3 Scale{1, 1, 1};
};

class Node
{
public:
	DECLARE_NODE_CLASS(Node)

	Node(const char* Name);

	virtual ~Node()
	{
		g_IDAllocator.FreeIdentifier(UniqueID);
	};

	// Primarily Called in Editor
	void SetNewParent(Node *ParentNode);

	void AddChild(Node *ChildNode);

	void RemoveChild(Node *ChildNode);

	const IDHandle GetEntityID() const { return UniqueID; }

	// Operator Overloads
	bool operator==(const Node &B) const {return B.GetEntityID().Id == GetEntityID().Id && B.GetEntityID().Generation == UniqueID.Generation;}
	bool operator!=(const Node &B) const { return !(*this == B); }

	// Core
	NodeTransform transform{};
	const char* GetName() const { return DisplayName; }

	// Base Node Calls
	// Called when object Spawned/Created
	virtual void Start() = 0;
	// Called Per-frame
	virtual void Tick(float DeltaTime) = 0;
	// Called per-Physics Tick
	virtual void FixedUpdate(float DeltaTime) = 0;
	// Called when Garbage Collected

	virtual void OnDestroy() = 0;
	// Called when Enabled by user via Enable()
	virtual void OnEnable() = 0;
	// Called when Disabled by user via Disable()
	virtual void OnDisable() = 0;
	// Called when Key Press registered in Window
	virtual void KeyPressed(KeyboardKey Key) = 0;

	inline bool CanTick() { return bCanTick;}

	Node *Parent;
	std::vector<Node *> Children;

	bool bEnabled{true};
	bool bCanReorderNode{true};
	bool bCanTick{true};

protected:
	const char* DisplayName;
	IDHandle UniqueID;

private:
	void OnDestroy_World();
	// Called when Enabled by user via Enable()
	void OnEnable_World();
	// Called when Disabled by user via Disable()
	void OnDisable_World();
};

#endif //RAYLIBFPS_NODE_H
