#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include "Nodes/Node.h"

using NodeFactoryFunc = std::function<Node*(Node *Parent, std::string Name, NodeTransform Transform)>;

using NodeRegistry = std::unordered_map<std::string, NodeFactoryFunc>;
extern NodeRegistry g_NodeRegistry;

inline NodeRegistry& GetNodeRegistry()
{
	static NodeRegistry Instance;
	return Instance;
}

struct NodeRegistrar
{
	NodeRegistrar(const std::string &ClassName, const NodeFactoryFunc &Func)
	{
		GetNodeRegistry()[ClassName] = Func;
	}
};

#define REGISTER_NODE(T) \
	static NodeRegistrar T##Reg(#T, \
		[](Node* Parent, std::string Name, NodeTransform Transform) { \
		return g_World.SpawnNode<T>(Parent, Name, Transform);\
		});