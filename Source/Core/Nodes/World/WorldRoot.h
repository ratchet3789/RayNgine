//
// Created by addic on 2025/09/16.
//

#ifndef SHOOTER_RAYLIB_WORLDROOT_H
#define SHOOTER_RAYLIB_WORLDROOT_H
#include "../Node.h"

/*
The World Root is the base Root Node for everyhting in the world. It shouldn't move or be able to be modified
This won't ever be ticked and won't have
*/
class WorldRoot : public Node
{
	WorldRoot();
};

#endif //SHOOTER_RAYLIB_WORLDROOT_H