#pragma once

enum PhysicsEngine
{
	PHYS_NONE,
	PHYS_VOLT
};

class Physics
{
public:
	Physics();
	~Physics();

	bool Initialize();
	void Release();

};

extern Physics g_Physics;
