//
// Created by addic on 2025/09/16.
//

#include "WorldRoot.h"

WorldRoot::WorldRoot() : Node("WorldRoot")
{
	// We cannot reorder this item AND it will always be active.
	bCanReorderNode = false;
	bEnabled = true;
	bCanTick = false;
}
