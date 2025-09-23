#ifndef RAYLIBFPS_NODE_H
#define RAYLIBFPS_NODE_H

//#include <raymath.h>
#include <raylib.h>

#include <vector>
#include <string>

#include "../IDAllocator.h"
#include "../Math/Vector.h"

#define DECLARE_NODE_CLASS(name) \
	static const char* StaticNodeClassName() { return #name; } \
	virtual const char* GetNodeClassName() const { return #name; }

struct NodeTransform
{
	NodeTransform() {};
	NodeTransform(const Vec3 Loc) : Location(Loc) {};
	NodeTransform(const Vec3 Loc, const Quat Rot) : Location(Loc), Rotation(Rot) {};
	NodeTransform(const Vec3 Loc, const Quat Rot, const Vec3 Scl) : Location(Loc), Rotation(Rot), Scale(Scl) {};

	Vec3 Location{0, 0, 0};
	Quat Rotation{0, 0, 0, 0};
	Vec3 Scale{1, 1, 1};
};

class Node
{
public:
	DECLARE_NODE_CLASS(Node)
	Node(std::string Name, NodeTransform _Transform);

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
	NodeTransform Transform{};
	std::string GetName() const { return DisplayName; }

	// Base Node Calls
	// Called when object Spawned/Created
	virtual void BeginPlay() {}
	// Called Per-frame
	virtual void Tick(float DeltaTime) {}
	// Called per-Physics Tick
	virtual void FixedUpdate(float DeltaTime) {}
	// Called when Garbage Collected

	virtual void OnDestroy() {}
	// Called when Enabled by user via Enable()
	virtual void OnEnable() {}
	// Called when Disabled by user via Disable()
	virtual void OnDisable() {}
	// Called when Key Press registered in Window
	virtual void KeyPressed(KeyboardKey Key) {}

	inline bool CanTick() { return bCanTick;}

	Node *Parent;
	std::vector<Node*> Children{};

	bool bEnabled{true};
	bool bCanReorderNode{true};
	bool bCanTick{true};

protected:
	std::string DisplayName;
	IDHandle UniqueID;

private:
	void OnDestroy_World();
	void OnEnable_World();
	void OnDisable_World();
};

#endif //RAYLIBFPS_NODE_H
