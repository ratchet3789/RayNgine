//
// Created by addic on 2025/09/16.
//

#ifndef SHOOTER_RAYLIB_WORLDROOT_H
#define SHOOTER_RAYLIB_WORLDROOT_H
#include "../Node.h"

/*
The World Root is the base Root Node for everything in the world. It shouldn't move or be able to be modified
*/
class WorldRoot : public Node
{
public:
	using Node::Node;
};

#endif //SHOOTER_RAYLIB_WORLDROOT_H