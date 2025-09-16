//
// Created by addic on 2025/09/16.
//

#ifndef SHOOTER_RAYLIB_IDALLOCATOR_H
#define SHOOTER_RAYLIB_IDALLOCATOR_H
#include <queue>
#include <map>

struct IDHandle { int Id; int Generation; };

class IDAllocator
{
public:
    void AssignIdentifer(IDHandle& Handle);
    void FreeIdentifier(IDHandle& Handle);

private:
    int NextId{0};
    std::queue<int> FreeList{};
    std::map<int,int> Generations{};
};

extern IDAllocator g_IDAllocator;

#endif //SHOOTER_RAYLIB_IDALLOCATOR_H
