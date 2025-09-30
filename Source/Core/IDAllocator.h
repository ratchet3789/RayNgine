#pragma once

#include <queue>
#include <map>

struct IDHandle { int Id; int Generation; };

class IDAllocator
{
public:
    void AssignIdentifer(IDHandle& Handle);
    void FreeIdentifier(IDHandle& Handle);

private:
    uint32_t NextId{0};
    std::queue<uint32_t> FreeList{};
    std::map<uint32_t,uint32_t> Generations{};
};

extern IDAllocator g_IDAllocator;