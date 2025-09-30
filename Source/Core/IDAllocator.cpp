#include "IDAllocator.h"

void IDAllocator::AssignIdentifer(IDHandle& Handle)
{
	if (FreeList.size() > 0)
	{
		Handle.Id = FreeList.front();
		FreeList.pop();
		Handle.Generation = ++Generations[Handle.Id];
		return;
	}
	Handle.Id = NextId++;
	Handle.Generation = 1;
	Generations[Handle.Id] = Handle.Generation;
}

void IDAllocator::FreeIdentifier(IDHandle &Handle)
{
	FreeList.push(Handle.Id);

}

IDAllocator g_IDAllocator;
