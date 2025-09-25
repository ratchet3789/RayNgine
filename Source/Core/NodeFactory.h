#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include "Nodes/Node.h"

using NodeFactoryFunc = std::function<Node*(Node *Parent, std::string Name, Transform _Transform)>;

using NodeRegistry = std::unordered_map<std::string, NodeFactoryFunc>;

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
		[](Node* Parent, std::string Name, Transform _Transform) { \
		return g_pWorld->SpawnNode<T>(Parent, Name, _Transform);\
		});