//
// Created by addic on 2025/09/17.
//

#ifndef SHOOTER_RAYLIB_CIRCLE2D_H
#define SHOOTER_RAYLIB_CIRCLE2D_H
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

};


#endif //SHOOTER_RAYLIB_CIRCLE2D_H
