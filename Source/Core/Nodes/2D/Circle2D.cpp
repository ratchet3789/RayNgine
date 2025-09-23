//
// Created by addic on 2025/09/17.
//

#include "Circle2D.h"
#include <raylib.h>
#include "../../Window.h" // Todo: Intermediate classes so we don't just get the window res from the window itself
#include "../../NodeFactory.h"
#include "../../World.h"
#include "../../../Debugging/Logger.h"

void Circle2D::Tick(float DeltaTime)
{
	if ((Transform.Location.X - CircleRadius < 0.0f || Transform.Location.X + CircleRadius > ScreenResolution.X))
	{
		Velocity.X = -Velocity.X;
	}

	if ((Transform.Location.Y - CircleRadius < 0.0f || Transform.Location.Y + CircleRadius > ScreenResolution.Y))
	{
		Velocity.Y = -Velocity.Y;
	}

	DrawCircle(Transform.Location.X, Transform.Location.Y, CircleRadius, CircleColor);

	Transform.Location += Velocity * DeltaTime;
	CircleColor = Color((Transform.Location.X / ScreenResolution.X) * 255.0f, (Transform.Location.Y / ScreenResolution.Y) * 255.0f, 128.0f, 255.0f);
}

void Circle2D::BeginPlay()
{
	g_Window.GetRendererScale(ScreenResolution.X, ScreenResolution.Y);
	Transform.Location = Vec3(ScreenResolution.X*.5f, ScreenResolution.Y*.5f, 0.0f);
}

REGISTER_NODE(Circle2D)
