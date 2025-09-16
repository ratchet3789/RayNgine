#include "Node.h"
#include <cassert>

void Node::SetNewParent(Node *ParentNode)
{
	assert(ParentNode != nullptr);

	if (Parent)
	{
		Parent->RemoveChild(this);
		Parent = nullptr;
	}

	Parent = ParentNode;
}

void Node::AddChild(Node *ChildNode)
{
	if (std::find(Children.begin(), Children.end(), ChildNode) != Children.end())
	{
		g_Logger.LogWarning("Child node %s is already a child of %s, ignoring.", ChildNode->GetNodeClassName(), GetNodeClassName());
		return;
	}

	Children.push_back(ChildNode);
}

void Node::RemoveChild(Node *ChildNode)
{
	std::vector<Node*>::iterator TargetNode = std::find(Children.begin(), Children.end(), ChildNode);

	if (TargetNode == Children.end())
	{
		g_Logger.LogWarning("%s is not a child of %s", ChildNode->GetNodeClassName(), GetNodeClassName());
		return;
	}
	
	Children.erase(TargetNode);
}
