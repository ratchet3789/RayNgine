#pragma once
#include "../Node.h"

class Node3D_Physics : public Node
{
public:
	Node3D_Physics();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void FixedUpdate(float DeltaTime) override;
	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;
	void KeyPressed(KeyboardKey Key) override;
};
