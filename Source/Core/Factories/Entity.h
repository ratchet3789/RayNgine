#ifndef Entity_H
#define Entity_H

#if _WIN32
#pragma once
#endif

#include <cstdint>

class UniqueEntity
{
public:
	UniqueEntity();
	~UniqueEntity();

	void GetID();

private:
	uint32_t UID{0};

};

#endif //Entity_H