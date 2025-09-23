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

	virtual void Start(){};
	virtual void FixedUpdate(float DeltaTime){};

	virtual void OnDestroy(){};
	virtual void OnEnable(){};
	virtual void OnDisable(){};
	virtual void KeyPressed(KeyboardKey Key){};

public:
	Vector3 Location;

};


#endif //SHOOTER_RAYLIB_CIRCLE2D_H
