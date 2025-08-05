#ifndef Entity_H
#define Entity_H

#if _WIN32
#pragma once
#endif

#include <cstdint>

class Entity
{
public:
	Entity();
	~Entity();

	void GetID();

private:
	uint32_t UID{0};

};

#endif //Entity_H