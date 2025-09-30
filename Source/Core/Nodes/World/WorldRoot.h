#pragma once
#include "../Node.h"

/*
The World Root is the base Root Node for everything in the world. It shouldn't move or be able to be modified
*/
class WorldRoot : public Node
{
public:
	using Node::Node;
};