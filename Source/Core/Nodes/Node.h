#ifndef RAYLIBFPS_NODE_H
#define RAYLIBFPS_NODE_H

#include <vector>
#include "../../Debugging/Logger.h"

#ifdef WIN32
#include <Rpc.h>
#elif __LINUX__
#include <uuid/uuid.h>
#endif

#define DECLARE_NODE_CLASS(name) \
	static const char* StaticNodeClassName() { return #name; } \
	virtual const char* GetNodeClassName() const { return #name; }

class Node
{
public:
	DECLARE_NODE_CLASS(Node)

	Node();
	virtual ~Node();

	void SetNewParent(Node* ParentNode);
	void AddChild(Node* ChildNode);
	void RemoveChild(Node* ChildNode);

private:
#if WIN32
	UUID NodeID;
#elif __LINUX__
	uuid_t NodeID;
#endif
	Node* Parent;
	std::vector<Node*> Children;
};


#endif //RAYLIBFPS_NODE_H