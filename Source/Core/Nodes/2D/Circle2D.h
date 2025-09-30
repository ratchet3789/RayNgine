#pragma once
#include "../Node.h"


class Circle2D : public Node
{
public:
	using Node::Node;

	void Tick(float DeltaTime) override;
	void BeginPlay() override;
	void KeyPressed(KeyboardKey Key) override {};

private:
	Vec3 Velocity{256.0f, 256.0f, 0.0f};
	Vec2 ScreenResolution;

	float CircleRadius{32.0f};
	Color CircleColor{255,100,255,255};

	DECLARE_DATA_TABLE(Circle2D)
};

START_DATA_TABLE(Circle2D)
	DATA_TABLE_ENTRY("Velocity", Circle2D, Velocity, FIELD_VEC3, nullptr)
	DATA_TABLE_ENTRY("CircleRadius", Circle2D, CircleRadius, FIELD_FLOAT, nullptr)
END_DATA_TABLE()